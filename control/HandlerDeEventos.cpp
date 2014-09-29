/*
 * HandlerDeEventos.cpp
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#include "HandlerDeEventos.h"

HandlerDeEventos::HandlerDeEventos() {}

HandlerDeEventos::~HandlerDeEventos() {}

void HandlerDeEventos::manejarEventoTeclado(SDL_KeyboardEvent keyEvent)
{
	switch( keyEvent.keysym.sym )
	{
		case SDLK_UP: {
			if (keyEvent.state == SDL_PRESSED) notificarObservadores(ARRIBA);
			else notificarObservadores(SOLTOARRIBA);
			break;
		}
		case SDLK_RIGHT: {
			if (keyEvent.state == SDL_PRESSED) notificarObservadores(DERECHA);
			else notificarObservadores(SOLTODERECHA);
			break;
		}
		case SDLK_LEFT: {
			if (keyEvent.state == SDL_PRESSED) notificarObservadores(IZQUIERDA);
			else notificarObservadores(SOLTOIZQUIERDA);
			break;
		}
		case SDLK_r: notificarObservadores(RESTART); break;
		case SDLK_KP_PLUS: notificarObservadores(ZOOMIN); break;
		case SDLK_KP_MINUS: notificarObservadores(ZOOMOUT); break;
		default: break;
	}
}
