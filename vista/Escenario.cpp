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
		if(*it != NULL) {
			delete(*it);
			*it = NULL;
		}
		return;
	}

	for( ; it != eLista.end(); it++)
	{
		eLista.erase(it);
		if(*it !=NULL) {
			delete(*it);
			*it = NULL;
		}
	}
}

void Escenario::dibujarEscena(SDL_Renderer* renderer)
{
	ListaDibujables::iterator it = eLista.begin();

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	// si la lista tiene 1 solo elemento, dibujo el 1ero y listo.
	if( eLista.size() == 1)
	{
		(*it)->dibujar();
		return;
	}

	// voy recorriendo la lista y dibujando cada objeto dibujable.
	for( it = eLista.begin(); it != eLista.end(); it++)
	{
		(*it)->dibujar();
	}

	SDL_RenderPresent(renderer);
}

void Escenario::agregarDibujable(IDibujable* dibujable)
{
	eLista.push_back(dibujable);
}

void Escenario::eventoRESTART()
{
	printf("EVENTO RESTART: RESTART ESCENARIO\n");
}
