/*
 * PelotaDeNieve.h
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#ifndef PELOTADENIEVE_H_
#define PELOTADENIEVE_H_

#include "ObjetoInanimado.h"

class PelotaDeNieve: public ObjetoInanimado {
public:
	PelotaDeNieve();
	virtual ~PelotaDeNieve();

protected:

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* PELOTADENIEVE_H_ */
