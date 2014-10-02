/*
 * HandlerDeEventos.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef HANDLERDEEVENTOS_H_
#define HANDLERDEEVENTOS_H_

#include <SDL2/SDL.h>
#include "interfaces/IObservado.h"

class HandlerDeEventos : public IObservado{
public:
	HandlerDeEventos();
	virtual ~HandlerDeEventos();

	void manejarEventoTeclado(SDL_KeyboardEvent);
};

#endif /* HANDLERDEEVENTOS_H_ */
