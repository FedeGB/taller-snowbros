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
};

#endif /* OBJETOJUEGO_H_ */
