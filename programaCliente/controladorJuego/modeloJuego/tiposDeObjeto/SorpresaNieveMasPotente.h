/*
 * SorpresaNieveMasPotente.h
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#ifndef SORPRESANIEVEMASPOTENTE_H_
#define SORPRESANIEVEMASPOTENTE_H_

#include "Sorpresa.h"

class SorpresaNieveMasPotente: public Sorpresa {
public:
	SorpresaNieveMasPotente();
	virtual ~SorpresaNieveMasPotente();

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();

};

#endif /* SORPRESANIEVEMASPOTENTE_H_ */
