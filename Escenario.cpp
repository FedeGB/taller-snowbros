/*
 * Escenario.cpp
 *
 *  Created on: 1/9/2014
 *      Author: manuel
 */

#include "Escenario.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Escenario::Escenario(){}

Escenario::~Escenario() {}

void Escenario::dibujar(IDibujable& objeto, SDL_Renderer* renderer)
{
	objeto.dibujar(renderer);
}

void Escenario::dibujar(IDibujable& objeto, SDL_Surface* surface)
{
	objeto.dibujar(surface);
}

