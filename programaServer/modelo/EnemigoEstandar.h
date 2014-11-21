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
	virtual void setOnBorder(bool);
	virtual bool itsOnBorder();
	virtual void applyDamage(float);
	virtual bool trapped();

	int enemyNumber;
	sprite_t spriteStun;

protected:

	bool isDownPressed;
	bool isOnPlataform;
	bool isOnBorder;
	bool isTrapped;
	bool isFrozzen;
	int stunCounter;

};



#endif /* ENEMIGOESTANDAR_H_ */
