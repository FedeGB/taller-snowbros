/*
 * ConnectionHandler.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

#include "TCPStream.h"
//#include "../threads/ColaTrabajo.h"
#include "../threads/Thread.h"
#include "../threads/ThreadSafeList.h"
#include "../threads/ConditionVariable.h"
#include "../interfaces/EnviadorNotificaciones.h"
#include "../parserMensajes/ParserMensajes.h"
#include "../parserMensajes/protocoloServidorCliente.h"
#include "../controladorJuego/ControladorJuego.h"
#include "../controladorJuego/estadoJuego/Jugador.h"

#define OK 0
#define SERVERFULL 1
#define USERONLINE 2
#define USERDEAD 3

class ConnectionHandler : public EnviadorNotificaciones, public Thread{
private:
    TCPStream * m_stream;

    // Intenta conectar un usuario al servidor, ya sea alguien que
    // ya estaba en la partida y se habia desconectado, o alguien nuevo.
    // username: el usuario a intentar conectarse.
    // return: numero de conexion si esta fue exitosa,
    // SERVERFULL si no hay mas lugar en el servidor,
    // USERONLINE si el usuario ya se encuentra conectado.
    int logIn(std::string username);

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
    bool protocoloLogIn();

    // Bloquea hasta que se hayan conectado (y validado) todos los clientes requeridos
    // por el servidor.
    bool esperarPorMasJugadores();

    // Loop que representa la comunicacion entre cliente y servidor a lo largo de una partida:
    // Se simula el nivel y, al finalizarlo, se espera a que el cliente decida pasar de nivel.
    bool loopPartida();

    // Loop que representa la comunicacion entre cliente y servidor a lo largo de un nivel:
    // se reciben eventos y luego se envia la pantalla a renderear para representar el estado
    // actual de juego. Se rompe cuando se pierde la conexion, o el nivel finaliza.
    // retorno: false si se pierde la conexion, true si el nivel finalizo sin problemas.
    bool loopNivel();

    // Recibe todos los eventos sucedidos en el cliente desde la ultima vez que se llamo al metodo.
    // Los almacena en la cola de notificaciones para ser procesados por el thread de simulacion.
    // retorno: false si se corto la comunicacion, true en caso contrario.
    bool recibirEventos();
/*
    // Informa al Jugador el resultado de la partida, y le pregunta si quiere seguir jugando.
    // En caso de que quiera seguir, se lo pone en espera para la siguiente partida.
    // En caso contrario, se lo quita de los usuarios del servidor y se desconecta.
    // retorno: true si decide seguir jugando, false en caso contrario; o si se desconecta.
    // NOTA: Esta funcion bloquea hasta que se llene el servidor. Al momento del retorno,
    // la partida ya ha comenzado.
    bool protocoloFinDePartida();
*/

    // Metodo encargado de enviar las modificaciones en los objetos del modelo.
    bool enviarObjetos();

    // Metodo encargado de enviar las modificaciones en los personajes del modelo.
    bool enviarPersonajes();

    // Metodo encargado de enviar las modificaciones en los enemigos del modelo.
    bool enviarEnemigos();

    // Metodo encargado de enviar las modificaciones en el estado del juego.
    bool enviarEstado();

    // Espera a que los demas jugadores respondan.
    bool esperar();

    // Espera una respuesta por parte del jugador.
    bool esperarRespuesta();

    ControladorJuego * controlador;
    ParserMensajes parser;

public:

    std::string username;

    ConnectionHandler(TCPStream * stream, ControladorJuego * controlador);
    void* run();
};

#endif /* CONNECTIONHANDLER_H_ */
