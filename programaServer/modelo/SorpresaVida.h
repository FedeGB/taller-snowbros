/*
 * SorpresaVida.h
 *
 *  Created on: 21/11/2014
 *      Author: manuel
 */

#ifndef SORPRESAVIDA_H_
#define SORPRESAVIDA_H_

#include "Sorpresa.h"
#include "../utiles/tipos.h"

class SorpresaVida: public Sorpresa{
public:
	SorpresaVida(){
		activeSprite = SORPRESAvida;
	}
	virtual ~SorpresaVida(){}

	virtual void aplicarAlPJ(Personaje* pj) {
		pj->agregarVida();
	}
};


#endif /* SORPRESAVIDA_H_ */
