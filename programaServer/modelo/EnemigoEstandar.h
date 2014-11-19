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
	virtual void eventoAbajo();
	virtual void eventoSoltoAbajo();
	virtual bool isRestricted(teclas_t);

	int enemyNumber;

protected:
	bool isDownPressed;
	bool isOnPlataform;

};



#endif /* ENEMIGOESTANDAR_H_ */
