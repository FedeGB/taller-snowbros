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
	bool hasAtacked;

	enum orientation_t{
		LEFT,
		RIGHT,
	};

	sprite_t activeSprite;
	float dmg;

	bool cayo;

public:
	virtual ~snowball();
	snowball();
	snowball(float32 posx,float32 posy,int orientation,b2World * world, float damage, float impulsoNieve, b2Vec2 vel_pj);
	std::string serializar();
	virtual void setDelete();
	virtual bool forDelete();
	virtual float getDamage();

	void setCayoPorAgujero(bool);
	bool cayoPorAgujero();
	void moverArriba();
};

#endif /* SNOWBALL_H_ */
