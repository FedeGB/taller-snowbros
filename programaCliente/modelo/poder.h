/*
 * poder.h
 *
 *  Created on: 12/11/2014
 *      Author: coco
 */

#ifndef PODER_H_
#define PODER_H_

#include "../modelo/formas/Cuadrilatero.h"
#include <SDL2/SDL.h>
#include "../utiles/tipos.h"

class poder:public Cuadrilatero {
public:
	poder();
	virtual ~poder();

//	virtual std::string serializar();

		enum orientation_t{
			LEFT,
			RIGHT,
		};

		orientation_t orientation;

		sprite_t activeSprite;
};

#endif /* PODER_H_ */
