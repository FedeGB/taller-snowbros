/*
 * Escenario.h
 *
 *  Created on: 1/9/2014
 *      Author: manuel
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include <SDL2/SDL.h>
#include "modelo/interfaces/IDibujable.h"

class Escenario {
public:
	Escenario();
	virtual ~Escenario();

	void dibujar(IDibujable& dibujable, SDL_Renderer* renderer);
	void dibujar(IDibujable& dibujable, SDL_Surface* surface);
};

#endif /* ESCENARIO_H_ */
