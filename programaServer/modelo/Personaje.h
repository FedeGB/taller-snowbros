/*
 * Personaje.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../modelo/formas/Cuadrilatero.h"
#include "Camera.h"
#include <SDL2/SDL.h>
#include "../utiles/tipos.h"


class Personaje : public Cuadrilatero {
public:
	Personaje();
	virtual ~Personaje();

	void setB2DBody(b2Body * pjB2D);
	void modifyFootContacts(int i);
	void setNewAngle(float32 a);

	// metodos de INotificable
	virtual void eventoArriba();
	virtual void eventoSoltoArriba();
	virtual void eventoDerecha();
	virtual void eventoSoltoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoSoltoIzquierda();
	virtual void eventoSpace();
	virtual void eventoSoltoSpace();

	virtual void update();
	virtual std::string serializar();

	Camera * camera;
	bool online;

protected:
	b2Body * bodyB2D;

	int numFootContacts;
	int animationCounter;
	bool isRightPressed;
	bool isLeftPressed;
	bool isUpPressed;
	bool wasLeftPressed1st;
	bool isJumping;
	bool isAirborne;
	bool isMoving;

	enum orientation_t{
		LEFT,
		RIGHT,
	};

	orientation_t orientation;

	sprite_t activeSprite;

private:
	bool isSpacePressed;
	bool canKick;
};

#endif /* PERSONAJE_H_ */
