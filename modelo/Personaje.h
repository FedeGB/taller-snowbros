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

enum ESTADOS
{
	ESTADO_PARADO,
	ESTADO_IZQUIERDA,
	ESTADO_DERECHA,
	ESTADO_SALTANDO,
};

class Personaje : public Objeto, public INotificable {
public:
	Personaje();
	virtual ~Personaje();

	// metodos de INotificable
	virtual void eventoArriba();
	virtual void eventoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoAbajo();
	virtual void eventoRESTART(); // NO HACE NADA

private:
	int pEstado;

	bool saltar();
	bool moverDerecha();
	bool moverIzquierda();
};

#endif /* PERSONAJE_H_ */
