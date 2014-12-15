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

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	virtual void aplicarAlPJ(Personaje* pj);
};

#endif /* SORPRESACORRER_H_ */
