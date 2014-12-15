/*
 * ControladorDeConexion.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "ControladorDeConexion.h"

#include <iostream>
#include <unistd.h>

#include "../utiles/Timer.h"

// Crea un thread controlador de conexion.
ControladorDeConexion::ControladorDeConexion(){
	modificaciones = NULL;
	stream = NULL;
	salir = false;
	finNivel = false;
	finJuego = false;
	esperando = true;
	jugarDeNuevo = false;
	moviendoIzquierda = moviendoDerecha = saltando = atacando = false;
}

// Destruye el controlador.
ControladorDeConexion::~ControladorDeConexion(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ControladorDeConexion::notificar(tipo_notificacion_t notificacion){

	if (notificacion == MOVERPERSONAJEIZQUIERDA) moviendoIzquierda = true;
	if (notificacion == MOVERPERSONAJEDERECHA) moviendoDerecha = true;
	if (notificacion == DETENERMOVIMIENTOPERSONAJEIZQUIERDA) moviendoIzquierda = false;
	if (notificacion == DETENERMOVIMIENTOPERSONAJEDERECHA) moviendoDerecha = false;
	if (notificacion == MOVERPERSONAJEATAQUE) atacando = true;
	if (notificacion == DETENERMOVIMIENTOPERSONAJEATAQUE) atacando = false;
	if (notificacion == MOVERPERSONAJESALTO) saltando = true;
	if (notificacion == DETENERMOVIMIENTOPERSONAJESALTO) saltando = false;
	if (notificacion == RESPUESTAVOLVERAJUGAR){
		esperando = false;
		jugarDeNuevo = true;
	}
	if (notificacion == RESPUESTASALIR){
		esperando = false;
		jugarDeNuevo = false;
	}
}

// Establece la interfaz de comunicacion entre el thread y su padre, para comunicar
// las modificaciones necesarias al mundo simulado.
void ControladorDeConexion::establecerControladorModificaciones(ControladorModificaciones * modificaciones){
	this->modificaciones = modificaciones;
}

// Procesa la respuesta del servidor ante el intento de iniciar sesion.
void ControladorDeConexion::procesarRespuestaInicioDeSesion(std::string respuesta){

	codigo_protocolo_t codigoRespuesta = (codigo_protocolo_t) atoi(respuesta.c_str());

	switch(codigoRespuesta){
	case CONEXIONRECHAZADASERVIDORLLENO:
		// TODO: mostrar un mensaje indicando el motivo.
		salir = true;
		break;
	case CONEXIONRECHAZADAUSUARIOYACONECTADO:
		// TODO: mostrar un mensaje indicando el motivo.
		salir = true;
		break;
	case CONEXIONRECHAZADAUSUARIOMUERTO:
		// TODO: mostrar un mensaje indicando el motivo.
		salir = true;
		break;
	case CONEXIONACEPTADA:
		// No es necesario hacer nada.
		break;
	default:
		break;
	}

}


// Establece una conexion con el servidor, e intenta validar la
// informacion de inicio de sesion con el mismo. en caso de tener exito,
// retorna para iniciar la espera de los demas jugadores. Sino, se
// desconecta y notifica que fallo la conexion.
void ControladorDeConexion::iniciarSesion(){

	// Conecto al servidor.
	TCPConnector * connector = new TCPConnector();
	stream =  connector->connect(LocalizadorDeServicios::obtenerInformacionPublica()->IP.c_str(),
			LocalizadorDeServicios::obtenerInformacionPublica()->puerto);
	if (!stream){
		std::cout << "Hubo un problema al conectar al servidor" << std::endl;
		salir = true;
		return;
	}

	std::string mensajeEntrante, mensajeSaliente;

	// Inicia la comunicacion enviando el nombre de usuario.
	mensajeSaliente = LocalizadorDeServicios::obtenerInformacionPublica()->nombreUsuario;

	int len = stream->send(mensajeSaliente);
	if (len <= 0){
		salir = true;
		return;
	}

	// Recibe la respuesta.
	len = stream->receive(mensajeEntrante);
	if (len <= 0) {
		salir = true;
		return;
	}

	procesarRespuestaInicioDeSesion(mensajeEntrante);
}

// Espera a que se ocupen todos los lugares disponibles para iniciar el juego.
void ControladorDeConexion::esperarPorMasJugadores(){

	std::string mensajeEntrante;
	bool finEspera = false;

	LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(ESPERAR);

	while (!finEspera){

		int len = stream->receive(mensajeEntrante);
		if (len <= 0) {
			salir = true;
			return;
		}

		MensajeParseado mensaje = parser.parsearTexto(mensajeEntrante);

		switch(mensaje.tipo){
		case NUEVOJUGADOR:{
			Jugador * jugador = Jugador::deserializar(mensaje.datos);
			modificaciones->agregarModificacion(jugador);
			break;
		}
		case INICIAJUEGO:
			std::cout << "empieza el juego " << std::endl;
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(COMIENZODEJUEGO);
			finEspera = true;
			break;
		case ESPERANDO:
			// No necesito hacer nada.
			break;
		default:
			break;
		}
	}

	LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(FINESPERAR);
}

// Carga el proximo nivel.
void ControladorDeConexion::cargarNivel(){

	std::string mensajeEntrante;
	bool finCarga = false;

	while (!finCarga){

		int len = stream->receive(mensajeEntrante);
		if (len <= 0) {
			salir = true;
			return;
		}

		MensajeParseado mensaje = parser.parsearTexto(mensajeEntrante);

		switch(mensaje.tipo){
		case ELEMENTOMAPA:{
			ObjetoModelo * objeto = ObjetoModelo::deserializar(mensaje.datos);
			modificaciones->agregarModificacion(objeto);
			break;
		}
		case FINMAPA:
			finCarga = true;
			break;
		default:
			break;
		}
	}
}

// Envia todos los eventos pendientes desde la ultima llamada a esta funcion.
void ControladorDeConexion::enviarEventos(){

	std::string mensajeSaliente;
	int len;

	if(moviendoIzquierda) {
		mensajeSaliente = SSTR(EVENTOIZQUIERDA);
		len = stream->send(mensajeSaliente);
		if (len <= 0) {
			salir = true;
			return;
		}
	}

	if(moviendoDerecha) {
		mensajeSaliente = SSTR(EVENTODERECHA);
		len = stream->send(mensajeSaliente);
		if (len <= 0) {
			salir = true;
			return;
		}
	}

	if (!moviendoDerecha && !moviendoIzquierda){
		mensajeSaliente = SSTR(EVENTOQUIETO);
		len = stream->send(mensajeSaliente);
		if (len <= 0) {
			salir = true;
			return;
		}
	}

	if(saltando) {
		mensajeSaliente = SSTR(EVENTOSALTAR);
		len = stream->send(mensajeSaliente);
		if (len <= 0) {
			salir = true;
			return;
		}
	} else {
		mensajeSaliente = SSTR(EVENTOFINSALTAR);
		len = stream->send(mensajeSaliente);
		if (len <= 0) {
			salir = true;
			return;
		}
	}

	if(atacando) {
		mensajeSaliente = SSTR(EVENTOATAQUE);
		len = stream->send(mensajeSaliente);
		if (len <= 0) {
			salir = true;
			return;
		}
	} else {
		mensajeSaliente = SSTR(EVENTOFINATAQUE);
		len = stream->send(mensajeSaliente);
		if (len <= 0) {
			salir = true;
			return;
		}
	}

	mensajeSaliente = SSTR(NOMASEVENTOS);
	len = stream->send(mensajeSaliente);
	if (len <= 0) {
		salir = true;
		return;
	}
}

// Recibe todas las modificaciones.
void ControladorDeConexion::recibirModificaciones(){

	std::string mensajeEntrante;
	bool finModificaciones = false;

	while (!finModificaciones){

		int len = stream->receive(mensajeEntrante);
		if (len <= 0) {
			salir = true;
			return;
		}

		MensajeParseado mensaje = parser.parsearTexto(mensajeEntrante);

		switch(mensaje.tipo){
		case MODIFICACIONMODELO:{
			ObjetoModelo * objeto = ObjetoModelo::deserializar(mensaje.datos);
			modificaciones->agregarModificacion(objeto);
			break;
		}
		case MODIFICACIONESTADO:{
			Jugador * jugador = Jugador::deserializar(mensaje.datos);
			modificaciones->agregarModificacion(jugador);
			break;
		}
		case NOMASMODIFICACIONES:
			finModificaciones = true;
			break;
		case FINDELNIVEL:
			std::cout << "fin del nivel recibido" << std::endl;
			finNivel = true;
			esperando = true;
			finModificaciones = true;
			break;
		case FINDELJUEGO:
			std::cout << "fin del juego recibido" << std::endl;
			finJuego = true;
			esperando = true;
			finModificaciones = true;
			break;
		case TAMANIOMAPA:{
			std::vector<std::string> buff;
			split(buff, mensaje.datos, SEPARADORDATOS, no_empties);
			LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.x = atoi(buff[0].c_str());
			LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.y = atoi(buff[1].c_str());
			return;
		}
		default:
			break;
		}
	}
}

// Espera a que el jugador decida inicia el proximo nivel / elija si
// jugar una nueva partida.
void ControladorDeConexion::esperar(){

	std::string mensajeSaliente = SSTR(LISTO);
	std::string mensajeEntrante = SSTR(ESPERANDO);
	int len;

	// Espera la respuesta del jugador.
	esperarRespuesta();

	// Si el jugador decidio jugar y sigue conectado, espera el input de los demas jugadores.
	if (salir) return;

	LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(ESPERAR);

	while (mensajeEntrante != SSTR(LISTO) && !salir) {
		len = stream->receive(mensajeEntrante);
		if (len <= 0) salir = true;
	}

	LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(FINESPERAR);

	finJuego = finNivel = esperando = false;
}

// Realiza la comunicacion entre cliente y servidor a lo largo de un nivel.
void ControladorDeConexion::simularNivel(){

	// Obtiene las dimensiones del mapa actual.
	recibirModificaciones();

	while(!finNivel && !finJuego){

		// Envia todos los eventos pendientes desde la ultima llamada a esta funcion.
		enviarEventos();
		if (salir) {
			return;
		}

		// Recibe todas las modificaciones
		recibirModificaciones();
		if (salir) {
			return;
		}
	}

	if (finNivel) LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(FINDENIVEL);
	if (finJuego) LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(FINDEJUEGO);
}

// Realiza la comunicacion entre cliente y servidor a lo largo de un juego.
// Al finalizar el juego, envia una notificacion para cambiar el estado de juego
// a FINDEJUEGO.
void ControladorDeConexion::simularJuego(){

	// Espera a que se ocupen todos los lugares disponibles para iniciar el juego.
	esperarPorMasJugadores();
	if (salir) return;

	LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(FINDENIVEL);
	finJuego = finNivel = false;

	while(!finJuego){

		// Espera que el jugador decida iniciar el nivel.
		esperar();
		if(salir) return;

		// Realiza la comunicacion entre cliente y servidor a lo largo de un nivel.
		simularNivel();
		if (salir) return;
	}
}

// Espera una respuesta por parte del jugador, y la envia al servidor.
// Si la respuesta fue dejar de jugar, envia una notificacion para desconectarse
// del servidor.
void ControladorDeConexion::esperarRespuesta(){

	std::string mensajeSaliente = SSTR(LISTO);
	std::string mensajeEntrante = SSTR(ESPERANDO);
	int len;

	// Espera input del usuario.
	while (esperando) {
		usleep(20000);
		mensajeSaliente = SSTR(ESPERANDO);
		len = stream->send(mensajeSaliente);
		if (len <= 0) salir = true;
	}

	esperando = true;

	// Verifica la respuesta del usuario.
	if (jugarDeNuevo) mensajeSaliente = SSTR(LISTO);
	else {
		mensajeSaliente = SSTR(SALIR);
		salir = true;
	}

	len = stream->send(mensajeSaliente);
	if (len <= 0) salir = true;

}

// 'Main' del thread. Se encarga de establecer una conexion con el servidor
// y hacer un updateo constante de la informacion necesaria para renderear
// la pantalla del juego.
void * ControladorDeConexion::correr(){

	// Subscribe a notificaciones: desea recibir eventos de teclado relacionados
	// con el movimiento del personaje.
	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	// Establece una conexion con el servidor, e intenta validar la
	// informacion de inicio de sesion con el mismo. en caso de tener exito,
	// retorna para iniciar la espera de los demas jugadores. Sino, se
	// desconecta y notifica que fallo la conexion.
	iniciarSesion();

	while (!salir) {

		// Realiza la comunicacion entre cliente y servidor a lo largo de un juego.
		// Al finalizar el juego, envia una notificacion para cambiar el estado de juego
		// a FINDEJUEGO.
		simularJuego();
		if (salir) break;

		// Espera una respuesta por parte del jugador, y la envia al servidor.
		// Si la respuesta fue dejar de jugar, envia una notificacion para desconectarse
		// del servidor.
		esperarRespuesta();
		if (salir) break;

	}

	// No desea recibir mas notificaciones.
	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);

	std::cout << "coneccion cerrada con servidor." << std::endl;

	return NULL;
}
