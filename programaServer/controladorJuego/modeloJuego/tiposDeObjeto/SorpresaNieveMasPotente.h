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

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	virtual void aplicarAlPJ(Personaje* pj);
};

#endif /* SORPRESANIEVEMASPOTENTE_H_ */
