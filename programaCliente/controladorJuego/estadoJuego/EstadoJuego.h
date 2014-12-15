/*
 * EstadoJuego.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef ESTADOJUEGO_H_
#define ESTADOJUEGO_H_

#include <vector>
#include <cstddef>
#include "../../interfaces/Notificable.h"
#include "../../utiles/tipos.h"

class Jugador;

class EstadoJuego: public Notificable {
public:

	// Representacion del estado del juego actual: jugadores conectados, vidas
	// de cada jugador, puntaje, etcetera.
	EstadoJuego();

	// Destruye la representacion del estado de juego.
	virtual ~EstadoJuego();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Inicializa el estado del juego.
	void inicializar();

	// Actualiza el estado del juego.
	void actualizar();

	// Destruye el estado de juego para asegurar un correcto finalizado
	// de los modulos involucrados.
	void limpiar();

	// Dibuja la informacion de estado del juego en pantalla.
	void dibujar();

	friend class ControladorJuego;

private:

	std::vector<Jugador*> jugadores;
	estado_juego_t estado;
};

#endif /* ESTADOJUEGO_H_ */
