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

ConnectionHandler::ConnectionHandler(TCPStream * stream, ControladorJuego * c):
	m_stream(stream), controlador(c){}


int ConnectionHandler::logIn(std::string username){

	// Si el usuario ya se habia loggeado durante la partida, lo reconecta.
	if (controlador->estado.jugadorExiste(username)){
		Jugador * jugador = controlador->estado.obtenerJugador(username);
		if(jugador->estado == Jugador::CONECTADO) {
			return USERONLINE;
		}else if (jugador->vidas <= 0){
			return USERDEAD;
		} else {
			jugador->estado = Jugador::CONECTADO;
			return OK;
		}

	// En caso contrario, si hay lugares vacantes en el escenario, lo agrega
	// como un nuevo PJ.
	} else if (controlador->estado.escenarioLleno()) return SERVERFULL;

	controlador->estado.registrarJugador(username);
	return OK;
}


// Bloquea hasta que se hayan conectado (y validado) todos los clientes requeridos
// por el servidor.
bool ConnectionHandler::esperarPorMasJugadores(){

	ssize_t len;

	int cantidadEnviados = 0;
	std::string mensaje;

	// Espera a que esten conectados todos los jugadores necesarios.
	while(!controlador->estado.escenarioLleno()) {

		// Checkea si se envio la informacion de todos los que se encuentran conectados.
		if (controlador->estado.cantidadOnline() != cantidadEnviados)

			// Si no se enviaron todos, se envian los que falten.
			for(int i = 1; i <= 4; i++){
				if (!controlador->estado.jugadorExiste(i)) continue;

				mensaje = SSTR( NUEVOJUGADOR << SEPARADORCAMPOS <<
					controlador->estado.obtenerJugador(i)->serializar() );
				len = m_stream->send(mensaje);
				if(len <= 0) return false;
			}

		cantidadEnviados = controlador->estado.cantidadOnline();

		// Si se enviaron todos, envia que se estan esperando conexiones.
		mensaje = SSTR(ESPERANDO);
		len = m_stream->send(mensaje);
		if(len <= 0) return false;

		usleep(20000);
	}

	len = m_stream->send(SSTR(INICIAJUEGO));
	if(len <= 0) return false;

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
bool ConnectionHandler::protocoloLogIn(){

	// Inicia la comunicacion recibiendo el nombre de usuario y validando sus datos de login.
	m_stream->receive(username);
	int result = logIn(username);

	// Rechaza la conexion si el servidor esta lleno.
	if (result == SERVERFULL) {
		printf ("Conexion rechazada, conexiones llenas. %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = SSTR(CONEXIONRECHAZADASERVIDORLLENO);
		m_stream->send(outMsg);
		return false;

	// Rechaza la conexion si el usuario ya se encuentra conectado.
	}else if( result == USERONLINE){
		printf ("Conexion rechazada, user esta online. %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = SSTR(CONEXIONRECHAZADAUSUARIOYACONECTADO);
		m_stream->send(outMsg);
		return false;

	// Rechaza la conexion si el usuario ya murio durante esta partida.
	}else if( result == USERDEAD){
		printf ("Conexion rechazada, user esta muerto. %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = SSTR(CONEXIONRECHAZADAUSUARIOMUERTO);
		m_stream->send(outMsg);
		return false;

	// Acepta la conexion si no se da ninguna de las condiciones anteriores.
	}else{
		printf ("Conexion aceptada %s:%d \n", m_stream->getPeerIP().c_str(), m_stream->getPeerPort());
		std::string outMsg = SSTR(CONEXIONACEPTADA);
		size_t len = m_stream->send(outMsg);
		if(len<=0){
			return false;
		}

		return true;
	}
}


// Metodo encargado de enviar las modificaciones en los objetos del modelo.
bool ConnectionHandler::enviarObjetos(){

	std::string outMessage;
	int len;

	for(std::map<std::string, ObjetoModelo *>::iterator it = controlador->modelo.objetos.begin();
			it != controlador->modelo.objetos.end(); it++ ){

		// Si el objeto ya no existe, lo saltea.
		if ((*it).second == NULL) continue;
		// Si el objeto no fue modificado, lo saltea.
		if (!(*it).second->modificado) continue;

		// Si el objeto esta marcado para destruir, marca que ya reconocio su destruccion.
		if ((*it).second->paraDestruir) (*it).second->reconocerDestruccion++;

		outMessage = SSTR( MODIFICACIONMODELO << SEPARADORCAMPOS << (*it).second->serializar() );
		len = m_stream->send(outMessage);
		if (len <= 0) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}
	}

	return true;
}

// Metodo encargado de enviar las modificaciones en los personajes del modelo.
bool ConnectionHandler::enviarPersonajes(){

	std::string outMessage;
	int len;

	for(std::map<std::string, Personaje *>::iterator it = controlador->modelo.personajes.begin();
			it != controlador->modelo.personajes.end(); it++ ){

		// Si el objeto ya no existe, lo saltea.
		if ((*it).second == NULL) continue;
		// Si el objeto no fue modificado, lo saltea.
		if (!(*it).second->modificado) continue;

		// Si el objeto esta marcado para destruir, marca que ya reconocio su destruccion.
		if ((*it).second->paraDestruir) (*it).second->reconocerDestruccion++;

		outMessage = SSTR( MODIFICACIONMODELO << SEPARADORCAMPOS << (*it).second->serializar() );
		len = m_stream->send(outMessage);
		if (len <= 0) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}
	}

	return true;
}

// Metodo encargado de enviar las modificaciones en los enemigos del modelo.
bool ConnectionHandler::enviarEnemigos(){

	std::string outMessage;
	int len;

	for(std::map<std::string, Enemigo *>::iterator it = controlador->modelo.enemigos.begin();
			it != controlador->modelo.enemigos.end(); it++ ){

		// Si el objeto ya no existe, lo saltea.
		if ((*it).second == NULL) continue;
		// Si el objeto no fue modificado, lo saltea.
		if (!(*it).second->modificado) continue;

		// Si el objeto esta marcado para destruir, marca que ya reconocio su destruccion.
		if ((*it).second->paraDestruir) (*it).second->reconocerDestruccion++;

		outMessage = SSTR( MODIFICACIONMODELO << SEPARADORCAMPOS << (*it).second->serializar() );
		len = m_stream->send(outMessage);
		if (len <= 0) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}
	}

	return true;
}

// Metodo encargado de enviar las modificaciones en el estado del juego.
bool ConnectionHandler::enviarEstado(){

	std::string outMessage;
	int len;

	for(int i = 1; i <= 4; i++){
		if (controlador->estado.jugadorExiste(i)){
			outMessage = SSTR( MODIFICACIONESTADO << SEPARADORCAMPOS << controlador->estado.obtenerJugador(i)->serializar() );
			len = m_stream->send(outMessage);
			if (len <= 0) {
				// Desbloquea el controlador.
				controlador->desbloquear();
				return false;
			}
		}
	}

	return true;
}

// Espera a que los demas jugadores respondan.
bool ConnectionHandler::esperar(){

	std::string outMessage = SSTR(ESPERANDO), inMessage = SSTR(ESPERANDO);
	int len;

	// Espera una respuesta del jugador.
	while(inMessage != SSTR(LISTO) && inMessage != SSTR(SALIR)) {
		usleep(20000);
		len = m_stream->receive(inMessage);
		if (len<= 0) return false;
	}

	// Analiza la respuesta del jugador.
	if (inMessage == SSTR(LISTO)) controlador->estado.obtenerJugador(username)->estado = Jugador::CONECTADO;
	if (inMessage == SSTR(SALIR)) return false;

	// Espera a que los demas jugadores den una respuesta.
	while (!controlador->estado.puedeEmpezar()){
		len = m_stream->send(outMessage);
		if (len <= 0) return false;
	}

	// Informa que el juego esta listo para comenzar.
	outMessage = SSTR(LISTO);
	len = m_stream->send(outMessage);
	if (len <= 0) return false;

	return true;
}

// Loop que representa la comunicacion entre cliente y servidor a lo largo de una partida:
// Se simula el nivel y, al finalizarlo, se espera a que el cliente decida pasar de nivel.
bool ConnectionHandler::loopPartida(){

	bool quit = false;
	std::string outMessage = SSTR(FINDELNIVEL);
	ssize_t len;

	// Espera a que se inicialize el modelo.
	while (controlador->estado.estado != JUGANDO) usleep(20000);

	// Simula la partida.
	while (controlador->estado.estado != JUEGOTERMINADO){

		// Espera a que el jugador acepte empezar el nivel.
		quit = !esperar();
		if (quit) return false;

		// Simula el nivel.
		quit = !loopNivel();
		if (quit) return false;

		// Notifica al jugador del fin de nivel/juego segun corresponda.
		if (controlador->estado.estado == NIVELTERMINADO) outMessage = SSTR(FINDELNIVEL);
		else if (controlador->estado.estado == JUEGOTERMINADO) outMessage = SSTR(FINDELJUEGO);

		len = m_stream->send(outMessage);
		if (len <= 0) return false;

	}

	return true;
}

// Loop que representa la comunicacion entre cliente y servidor a lo largo de un nivel:
// se reciben eventos y luego se envia la pantalla a renderear para representar el estado
// actual de juego. Se rompe cuando se pierde la conexion, o el nivel finaliza.
// retorno: false si se pierde la conexion, true si el nivel finalizo sin problemas.
bool ConnectionHandler::loopNivel(){

	bool quit = false;
	std::string outMessage;
	ssize_t len;

	// Espera a que se inicialize el modelo.
	while (controlador->estado.estado != JUGANDO) usleep(20000);

	// Antes de empezar el nivel, envia el tamanio del mapa.
	Vector2D tamanio = LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa;
	outMessage = SSTR(TAMANIOMAPA << SEPARADORCAMPOS << tamanio.x << SEPARADORDATOS << tamanio.y);

	m_stream->send(outMessage);

	while ( controlador->estado.estado != NIVELTERMINADO && controlador->estado.estado != JUEGOTERMINADO ){

		// Recibe todos los eventos sucedidos en el cliente.
		quit = !recibirEventos();
		if (quit) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}

		// Bloquea el controlador de juego para que no pueda modificarse el modelo
		// mientras se envia.
		controlador->bloquear();

		// Obtiene la representacion serializada del estado, y la envia.
		quit = !enviarEstado();
		if (quit) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}

		// Obtiene la representacion serializada del modelo, y la envia.
		// Para esto recorre uno por uno los objetos del modelo, verificando si
		// estos fueron modificados.

		// Objetos
		quit = !enviarObjetos();
		if (quit) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}

		// Personajes
		quit = !enviarPersonajes();
		if (quit) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}

		// Enemigos
		quit = !enviarEnemigos();
		if (quit) {
			// Desbloquea el controlador.
			controlador->desbloquear();
			return false;
		}

		// Desbloquea el controlador.
		controlador->desbloquear();

		outMessage = SSTR(NOMASMODIFICACIONES);
		len = m_stream->send(outMessage);
		if (len <= 0) return false;

		usleep(20000);
	}

	return true;
}

