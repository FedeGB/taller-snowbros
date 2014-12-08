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
	EnemigoEstandar();
	virtual ~EnemigoEstandar();
	virtual std::string serializar();
	virtual void update();
	virtual void eventoAbajo();
	virtual void eventoSoltoAbajo();
	virtual void eventoSpace();
	virtual void eventoSoltoSpace();
	virtual void setOnBorder(bool);
	virtual bool itsOnBorder();
	virtual void applyDamage(float);
	virtual bool trapped();
	virtual void empujar(orientation_t);
	virtual void Noempujar();
	virtual bool isMovingLeft();
	virtual bool isMovingRight();
	virtual void setAsKicked();


	void setCayoPorAgujero(bool);
	bool cayoPorAgujero();
	void moverArriba();

	void setDelete(){
			toDelete = true;
		}
	bool forDelete(){
			return toDelete;
		}
	//bool isSpacePressed;
	int enemyNumber;
	sprite_t spriteStun;
	bool isFrozzen;
	orientation_t pushOrientation;
	void hacerBola();
	void deshacerBola();
	bool canRotate();

protected:
	bool toDelete;

	bool isDownPressed;

	bool isOnBorder;
	bool isTrapped;
	bool isPushable;
	bool isBolaGirar;
	bool alreadyBall;

	bool wasKicked;

	int stunCounter;
	int dropCounter;

};



#endif /* ENEMIGOESTANDAR_H_ */
