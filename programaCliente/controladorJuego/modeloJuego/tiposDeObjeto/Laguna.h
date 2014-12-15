/*
 * Laguna.h
 *
 *  Created on: Dec 13, 2014
 *      Author: rodrizapico
 */

#ifndef LAGUNA_H_
#define LAGUNA_H_

#include "ObjetoInanimado.h"

class Laguna: public ObjetoInanimado {
public:
	Laguna();

	virtual ~Laguna();

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* LAGUNA_H_ */
