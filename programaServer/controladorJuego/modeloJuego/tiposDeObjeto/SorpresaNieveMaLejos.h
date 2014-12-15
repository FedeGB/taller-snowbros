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

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	virtual void aplicarAlPJ(Personaje* pj);
};

#endif /* SORPRESANIEVEMALEJOS_H_ */
