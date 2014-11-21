/*
 * snowball.h
 *
 *  Created on: 12/11/2014
 *      Author: coco
 */

#include "Personaje.h"

#ifndef SNOWBALL_H_
#define SNOWBALL_H_

class snowball: public Cuadrilatero {


protected:
	b2Body * poder;
	bool toDelete;

	enum orientation_t{
		LEFT,
		RIGHT,
	};

	sprite_t activeSprite;
	float dmg;

public:
	virtual ~snowball();
	snowball();
	snowball(float32 posx,float32 posy,int orientation,b2World * world, float);
	std::string serializar();
	void setDelete();
	bool forDelete();
	float getDamage();
};

#endif /* SNOWBALL_H_ */
