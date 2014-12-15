/*
 * Ladrillo.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef LADRILLO_H_
#define LADRILLO_H_

#include "ObjetoInanimado.h"

class Ladrillo: public ObjetoInanimado {
public:
	Ladrillo();
	virtual ~Ladrillo();

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* LADRILLO_H_ */
