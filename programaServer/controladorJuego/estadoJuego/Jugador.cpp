/*
 * Jugador.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "Jugador.h"

#include "../ControladorJuego.h"

// Crea un nuevo jugador.
Jugador::Jugador(){
	personaje = NULL;
	estadoJuego = ESPERANDOCONEXIONES;
	numero = 0;
	puntaje = 0;
	estado = NOEXISTE;
	vidas = 0;
}

// Destruye un jugador.
Jugador::~Jugador(){

}

// Crea un jugador nuevo en base a los datos serializados.
Jugador * Jugador::deserializar(std::string serializado){

	Jugador * jugador = new Jugador;

	// Separa el los campos del mensaje.
	std::vector<std::string> buff;
	split(buff, serializado, SEPARADORDATOS, no_empties);

	// Salteo buff[0] pues dice TIPOJUGADOR.
	jugador->nombre = buff[1];
	jugador->numero = atoi(buff[2].c_str());
	jugador->vidas = atoi(buff[3].c_str());
	jugador->puntaje = atoi(buff[4].c_str());
	jugador->estado = (estado_t) atoi(buff[5].c_str());
	jugador->estadoJuego = (estado_juego_t) atoi(buff[6].c_str());

	return jugador;
}

// Serializa la informacion de un jugador para su almacenamiento.
std::string Jugador::serializar(){

	std::string buff;

	buff = SSTR(TIPOJUGADOR << SEPARADORDATOS << nombre << SEPARADORDATOS << numero << SEPARADORDATOS << vidas
			<< SEPARADORDATOS << puntaje << SEPARADORDATOS << estado << SEPARADORDATOS << estadoJuego);

	return buff;
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void Jugador::notificar(tipo_notificacion_t notificacion){

}

// Inicializa al jugador.
void Jugador::inicializar(){

}

// Elimina lo que sea necesario.
void Jugador::limpiar(){

}

// Actualiza la informacion del jugador para poder dibujarla.
void Jugador::actualizar(){

	vidas = personaje->salud;
	puntaje = personaje->puntaje;
	if (vidas < 1) estado = ESPERANDORESPUESTA;
}