// Recibe todos los eventos sucedidos en el cliente desde la ultima vez que se llamo al metodo.
// Los almacena en la cola de notificaciones para ser procesados por el thread de simulacion.
// retorno: false si se corto la comunicacion, true en caso contrario.
bool ConnectionHandler::recibirEventos(){

	std::string mensajeEntrante;
	bool finEventos = false;

	while (!finEventos){
		int len = m_stream->receive(mensajeEntrante);
		if (len <= 0) return false;
		MensajeParseado mensaje = parser.parsearTexto(mensajeEntrante);

		switch(mensaje.tipo){
		case EVENTOIZQUIERDA:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJEIZQUIERDA, this);
			break;
		case EVENTODERECHA:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJEDERECHA, this);
			break;
		case EVENTOQUIETO:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(DETENERMOVIMIENTOPERSONAJE, this);
			break;
		case EVENTOSALTAR:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJESALTO, this);
			break;
		case EVENTOFINSALTAR:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(DETENERMOVIMIENTOPERSONAJESALTO, this);
			break;
		case EVENTOATAQUE:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJEATAQUE, this);
			break;
		case EVENTOFINATAQUE:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(DETENERMOVIMIENTOPERSONAJEATAQUE, this);
			break;
		case NOMASEVENTOS:
			finEventos = true;
			break;
		default:
			break;
		}
	}

	return true;
}

