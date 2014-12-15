/*
 * ControladorJuego.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "ControladorJuego.h"

#include "estadoJuego/Jugador.h"
#include "modeloJuego/ObjetoModelo.h"

// Crea un controlador de juego.
ControladorJuego::ControladorJuego(){
	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_condv, NULL);
}

// Destruye el controlador de juego.
ControladorJuego::~ControladorJuego(){
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_condv);
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ControladorJuego::notificar(tipo_notificacion_t notificacion){

}

// Establece los valores iniciales y configura los modulos que conforman
// el controlador.
void ControladorJuego::inicializar(){

	estado.inicializar();
	modelo.inicializar();
}

// Actualiza el juego.
void ControladorJuego::actualizar(){

	estado.actualizar();
	modelo.actualizar(estado.cantidadOnline());
}

// Destruye el modelo y el estado de juego para asegurar un correcto finalizado
// de los modulos involucrados.
void ControladorJuego::limpiar(){

	estado.limpiar();
	modelo.limpiar();
}

// Bloquea el controlador.
void ControladorJuego::bloquear(){
	pthread_mutex_lock(&m_mutex);
}

// Desbloquea el controlador.
void ControladorJuego::desbloquear(){
	pthread_mutex_unlock(&m_mutex);
}

