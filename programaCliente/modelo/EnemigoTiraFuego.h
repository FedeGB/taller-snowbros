/*
 * EnemigoTiraFuego.h
 *
 *  Created on: Nov 26, 2014
 *      Author: fedevm
 */

#ifndef ENEMIGOTIRAFUEGO_H_
#define ENEMIGOTIRAFUEGO_H_

#include "EnemigoEstandar.h"

class EnemigoTiraFuego: public EnemigoEstandar {
public:
	EnemigoTiraFuego();
	virtual ~EnemigoTiraFuego();

	virtual std::string serializar();
};



#endif /* ENEMIGOTIRAFUEGO_H_ */
