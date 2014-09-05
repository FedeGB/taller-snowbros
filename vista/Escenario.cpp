/*
 * Escenario.cpp
 *
 *  Created on: 1/9/2014
 *      Author: manuel
 */

#include "Escenario.h"

Escenario::Escenario(){}

Escenario::~Escenario()
{
	ListaDibujables::iterator it = eLista.begin();

	if( eLista.size() == 1 )
	{
		eLista.erase(it);
		delete(*it);
		return;
	}

	for( ; it != eLista.end(); it++)
	{
		eLista.erase(it);
		delete(*it);
	}
}

void Escenario::dibujarEscena(SDL_Surface* surface)
{
	ListaDibujables::iterator it = eLista.begin();

	// si la lista tiene 1 solo elemento, dibujo el 1ero y listo.
	if( eLista.size() == 1)
	{
		(*it)->dibujar(surface);
		return;
	}

	// voy recorriendo la lista y dibujando cada objeto dibujable.
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

void Escenario::eventoRESTART()
{
	printf("EVENTO RESTART: RESTART ESCENARIO\n");
}
