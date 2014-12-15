/*
 * ObjetoJuego.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef OBJETOJUEGO_H_
#define OBJETOJUEGO_H_

#include "../interfaces/Notificable.h"

class ControladorJuego;

class ObjetoJuego: public Notificable {
public:
	virtual ~ObjetoJuego(){};

	// Aplica una modificacion.
	virtual void aplicarModificacion(ControladorJuego * juego) = 0;
};

#endif /* OBJETOJUEGO_H_ */
