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
	virtual void eventoSpace();
	virtual void eventoSoltoSpace();
	virtual bool isRestricted(teclas_t);
	virtual void setOnBorder(bool);
	virtual bool itsOnBorder();
	virtual void applyDamage(float);
	virtual bool trapped();
	virtual void empujar(orientation_t);
	virtual void Noempujar();
	void setDelete(){
			toDelete = true;
		}
	bool forDelete(){
			return toDelete;
		}

	int enemyNumber;
	sprite_t spriteStun;
	bool isFrozzen;

protected:
	bool toDelete;

	bool isDownPressed;
	bool isSpacePressed;
	bool isOnBorder;
	bool isTrapped;
	bool isPushable;
	orientation_t pushOrientation;

	int stunCounter;

};



#endif /* ENEMIGOESTANDAR_H_ */
