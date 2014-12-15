/*
 * Agujero.h
 *
 *  Created on: Dec 13, 2014
 *      Author: rodrizapico
 */

#ifndef AGUJERO_H_
#define AGUJERO_H_

#include "ObjetoInanimado.h"

class Agujero: public ObjetoInanimado {
public:
	Agujero();
	virtual ~Agujero();

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* AGUJERO_H_ */
