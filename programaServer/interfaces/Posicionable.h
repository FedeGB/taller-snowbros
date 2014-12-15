/*
 * Posicionable.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef POSICIONABLE_H_
#define POSICIONABLE_H_

#include "Notificable.h"

class Posicionable: public Notificable {
public:
	virtual ~Posicionable(){};

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion){};

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto){};

	// Asigna una posicion en pantalla al elemento. Las coordenadas dadas son
	// en la escala de pantalla.
	virtual void asignarPosicion(int x, int y) = 0;

	// Asigna dimensiones del elemento. Las coordenadas dadas son en la escala
	// de pantalla.
	virtual void asignarDimensiones(int ancho, int alto) = 0;

	// Una vez asignadas la posicion y dimensiones, se debe llamar a este metodo,
	// encargado de inicializar el objeto a un estado valido para ser utilizado.
	virtual void inicializar() = 0;
};

#endif /* POSICIONABLE_H_ */
