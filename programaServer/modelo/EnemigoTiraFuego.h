/*
 * EnemigoTiraFuego.h
 *
 *  Created on: Nov 25, 2014
 *      Author: fedevm
 */

#ifndef ENEMIGOTIRAFUEGO_H_
#define ENEMIGOTIRAFUEGO_H_

#include "EnemigoEstandar.h"

class EnemigoTiraFuego: public EnemigoEstandar {
public:
	EnemigoTiraFuego(int number);
	virtual ~EnemigoTiraFuego();
	virtual std::string serializar();
	virtual void update();
	virtual void restarTimerThrow();
	virtual int getTimerThrow();


protected:
	int timerThrow;
};


#endif /* ENEMIGOTIRAFUEGO_H_ */
