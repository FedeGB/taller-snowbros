/*
 * Personaje.cpp
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#include "Personaje.h"

Personaje::Personaje(){
	bodyB2D = NULL;
	numFootContacts = 0;
	isUpPressed = false;
	isLeftPressed = false;
	isRightPressed = false;
	wasLeftPressed1st = false;
}

Personaje::~Personaje() {}

void Personaje::eventoArriba(){	isUpPressed = true;}

void Personaje::eventoSoltoArriba(){isUpPressed = false;}

void Personaje::eventoDerecha(){
	isRightPressed = true;
	if (!isLeftPressed) wasLeftPressed1st = false;
}

void Personaje::eventoSoltoDerecha(){
	isRightPressed = false;
	if (isLeftPressed) wasLeftPressed1st = true;
}

void Personaje::eventoIzquierda(){
	isLeftPressed = true;
	if (!isRightPressed) wasLeftPressed1st = true;
}

void Personaje::eventoSoltoIzquierda(){
	isLeftPressed = false;
	if (isRightPressed) wasLeftPressed1st = false;
}

void Personaje::eventoRESTART(){//posicion(100.0 ,100.0);
}

void Personaje::setB2DBody(b2Body * pjB2D){
	bodyB2D = pjB2D;
}

void Personaje::modifyFootContacts(int i){
	numFootContacts += i;
}

void Personaje::render(){

	if (isUpPressed && (numFootContacts >= 1)){

		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -10;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
	}

	if (isLeftPressed && wasLeftPressed1st){

		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -15;
		float velChange = desiredVel - vel.x;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(impulse, 0), bodyB2D->GetWorldCenter(), true);
	}

	if (isRightPressed && !wasLeftPressed1st){

		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = 15;
		float velChange = desiredVel - vel.x;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(impulse, 0), bodyB2D->GetWorldCenter(), true);
	}

	if (!isRightPressed && !isLeftPressed){

		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = 0;
		float velChange = desiredVel - vel.x;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(impulse, 0), bodyB2D->GetWorldCenter(), true);
	}

	RectanguloDibujable::render();

}

