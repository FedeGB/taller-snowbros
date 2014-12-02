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

class Personaje : public Cuadrilatero {
public:
	Personaje();
	virtual ~Personaje();

	void setB2DBody(b2Body * pjB2D);
	void modifyFootContacts(int i);
	void setNewAngle(float32 a);

	virtual bool isAlive();
	virtual void applyDamage(float);
	virtual bool GetAirborne();
	virtual int GetOrientation();

	virtual void agregarVida();
	virtual void correrMasRapido();
	virtual void nieveMasLejos();
	virtual void nieveMasPotente();
	virtual void Patear();
	virtual void NoPatear();

	void respawn();


	virtual void actualizarEfectos();

	virtual b2World * getMundo();

	virtual bool estaSumergido();
	virtual void setSumergido(bool);

	/* virtual */ void setCayoPorAgujero(bool);
	/* virtual */ bool cayoPorAgujero();
	void moverArriba();

	// metodos de INotificable
	virtual void eventoArriba();
	virtual void eventoSoltoArriba();
	virtual void eventoDerecha();
	virtual void eventoSoltoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoSoltoIzquierda();
	virtual void eventoSpace();
	virtual void eventoSoltoSpace();
	virtual void setFalling(bool);
	virtual bool getFalling();
	virtual bool getThrowing();

	//virtual void eventoa();

	virtual void update(Sonido*);
	virtual std::string serializar();

	Camera * camera;
	bool online;
	orientation_t orientation;
	bool isSpacePressed;
	void * enemigoParaEmpujar;
	b2Vec2 initPos;
	bool isRespawnable;
	bool inmunity;
	float vida;

protected:
	b2Body * bodyB2D;
	float inmunityCounter;

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
	bool isFalling;
	bool sumergido;



	float sorpresaPaso;
	float sorpresasContador[4];


	float velocidadPJSorpresa;
	float potenciaNieveSorpresa;
	float impulsoNieveSorpresa;

	float velocidadSumergido;

	bool cayo; //cayo por agujero



	sprite_t activeSprite;

private:
	bool canKick;
	b2Vec2 posIni;
};

#endif /* PERSONAJE_H_ */
