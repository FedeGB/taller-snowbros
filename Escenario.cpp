/*
 * Escenario.cpp
 *
 *  Created on: 1/9/2014
 *      Author: manuel
 */

#include "Escenario.h"

Escenario::~Escenario()
{
	ListaDibujables::iterator it = eLista.begin();

	if( eLista.size() == 1 )
	{
		delete(*it);
		return;
	}

	for( ; it != eLista.end(); it++)
		delete(*it);
}

void Escenario::dibujarEscena(SDL_Surface* surface)
{
	ListaDibujables::iterator it = eLista.begin();

	if( eLista.size() == 1)
	{
		printf("size lista: %i\n", eLista.size());
		(*it)->dibujar(surface);
		return;
	}

	for( it = eLista.begin(); it != eLista.end(); it++)
		(*it)->dibujar(surface);
}

void Escenario::agregarDibujable(IDibujable* dibujable)
{
	eLista.push_back(dibujable);
}

void Escenario::dibujar(IDibujable& objeto, SDL_Renderer* renderer)
{
	objeto.dibujar(renderer);
}

void Escenario::dibujar(IDibujable& objeto, SDL_Surface* surface)
{
	objeto.dibujar(surface);
}
