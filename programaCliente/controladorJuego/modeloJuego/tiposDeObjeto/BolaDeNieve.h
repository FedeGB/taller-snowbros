/*
 * BolaDeNieve.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef BOLADENIEVE_H_
#define BOLADENIEVE_H_

#include "ObjetoInanimado.h"

class BolaDeNieve: public ObjetoInanimado {
public:
	BolaDeNieve();
	virtual ~BolaDeNieve();

protected:

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* BOLADENIEVE_H_ */
