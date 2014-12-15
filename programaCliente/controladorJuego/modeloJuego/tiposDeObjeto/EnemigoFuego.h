/*
 * EnemigoFuego.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef ENEMIGOFUEGO_H_
#define ENEMIGOFUEGO_H_

#include "Enemigo.h"

class EnemigoFuego: public Enemigo {
public:
	EnemigoFuego();
	virtual ~EnemigoFuego();

protected:

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* ENEMIGOFUEGO_H_ */
