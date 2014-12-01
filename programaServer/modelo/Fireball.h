/*
 * Fireball.h
 *
 *  Created on: Nov 28, 2014
 *      Author: fedevm
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_


#include "snowball.h"

class Fireball: public snowball {
public:
	Fireball();
	Fireball(float32 posx,float32 posy,int orientation,b2World * world, float damage, float potenciaFuego, float impulsoFuego, b2Vec2 vel_unit);
	virtual ~Fireball();

	virtual std::string serializar();

};



#endif /* FIREBALL_H_ */
