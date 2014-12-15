/*
 * EstadoJuego.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "EstadoJuego.h"

#include "Jugador.h"

// Representacion del estado del juego actual: jugadores conectados, vidas
// de cada jugador, puntaje, etcetera.
EstadoJuego::EstadoJuego(){
	estado = ESPERANDOCONEXIONES;
}

// Destruye la representacion del estado de juego.
EstadoJuego::~EstadoJuego(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void EstadoJuego::notificar(tipo_notificacion_t notificacion){

	if (notificacion == COMIENZODEJUEGO) {
		estado = JUGANDO;
	}
	if (notificacion == FINDEJUEGO) estado = JUEGOTERMINADO;
}

// Inicializa el estado del juego.
void EstadoJuego::inicializar(){

	// Reserva memoria para los 4 jugadores (como maximo).
	jugadores.reserve(4);

	// Inicializa los 4 jugadores.
	for(int i = 0; i < 4; i++){
		Jugador * jugadorTemp = new Jugador();
		jugadores[i] = jugadorTemp;
	}

	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);
}

// Actualiza el estado del juego.
void EstadoJuego::actualizar(){

}

// Destruye el estado de juego para asegurar un correcto finalizado
// de los modulos involucrados.
void EstadoJuego::limpiar(){

	// Inicializa los 4 jugadores.
	for(int i = 0; i < 4; i++){
		jugadores[i]->limpiar();
		delete jugadores[i];
		jugadores[i] = NULL;
	}

	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);
}

// Dibuja la informacion de estado del juego en pantalla.
void EstadoJuego::dibujar(){

	// Dibuja la informacion de los 4 jugadores.
	for(int i = 0; i < 4; i++){
		Jugador * jugadorADibujar = jugadores[i];
		// Si el jugador no existe, lo saltea.
		if (jugadorADibujar->estado == Jugador::NOEXISTE) continue;

		// Dibuja la informacion del jugador correspondiente.
		jugadorADibujar->dibujar();
	}
}
