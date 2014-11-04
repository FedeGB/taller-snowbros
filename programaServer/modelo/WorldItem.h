/*
 * WorldItem.h
 *
 *  Created on: Oct 16, 2014
 *      Author: rodrizapico
 */

#ifndef WORLDITEM_H_
#define WORLDITEM_H_

#include <Box2D/Box2D.h>
#include <string>
#include <vector>
#include "../utiles/tipos.h"

class WorldItem {
public:

	WorldItem();
	virtual ~WorldItem();
	virtual std::string serializar()=0;

	b2Vec2 posicion;
	float angulo;
	worlditem_t tipo;
	bool hielo;

};

#endif /* WORLDITEM_H_ */
