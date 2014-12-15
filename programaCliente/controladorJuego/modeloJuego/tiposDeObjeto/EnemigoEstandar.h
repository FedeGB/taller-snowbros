/*
 * EnemigoEstandar.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef ENEMIGOESTANDAR_H_
#define ENEMIGOESTANDAR_H_

#include "Enemigo.h"

class EnemigoEstandar: public Enemigo {
public:
	EnemigoEstandar();
	virtual ~EnemigoEstandar();

protected:

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* ENEMIGOESTANDAR_H_ */
