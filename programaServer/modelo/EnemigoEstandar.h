/*
 * EnemigoEstandar.h
 *
 *  Created on: Nov 4, 2014
 *      Author: fedevm
 */

#ifndef ENEMIGOESTANDAR_H_
#define ENEMIGOESTANDAR_H_

#include "Personaje.h"

class EnemigoEstandar: public Personaje {
public:
	EnemigoEstandar(int number);
	virtual ~EnemigoEstandar();
	virtual std::string serializar();
	virtual void update();
	int enemyNumber;
};



#endif /* ENEMIGOESTANDAR_H_ */
