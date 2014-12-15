/*
 * protocoloServidorCliente.h
 *
 *  Created on: Dec 7, 2014
 *      Author: rodrizapico
 */

#ifndef PROTOCOLOSERVIDORCLIENTE_H_
#define PROTOCOLOSERVIDORCLIENTE_H_

enum codigo_protocolo_t {

// Posibles respuestas del servidor ante el intento de iniciar sesion por parte del cliente.

	// "Conexion rechazada. Motivo: el servidor se encuentra lleno."
	CONEXIONRECHAZADASERVIDORLLENO,
	// "Conexion rechazada. Motivo: el usuario especificado ya se encuentra conectado."
	CONEXIONRECHAZADAUSUARIOYACONECTADO,
	// "Conexion rechazada. Motivo: el usuario especificado ya ha perdido durante la partida actual."
	CONEXIONRECHAZADAUSUARIOMUERTO,
	// "Conexion aceptada."
	CONEXIONACEPTADA,


// Posibles mensajes enviados por el servidor mientras se encuentra esperando mas jugadores.

	// "Se ha recibido la informacion de un nuevo jugador."
	NUEVOJUGADOR, // + datos del jugador.
	// "Esperando que se conecten mas jugadores."
	ESPERANDO,
	// "Se lleno el servidor, inicia el juego."
	INICIAJUEGO,


// Posibles mensajes enviados por el servidor mientras se encuentra cargando el mapa.

	// "Se ha recibido un nuevo elemento del mapa."
	ELEMENTOMAPA, // + datos del elemento.
	// "Se ha finalizado de cargar el mapa."
	FINMAPA,
	// "El tamanio del mapa es.."
	TAMANIOMAPA, // + datos del tamanio.


// Posibles mensajes enviados por el cliente en el loop principal del juego.

	// "Se ha apretado la tecla de saltar."
	EVENTOSALTAR,
	// "Se ha soltado la tecla de saltar."
	EVENTOFINSALTAR,
	// "Se ha apretado la tecla de mover izquierda."
	EVENTOIZQUIERDA,
	// "Se han soltado ambas teclas de movimiento."
	EVENTOQUIETO,
	// "Se ha apretado la tecla de mover derecha."
	EVENTODERECHA,
	// "Se ha apretado la tecla de ataque."
	EVENTOATAQUE,
	// "Se ha soltado la tecla de ataque."
	EVENTOFINATAQUE,
	// "No quedan eventos para informar."
	NOMASEVENTOS,

// Posibles mensajes enviados por el servidor en el loop principal de juego.

	// "Ha habido una modificacion en el modelo."
	MODIFICACIONMODELO, // + informacion del cambio
	// "Ha habido una modificacion en el estado de juego."
	MODIFICACIONESTADO, // + informacion del cambio
	// "No quedan modificaciones para informar."
	NOMASMODIFICACIONES,
	// "Se termino el nivel."
	FINDELNIVEL,
	// "Se termino el juego."
	FINDELJUEGO,


// Posibles mensajes enviados por el cliente luego de finalizar el juego.

	// "Volver a jugar."
	LISTO,
	// "Salir del juego."
	SALIR,

};

// Separador de campos en un mensaje.

#define SEPARADORCAMPOS "%"
#define SEPARADORDATOS "&"


// Tipos de datos posibles.

enum tipos_datos_t{
	TIPOJUGADOR,
	TIPOPERSONAJE,
	TIPOENEMIGOESTANDAR,
	TIPOENEMIGOFUEGO,
	TIPOLADRILLO,
	TIPOBOLADEFUEGO,
	TIPOBOLADENIEVE,
	TIPOBOLAENEMIGO,
	TIPOPELOTADENIEVE,
	TIPOLAGUNA,
	TIPOAGUJERO,
	TIPOSORPRESACORRER,
	TIPOSORPRESANIEVEMASLEJOS,
	TIPOSORPRESANIEVEMASPOTENTE,
};

#endif /* PROTOCOLOSERVIDORCLIENTE_H_ */
