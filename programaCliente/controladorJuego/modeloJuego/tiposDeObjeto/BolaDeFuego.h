/*
 * BolaDeFuego.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef BOLADEFUEGO_H_
#define BOLADEFUEGO_H_

#include "ObjetoInanimado.h"

class BolaDeFuego: public ObjetoInanimado {
public:
	BolaDeFuego();
	virtual ~BolaDeFuego();

protected:

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* BOLADEFUEGO_H_ */
