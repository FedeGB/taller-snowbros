/*
 * shapes.h
 *
 *  Created on: 30/08/2014
 *      Author: coco
 */

#ifndef SHAPES_H_
#define SHAPES_H_

#define PI 3.14159265
#include <Box2D/Box2D.h>
#include <string>
#include <cmath>
#include "parser.h"

class shapes {
public:
	shapes();
	shapes(std::string data,b2World* mundo, int num);
	virtual ~shapes();
	b2Body& getShape();
	b2Vec2& getPoints();



private:
	bool b2d_objet(std::string data,b2World *mundo,int num);
	int num_lados(std::string data);
	b2Body *_shape;
	b2Vec2 *_point;
	bool update_Position();//cambia la posicion de la imagen
};

#endif /* SHAPES_H_ */
