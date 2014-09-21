/*
 * Personaje.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../control/interfaces/INotificable.h"
#include "../modelo/formas/RectanguloDibujable.h"

enum ESTADOS
{
	ESTADO_PARADO,
	ESTADO_IZQUIERDA,
	ESTADO_DERECHA,
	ESTADO_SALTANDO,
	ESTADO_ABAJO,
};

class Personaje : public RectanguloDibujable, public INotificable {
public:
	Personaje();
	virtual ~Personaje();

	void setB2DBody(b2Body * pjB2D);
	void modifyFootContacts(int i);

	// metodos de INotificable
	virtual void eventoArriba();
	virtual void eventoSoltoArriba();
	virtual void eventoDerecha();
	virtual void eventoSoltoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoSoltoIzquierda();
	virtual void eventoRESTART(); // NO HACE NADA

	virtual void render();

private:
	//int pEstado;
	b2Body * bodyB2D;
	int numFootContacts;
	bool isRightPressed;
	bool isLeftPressed;
	bool isUpPressed;
	bool wasLeftPressed1st;
};

#endif /* PERSONAJE_H_ */
