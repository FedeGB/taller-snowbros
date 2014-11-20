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
#include "../modelo/snowball.h"

#include "../modelo/Sonido.h"
#include "../modelo/Sorpresa.h"


class Personaje : public Cuadrilatero {
public:
	Personaje();
	virtual ~Personaje();

	void setB2DBody(b2Body * pjB2D);
	void modifyFootContacts(int i);
	void setNewAngle(float32 a);
	virtual bool isAlive();
	virtual void applyDamage(float);
	virtual void aplicarSorpresa(Sorpresa*);

	// metodos de INotificable
	virtual void eventoArriba();
	virtual void eventoSoltoArriba();
	virtual void eventoDerecha();
	virtual void eventoSoltoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoSoltoIzquierda();
	virtual void eventoSpace();
	virtual void eventoSoltoSpace();

	virtual void eventoa();

	virtual void update(Sonido*);
	virtual std::string serializar();

	Camera * camera;
	bool online;

protected:
	b2Body * bodyB2D;

	int maxpower;
	int numFootContacts;
	int animationCounter;
	bool isRightPressed;
	bool isLeftPressed;
	bool isUpPressed;
	bool wasLeftPressed1st;
	bool isJumping;
	bool isAirborne;
	bool isMoving;
	bool isThrowing;
	bool isSpacePressed;
	float vida;

	enum orientation_t{
		LEFT,
		RIGHT,
	};

	orientation_t orientation;

	sprite_t activeSprite;

private:
	bool canKick;
};

#endif /* PERSONAJE_H_ */
