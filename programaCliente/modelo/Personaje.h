/*
 * Personaje.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../modelo/formas/Cuadrilatero.h"
#include <SDL2/SDL.h>
#include "../utiles/tipos.h"


class Personaje : public Cuadrilatero {
public:
	Personaje();
	virtual ~Personaje();

	virtual std::string serializar();

	enum orientation_t{
		LEFT,
		RIGHT,
	};

	orientation_t orientation;

	sprite_t activeSprite;

};

#endif /* PERSONAJE_H_ */
