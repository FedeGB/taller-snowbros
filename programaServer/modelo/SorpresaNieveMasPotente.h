/*
 * SorpresaNieveMasPotente.h
 *
 *  Created on: 21/11/2014
 *      Author: manuel
 */

#ifndef SORPRESANIEVEMASPOTENTE_H_
#define SORPRESANIEVEMASPOTENTE_H_

#include "../utiles/tipos.h"
#include "Sorpresa.h"

class SorpresaNieveMasPotente: public Sorpresa{
public:
	SorpresaNieveMasPotente(){
		activeSprite = SORPRESAnieveMasPotente;
	}
	virtual ~SorpresaNieveMasPotente(){}

	virtual void aplicarAlPJ(Personaje* pj) {
		pj->nieveMasPotente();
	}
};



#endif /* SORPRESANIEVEMASPOTENTE_H_ */
