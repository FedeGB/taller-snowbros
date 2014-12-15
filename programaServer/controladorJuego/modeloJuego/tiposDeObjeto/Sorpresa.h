/*
 * Sorpresa.h
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#ifndef SORPRESA_H_
#define SORPRESA_H_

#include "ObjetoInanimado.h"
#include "Personaje.h"

class Sorpresa: public ObjetoInanimado {
public:
	Sorpresa();
	virtual ~Sorpresa();

	virtual void aplicarAlPJ(Personaje* pj) = 0;
};

#endif /* SORPRESA_H_ */
