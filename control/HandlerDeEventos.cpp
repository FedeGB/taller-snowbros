/*
 * HandlerDeEventos.cpp
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#include "HandlerDeEventos.h"

HandlerDeEventos::HandlerDeEventos() {}

HandlerDeEventos::~HandlerDeEventos() {}

void HandlerDeEventos::manejarTeclaPresionada(SDL_Keycode key)
{
	switch( key )
	{
		case SDLK_UP: notificarObservadores(ARRIBA); break;
		case SDLK_RIGHT: notificarObservadores(DERECHA); break;
		case SDLK_LEFT: notificarObservadores(IZQUIERDA); break;
		case SDLK_DOWN: notificarObservadores(ABAJO); break;
		case SDLK_r: notificarObservadores(RESTART); break;
	}
}
