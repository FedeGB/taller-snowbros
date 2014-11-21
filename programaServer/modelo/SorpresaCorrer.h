/*
 * SorpresaCorrer.h
 *
 *  Created on: 21/11/2014
 *      Author: manuel
 */

#ifndef SORPRESACORRER_H_
#define SORPRESACORRER_H_

#include "Sorpresa.h"

class SorpresaCorrer: public Sorpresa{
public:

	SorpresaCorrer(){
		activeSprite = SORPRESAcorrer;
	}
	virtual ~SorpresaCorrer(){}

	virtual void aplicarAlPJ(Personaje* pj) {
		pj->correrMasRapido();
	}
};



#endif /* SORPRESACORRER_H_ */
