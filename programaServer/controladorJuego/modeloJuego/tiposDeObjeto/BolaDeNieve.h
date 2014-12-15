/*
 * BolaDeNieve.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef BOLADENIEVE_H_
#define BOLADENIEVE_H_

#include "ObjetoInanimado.h"

class BolaDeNieve: public ObjetoInanimado {
public:
	BolaDeNieve();
	virtual ~BolaDeNieve();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	int danio;
};

#endif /* BOLADENIEVE_H_ */
