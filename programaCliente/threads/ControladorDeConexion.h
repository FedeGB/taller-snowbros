/*
 * ControladorDeConexion.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef CONTROLADORDECONEXION_H_
#define CONTROLADORDECONEXION_H_

#include "Thread.h"
#include "../ControladorModificaciones.h"
#include "../controladorJuego/estadoJuego/Jugador.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/Personaje.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/EnemigoEstandar.h"
#include "../sockets/TCPConnector.h"
#include "../sockets/TCPStream.h"
#include "../parserMensajes/protocoloServidorCliente.h"
#include "../parserMensajes/ParserMensajes.h"
#include "../parserMensajes/MensajeParseado.h"


class ControladorDeConexion: public Thread, public Notificable {
public:

	// Crea un thread controlador de conexion.
	ControladorDeConexion();

	// Destruye el controlador.
	virtual ~ControladorDeConexion();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Establece la interfaz de comunicacion entre el thread y su padre, para comunicar
	// las modificaciones necesarias al mundo simulado.
	void establecerControladorModificaciones(ControladorModificaciones * modificaciones);

	// 'Main' del thread. Se encarga de establecer una conexion con el servidor
	// y hacer un updateo constante de la informacion necesaria para renderear
	// la pantalla del juego.
	virtual void * correr();

private:

	// Procesa la respuesta del servidor ante el intento de iniciar sesion.
	void procesarRespuestaInicioDeSesion(std::string respuesta);

	// Establece una conexion con el servidor, e intenta validar la
	// informacion de inicio de sesion con el mismo. en caso de tener exito,
	// retorna para iniciar la espera de los demas jugadores. Sino, se
	// desconecta y notifica que fallo la conexion.
	void iniciarSesion();

	// Espera a que se ocupen todos los lugares disponibles para iniciar el juego.
	void esperarPorMasJugadores();

	// Carga el proximo nivel.
	void cargarNivel();

	// Envia todos los eventos pendientes desde la ultima llamada a esta funcion.
	void enviarEventos();

	// Recibe todas las modificaciones
	void recibirModificaciones();

	// Espera a que el jugador decida inicia el proximo nivel / elija si
	// jugar una nueva partida.
	void esperar();

	// Realiza la comunicacion entre cliente y servidor a lo largo de un nivel.
	void simularNivel();

	// Realiza la comunicacion entre cliente y servidor a lo largo de un juego.
	// Al finalizar el juego, envia una notificacion para cambiar el estado de juego
	// a FINDEJUEGO.
	void simularJuego();

	// Espera una respuesta por parte del jugador, y la envia al servidor.
	// Si la respuesta fue dejar de jugar, envia una notificacion para desconectarse
	// del servidor.
	void esperarRespuesta();

	// Objeto que sirve de interfaz entre el thread de comunicacion y el de rendereo.
	ControladorModificaciones * modificaciones;

	// Canal de comunicacion con el servidor.
	TCPStream * stream;

	// Indica si se debe cerrar la comunicacion con el servidor.
	bool salir;
	bool finNivel;
	bool finJuego;
	bool esperando, jugarDeNuevo;
	bool moviendoIzquierda, moviendoDerecha, saltando, atacando;

	// Procesa los mensajes recibidos.
	ParserMensajes parser;

};

#endif /* CONTROLADORDECONEXION_H_ */
