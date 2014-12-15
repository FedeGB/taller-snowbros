/*
 * ControladorJuego.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef CONTROLADORJUEGO_H_
#define CONTROLADORJUEGO_H_

#include "../interfaces/Notificable.h"
#include "estadoJuego/EstadoJuego.h"
#include "modeloJuego/ModeloJuego.h"

class Jugador;
class ObjetoModelo;

class ControladorJuego: public Notificable {
public:

	// Crea un controlador de juego.
	ControladorJuego();

	// Destruye el controlador de juego.
	virtual ~ControladorJuego();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Establece los valores iniciales y configura los modulos que conforman
	// el controlador.
	void inicializar();

	// Actualiza el juego.
	void actualizar();

	// Destruye el modelo y el estado de juego para asegurar un correcto finalizado
	// de los modulos involucrados.
	void limpiar();

	// Bloquea el controlador.
	void bloquear();

	// Desbloquea el controlador.
	void desbloquear();


	EstadoJuego estado;
	ModeloJuego modelo;

private:

	// Hago 'thread safe' al controlador.
	pthread_mutex_t m_mutex;
    pthread_cond_t m_condv;
};

#endif /* CONTROLADORJUEGO_H_ */
