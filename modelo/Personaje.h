/*
 * Personaje.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "Objeto.h"
#include "../control/interfaces/INotificable.h"
#include "../modelo/ObjetoDibujable.h"

enum ESTADOS
{
	ESTADO_PARADO,
	ESTADO_IZQUIERDA,
	ESTADO_DERECHA,
	ESTADO_SALTANDO,
	ESTADO_ABAJO,
};

class Personaje : public ObjetoDibujable, public INotificable {
public:
	Personaje();
	virtual ~Personaje();

	// metodos de INotificable
	virtual void eventoArriba();
	virtual void eventoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoAbajo();
	virtual void eventoRESTART(); // NO HACE NADA

	// metodos de IDibujable
	virtual SDL_Rect getRecuadroDeDibujo()
	{
		return getSDL_Rect();
	}

private:
	int pEstado;

	bool saltar();
	bool moverDerecha();
	bool moverIzquierda();
};

#endif /* PERSONAJE_H_ */
