/*
 * SorpresaNieveMaLejos.h
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#ifndef SORPRESANIEVEMALEJOS_H_
#define SORPRESANIEVEMALEJOS_H_

#include "Sorpresa.h"

class SorpresaNieveMaLejos: public Sorpresa {
public:
	SorpresaNieveMaLejos();
	virtual ~SorpresaNieveMaLejos();

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* SORPRESANIEVEMALEJOS_H_ */
