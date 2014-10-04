/*
 * vistaPersonaje.h
 *
 *  Created on: Sep 21, 2014
 *      Author: matias
 */

#ifndef VISTAPERSONAJE_H_
#define VISTAPERSONAJE_H_

#include "../modelo/interfaces/IDibujable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../Window.h"
#include <list>
#include "../modelo/Personaje.h"

class vistaPersonaje {
public:
	vistaPersonaje(Personaje* personaje);
	virtual ~vistaPersonaje();
	void render();

private:
	Personaje* refPersonaje;
	SDL_Surface* imgParado;
	SDL_Surface* imgIzq;
	SDL_Surface* imgDer;
};

#endif /* VISTAPERSONAJE_H_ */
