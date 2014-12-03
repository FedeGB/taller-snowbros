/*
 * ConnectionHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "ConnectionHandler.h"
#include "../utiles/tipos.h"
#include "../utiles/Timer.h"
#include <iostream>

ConnectionHandler::ConnectionHandler(ControladorUsuarios & c, TCPStream * stream) :
	controlador(c), m_stream(stream){}


int ConnectionHandler::logIn(std::string username){

	// Si el usuario ya se habia loggeado durante la partida, lo reconecta.
	if (controlador.usuarioExiste(username)){
		Usuario* user = controlador.obtenerUsuario(username);
		if(user->online) {
			return USERONLINE;
		}else if (!user->isPJAlive()){
			return USERDEAD;
		} else {
			user->setOnline(true);
		}

	// En caso contrario, si hay lugares vacantes en el escenario, lo agrega
	// como un nuevo PJ.
	} else {
		if (controlador.escenarioLleno()) return SERVERFULL;
		controlador.registrarUsuario(username);
	}
	return OK; //controlador.numeroUsuario(username);
}

// Bloquea hasta que se hayan conectado (y validado) todos los clientes requeridos
// por el servidor.
bool ConnectionHandler::esperarPorMasJugadores(){

	ssize_t len;

	// Espera a que esten conectados todos los jugadores necesarios.
	while(!controlador.escenarioLleno()) {
		len = m_stream->send("SERVER-ESPERANDO");
		if(len <= 0) return false;
		std::cout << "el server esta esperando mas conexiones" << std::endl;
		usleep(20000);
	}

	len = m_stream->send("SERVER-LISTO");
	if(len <= 0) return false;
	std::cout << username << ": iniciando simulacion" << std::endl;

	return true;
}

// Ejecuta los pasos necesarios para validar la conexion entrante. En base al nombre de
// usuario provisto por el cliente que se intenta conectar, determina si puede permitirle
// acceso al servidor.
// - Si el servidor ya esta lleno, rechaza la conexion, informando el motivo.
// - Si el usuario provisto por el cliente ya se encuentra conectado, rechaza la conexion,
// informando el motivo.
// - Si el usuario provisto por el cliente murio durante la partida actual, rechaza la conexion,
// informando el motivo.
// - En caso que no se de alguna de las condiciones anteriores, se acepta la conexion, y
// se pone al cliente en standby hasta que se llene el servidor y empiece la partida.
// retorno: true si se acepto la conexion, false en caso contrario, siempre siguiendo lo indicado
// anteriormente.
// NOTA: Esta funcion bloquea hasta que se llene el servidor. Al momento del retorno,
// la partida ya ha comenzado.
bool ConnectionHandler::protocoloLogIn(){

	// Inicia la comunicacion recibiendo el nombre de usuario y validando sus datos de login.
	m_stream->receive(username);
	int result = logIn(username);

	// Rechaza la conexion si el servidor esta lleno.
	if (result == SERVERFULL) {
		printf ("Conexion rechazada, conexiones llenas. %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = "RECHAZADA-FULL";
		m_stream->send(outMsg);
		return false;

	// Rechaza la conexion si el usuario ya se encuentra conectado.
	}else if( result == USERONLINE){
		printf ("Conexion rechazada, user esta online. %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = "RECHAZADA-USR";
		m_stream->send(outMsg);
		return false;

	// Rechaza la conexion si el usuario ya murio durante esta partida.
	}else if( result == USERDEAD){
		printf ("Conexion rechazada, user esta muerto. %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = "RECHAZADA-USR";
		m_stream->send(outMsg);
		return false;

	// Acepta la conexion si no se da ninguna de las condiciones anteriores.
	}else{
		printf ("Conexion aceptada %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = "OK";
		size_t len = m_stream->send(outMsg);
		if(len<=0){
			return false;
		}

		// Bloquea hasta que el servidor este listo para jugar.
		return esperarPorMasJugadores();
	}
}

// Loop que representa la comunicacion entre cliente y servidor a lo largo de una partida:
// se reciben eventos y luego se envia la pantalla a renderear para representar el estado
// actual de juego. Se rompe cuando se pierde la conexion, o la partida finaliza.
// retorno: false si se pierde la conexion, true si la partida finalizo sin problemas.
bool ConnectionHandler::loopPartida(){

	bool quit = false;
	std::string outMessage;
	ssize_t len;

	while (!controlador.finDePartida){

		// Recibe todos los eventos sucedidos en el cliente.
		quit = !recibirEventos();
		if (quit) return false;

		// Obtiene la representacion serializada de la pantalla, y la envia.
		if (controlador.obtenerUsuario(username)->inicializado)
			outMessage = controlador.obtenerPantallaSerializada(username);
		else outMessage= "EMPTY";

		len = m_stream->send(outMessage);
		if (len <= 0) return false;

		controlador.obtenerUsuario(username)->enviarSenial();
	}

	return true;
}

// Recibe todos los eventos sucedidos en el cliente desde la ultima vez que se llamo al metodo.
// Los almacena en la cola de notificaciones para ser procesados por el thread de simulacion.
// retorno: false si se corto la comunicacion, true en caso contrario.
bool ConnectionHandler::recibirEventos(){

	ssize_t len;
	std::string inMessage = "NOTDONE";
	while (inMessage != "DONE"){
		len = m_stream->receive(inMessage);
		if (len <= 0) {
			if(!controlador.obtenerUsuario(username)->isPJAlive())
				controlador.obtenerUsuario(username)->DeletePj();
			return false;
		}
		if (inMessage != "DONE") {
			teclas_t IDEvento = (teclas_t) atol(inMessage.c_str());
			controlador.obtenerUsuario(username)->encolarNotificacion(IDEvento);
		}
	}
	return true;
}

// Informa al Jugador el resultado de la partida, y le pregunta si quiere seguir jugando.
// En caso de que quiera seguir, se lo pone en espera para la siguiente partida.
// En caso contrario, se lo quita de los usuarios del servidor y se desconecta.
// retorno: true si decide seguir jugando, false en caso contrario; o si se desconecta.
// NOTA: Esta funcion bloquea hasta que se llene el servidor. Al momento del retorno,
// la partida ya ha comenzado.
bool ConnectionHandler::protocoloFinDePartida(){

	ssize_t len;

	controlador.confirmarUsuario(username, ESPERANDO_ESTADO);

	// Recibe los inputs de la ultima iteracion, y los descarta.
	std::string inMessage = "NOTDONE";
	while (inMessage != "DONE")	len = m_stream->receive(inMessage);

	// Envia el resultado de la partida.
	std::string outMessage = SSTR("GAMEENDED%" << controlador.resultadoPartida);
	len = m_stream->send(outMessage);
	if (len <= 0) return false;

	// Recibe la decision del jugador.
	while(inMessage == "DONE"){
		len = m_stream->receive(inMessage);
		if (len <= 0) return false;
	}
	std::cout << "recibi la siguiente respuesta del jugador: " << inMessage << std::endl;
	// Si contesto CONTINUEPLAYING lo encola para la siguiente partida, en caso contrario lo
	// quita de los jugadores disponibles para la siguiente partida.

	if (inMessage == "CONTINUEPLAYING") {
		controlador.confirmarUsuario(username, REGISTRADO);
		return esperarPorMasJugadores();
	}
	else {
		controlador.eliminarUsuario(username);
		return false;
	}
}

void* ConnectionHandler::run() {

	printf("Conexion con: %s:%d establecida.\n", m_stream->getPeerIP().c_str() , m_stream->getPeerPort());

	// Valida las credenciales del cliente, lo conecta y espera a que empiece el juego; o rechaza la
	// conexion y termina.
	bool quit = !protocoloLogIn();
	if (quit) return NULL;

	// Loop de partidas. Mientras el usuario elija permanecer conectado, jugara una partida
	// tras otra.
	while (!quit){

		// Loop que representa una partida: recibir eventos y enviar pantalla a renderear.
		// Se rompe cuando se pierde la conexion, o la partida finaliza.
		quit = !loopPartida();
		if (quit) break;

		// Termino la partida, debo informar el resultado al jugador y preguntar si quiere seguir jugando.
		quit = !protocoloFinDePartida();
	}

	controlador.obtenerUsuario(username)->setOnline(false);
	controlador.obtenerUsuario(username)->enviarSenial();

	printf("Conexion con: %s:%d terminada.\n", m_stream->getPeerIP().c_str() , m_stream->getPeerPort());

	delete m_stream;

	return NULL;
}

