/*
 * IDibujable.h
 *
 *  Created on: 2/9/2014
 *      Author: manuel
 */

#ifndef IDIBUJABLE_H_
#define IDIBUJABLE_H_

#include <SDL2/SDL.h>

class IDibujable {
public:
	IDibujable(){};
	virtual ~IDibujable(){};

	virtual void dibujar(SDL_Renderer* renderer){};
	virtual void dibujar(SDL_Surface* surface){};
};



#endif /* IDIBUJABLE_H_ */
