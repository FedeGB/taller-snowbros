/*
 * BolaDeFuego.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef BOLADEFUEGO_H_
#define BOLADEFUEGO_H_

#include "ObjetoInanimado.h"

class BolaDeFuego: public ObjetoInanimado {
public:
	BolaDeFuego();
	virtual ~BolaDeFuego();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	int danio;
};

#endif /* BOLADEFUEGO_H_ */
