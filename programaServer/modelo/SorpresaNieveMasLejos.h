/*
 * SorpresaNieveMasLejos.h
 *
 *  Created on: 21/11/2014
 *      Author: manuel
 */

#ifndef SORPRESANIEVEMASLEJOS_H_
#define SORPRESANIEVEMASLEJOS_H_

#include "Sorpresa.h"

class SorpresaNieveMasLejos: public Sorpresa{
public:
	SorpresaNieveMasLejos(){
		activeSprite = SORPRESAnieveLejos;
	}
	virtual ~SorpresaNieveMasLejos(){}

	virtual void aplicarAlPJ(Personaje* pj) {
		pj->nieveMasLejos();
	}
};



#endif /* SORPRESANIEVEMASLEJOS_H_ */
