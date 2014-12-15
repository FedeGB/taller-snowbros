/*
 * SorpresaCorrer.h
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#ifndef SORPRESACORRER_H_
#define SORPRESACORRER_H_

#include "Sorpresa.h"

class SorpresaCorrer: public Sorpresa {
public:
	SorpresaCorrer();
	virtual ~SorpresaCorrer();

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();

};

#endif /* SORPRESACORRER_H_ */
