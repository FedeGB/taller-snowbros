/*
 * EnemigoEstandar.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: fedevm
 */

#include "EnemigoEstandar.h"
#include "../utiles/tipos.h"

EnemigoEstandar::EnemigoEstandar(int number){
	bodyB2D = NULL;
	numFootContacts = 0;
	isUpPressed = false;
	isDownPressed = false;
	isLeftPressed = false;
	isRightPressed = false;
	wasLeftPressed1st = false;
	orientation = LEFT;
	activeSprite = PARADOIZQUIERDA;
	animationCounter = 0;
	angulo = 0;
	isJumping = 0;
	isAirborne = false;
	isMoving = false;
	isOnPlataform = false;
	camera = NULL;
	online = true;
	enemyNumber = number;
	vida = 10;
}

EnemigoEstandar::~EnemigoEstandar() {};

std::string EnemigoEstandar::serializar(){

	std::string buffer;
	buffer = SSTR(ENEMIGOESTANDAR << " " << posicion.x << " " << posicion.y << " "
			<< angulo << "  " << baseMayor << " " << altura << " "
			<< activeSprite << " " << orientation);
	return buffer;
}

void EnemigoEstandar::update(){
	// Determina si esta en el aire.
	isAirborne = numFootContacts <= 0 ? true : false;

	// Determina, si esta saltando, si ya termino el salto.
	if (!isAirborne) {
		isJumping = false;
		if(isDownPressed /*&& isOnPlataform*/) {
			// TODO: En ContactListener falta contacto con plataformas
			bodyB2D->SetType(b2_kinematicBody);
		}
	}

	float32 desiredVel = 0, scale = 0;

	// Se mueve a la izquierda.
	if (isLeftPressed && wasLeftPressed1st){
		orientation = LEFT;
		desiredVel = -7;                         //// VERIFICAR QUE CUANDO ESTE SALTANDO NO CAMBIE LA VELOCIDAD EN Y!! ! ! ! ! ! !  11 1 1 1 1 one one one
		if (angulo <= 180 * DEGTORAD) scale = 0.33;
		else scale = 3;
		isMoving = true;
	}

	// Se mueve a la derecha.
	if (isRightPressed && !wasLeftPressed1st){
		orientation = RIGHT;
		desiredVel = 7;
		scale = 4;
		if (angulo <= 180 * DEGTORAD) scale = 3;
		else scale = 0.33;
		isMoving = true;
	}

	// Calcula las velocidades deseadas segun la direccion de movimiento.
	b2Vec2 vel = bodyB2D->GetLinearVelocity();
	float32 velXChange = desiredVel * cos(angulo) - vel.x;
	float32 velYChange = 0;
	if ( angulo != 0 ) velYChange =  scale * desiredVel * sin(angulo) - vel.y ;


	// Sin ninguna direccion indicada, se debe quedar quieto.
	if (!isRightPressed && !isLeftPressed ){
		velXChange = -vel.x; // I want the PJ to stop moving in the X axis.
		if (isAirborne) velYChange = 0; // I want the PJ to keep moving normally in the Y axis if it is falling.
		else velYChange = -vel.y; // I want the PJ to stop it's motion if it's in a slope.
		isMoving = false;
	}

	// Calcula los impulsos a aplicar segun en que direccion se esta moviendo el PJ.
	float impulseX = bodyB2D->GetMass() * velXChange;
	float impulseY = bodyB2D->GetMass() * velYChange;
	bodyB2D->ApplyLinearImpulse( b2Vec2(impulseX, impulseY), bodyB2D->GetWorldCenter(), true);


	// Si se recibio UP y el personaje esta en el piso, salta.
	if (isUpPressed && (!isAirborne)){
		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -19;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
		isJumping = true;
	}

	// DETERMINA EL SPRITE QUE CORRESPONDE AL ESTADO DEL PJ.
	animationCounter++;
	switch ((animationCounter/128)){
	case 0:
		if (isAirborne){  // Si esta en el aire:
			if (isJumping) activeSprite = SALTANDOIZQUIERDA1; // Salta.
			else activeSprite = SALTANDOIZQUIERDA5; // Solo cae.
		}
		else {  // Si esta en el piso.
			if (isMoving) activeSprite = MOVIENDOIZQUIERDA1;
			else activeSprite = PARADOIZQUIERDA;
		}
		break;
	case 1:
		if (isAirborne){
			if (isJumping) activeSprite = SALTANDOIZQUIERDA2;
			else activeSprite = SALTANDOIZQUIERDA5;
		}
		else {
			if (isMoving) activeSprite = MOVIENDOIZQUIERDA2;
			else activeSprite = PARADOIZQUIERDA;
		}
		break;
	case 2:
		if (isAirborne){
			if (isJumping) activeSprite = SALTANDOIZQUIERDA3;
			else activeSprite = SALTANDOIZQUIERDA5;
		}
		else {
			if (isMoving) activeSprite = MOVIENDOIZQUIERDA3;
			else activeSprite = PARADOIZQUIERDA;
		}
		break;
	case 3:
		if (isAirborne){
			if (isJumping) activeSprite = SALTANDOIZQUIERDA4;
			else activeSprite = SALTANDOIZQUIERDA5;
		}
		else {
			if (isMoving) activeSprite = MOVIENDOIZQUIERDA4;
			else activeSprite = PARADOIZQUIERDA;
			animationCounter = 0;
		}
		break;
	default:
		if (isAirborne) activeSprite = SALTANDOIZQUIERDA5;
		else animationCounter = 0;
	}


	// Si ya termino la animacion del salto,o cayo sin saltar, settea el sprite de 'cayendo'.
	if(bodyB2D->GetLinearVelocity().y>1 && numFootContacts < 1 ){
		 activeSprite = SALTANDOIZQUIERDA5;
	}

}


void EnemigoEstandar::eventoAbajo() {
	isDownPressed = true;
}

void EnemigoEstandar::eventoSoltoAbajo() {
	isDownPressed = false;
}

bool EnemigoEstandar::isRestricted(teclas_t action) {
	if(action == ARRIBA) {
		if(isDownPressed || isAirborne) {
			return true;
		}
		return false;
	}
	if(action == ABAJO) {
		if(isUpPressed || isAirborne) {
			return true;
		}
		return false;
	}
	// TODO: More restrictions
	return false;
}

