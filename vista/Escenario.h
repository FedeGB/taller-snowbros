/*
 * Escenario.h
 *
 *  Created on: 1/9/2014
 *      Author: manuel
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include <SDL2/SDL.h>
#include "../modelo/interfaces/IDibujable.h"
#include "../control/interfaces/INotificable.h"
#include "../utiles/tipos.h"
#include "../utiles/Logger.h"

typedef std::vector<IDibujable*> ListaDibujables;

class Escenario : public INotificable {
public:
	Escenario();
	virtual ~Escenario();

	void agregarDibujable(IDibujable* dibujable);

	void dibujarEscena(SDL_Renderer*);

	// metodos de INotificable
	virtual void eventoArriba() {}; // NO HACE NADA
	virtual void eventoDerecha() {}; // NO HACE NADA
	virtual void eventoIzquierda() {}; // NO HACE NADA
	virtual void eventoAbajo() {}; // NO HACE NADA
	virtual void eventoRESTART();

private:
	ListaDibujables eLista;
};

#endif /* ESCENARIO_H_ */
