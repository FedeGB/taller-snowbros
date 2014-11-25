/*
 * BolaEnemigo.h
 *
 *  Created on: 24/11/2014
 *      Author: coco
 */

#ifndef BOLAENEMIGO_H_
#define BOLAENEMIGO_H_

#include "../utiles/tipos.h"
#include "../modelo/formas/Circulo.h"

class BolaEnemigo: public Circulo {
public:
	BolaEnemigo();
	virtual ~BolaEnemigo();
	sprite_t activeSprite;

};

#endif /* BOLAENEMIGO_H_ */