// Espera una respuesta por parte del jugador.
bool ConnectionHandler::esperarRespuesta(){

	std::string outMessage = SSTR(ESPERANDO), inMessage = SSTR(ESPERANDO);
	int len;

	// Espera una respuesta del jugador.
	while(inMessage != SSTR(LISTO) && inMessage != SSTR(SALIR)) {
		usleep(20000);
		len = m_stream->receive(inMessage);
		if (len<= 0) return false;
	}

	// Analiza la respuesta del jugador.
	if (inMessage == SSTR(LISTO)) {
		controlador->estado.obtenerJugador(username)->estado = Jugador::CONECTADO;
	}
	if (inMessage == SSTR(SALIR)) return false;

	return true;
}

void * ConnectionHandler::run() {

	printf("Conexion con: %s:%d establecida.\n", m_stream->getPeerIP().c_str() , m_stream->getPeerPort());

	// Valida las credenciales del cliente, lo conecta y espera a que empiece el juego; o rechaza la
	// conexion y termina.
	bool quit = !protocoloLogIn();
	if (quit) return NULL;


	// Loop de partidas. Mientras el usuario elija permanecer conectado, jugara una partida
	// tras otra.
	while (!quit){


		quit = !esperarPorMasJugadores();
		if (quit) continue;

		// Loop que representa una partida: recibir eventos y enviar pantalla a renderear.
		// Se rompe cuando se pierde la conexion, o la partida finaliza.
		quit = !loopPartida();
		if (quit) continue;

		// Espera una respuesta por parte del jugador.
		quit = !esperarRespuesta();
		if(quit) continue;

	}

	// Informa que se desconecto el jugador.
	if(controlador->estado.jugadorExiste(username)){
		if(controlador->estado.estado == ESPERANDOCONEXIONES || controlador->estado.estado == JUEGOTERMINADO){
			controlador->estado.eliminarJugador(username);
		}
		else controlador->estado.obtenerJugador(username)->estado = Jugador::DESCONECTADO;
	}

	printf("Conexion con: %s:%d terminada.\n", m_stream->getPeerIP().c_str() , m_stream->getPeerPort());

	delete m_stream;

	return NULL;

}

