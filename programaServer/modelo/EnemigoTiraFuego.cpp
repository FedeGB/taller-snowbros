/*
 * EnemigoTiraFuego.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: fedevm
 */

#include "EnemigoTiraFuego.h"
#include "BolaEnemigo.h"
#include "Fireball.h"

#define TTHROW 200

EnemigoTiraFuego::EnemigoTiraFuego(int number) {
	tipo = ENEMIGOTIRAFUEGO;
	bodyB2D = NULL;
	numFootContacts = 0;
	toDelete=false;
	isUpPressed = false;
	isDownPressed = false;
	isLeftPressed = false;
	isRightPressed = false;
	isSpacePressed=false;
	wasLeftPressed1st = false;
	orientation = LEFT;
	activeSprite = PARADOIZQUIERDA;
	spriteStun= STUN0;
	animationCounter = 0;
	angulo = 0;
	isJumping = 0;
	isAirborne = false;
	isMoving = false;
	isOnBorder = false;
	isFrozzen=false;
	camera = NULL;
	online = true;
	enemyNumber = number;
	vida = 3;
	isTrapped = false;
	stunCounter=0;
	dropCounter = 0;
	isPushable=false;
	maxpower = 0;
	timerThrow = 0;
	wasKicked = false;
	safeFlag = false;

	sumergido = false;
	velocidadSumergido = 1.0f;
	sobreHielo = false;
}

EnemigoTiraFuego::~EnemigoTiraFuego() {

}

std::string EnemigoTiraFuego::serializar() {
	std::string buffer;
	buffer = SSTR(ENEMIGOTIRAFUEGO << " " << posicion.x << " " << posicion.y << " "
	<< angulo << "  " << baseMayor << " " << altura << " "
	<< activeSprite << " " << orientation<< " " << spriteStun);

	return buffer;
}

void EnemigoTiraFuego::update(){

	if( sumergido ){
		bodyB2D->SetGravityScale(0.5f);
		velocidadSumergido = 0.5f;
	}
	else{
		bodyB2D->SetGravityScale(1.0f);
		velocidadSumergido = 1.0f;
	}

	// Determina si esta en el aire.
	isAirborne = numFootContacts <= 0 ? true : false;

	if(vida<0) spriteStun=STUN0;
	else if(vida<=1) spriteStun=STUN3;
	else if(vida<=2) spriteStun=STUN2;
	else if(vida<3) spriteStun=STUN1;
	else if(vida>=3) spriteStun=STUN0;

	if(isPushable&&wasKicked){
		setDelete();
	}

	if(isFrozzen){
		stunCounter++;
		if(stunCounter==10000){
			isFrozzen=false;
//			for(b2Fixture * fix= bodyB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
//				void* userData =fix->GetUserData();
//				if(*((int*)(&userData))==ENEMIGOBOLA) fix->SetUserData((void*)ENEMIGOCONGELADO);
//				if(*((int*)(&userData))==PIESENBOLA) fix->SetUserData((void*)PIESENCONGELADO);
//			}
			isBolaGirar = false;
		}
		activeSprite=CONGELADO;
		return;
	}

	if(isTrapped) {
		animationCounter++;
		if(animationCounter<100)
			activeSprite=ATRAPADO1;
		else if (animationCounter<200)
			activeSprite=ATRAPADO2;
		else {
			animationCounter=0;
			stunCounter++;
		}
		if(stunCounter>=10){
			vida++;
			stunCounter=0;
		}
		if(vida>=3){
			isTrapped=false;
			for(b2Fixture * fix= bodyB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
				void* userData =fix->GetUserData();
				if(*((int*)(&userData))==ENEMIGOCONGELADO)
					fix->SetUserData((void*)ENEMIGO);
				if(*((int*)(&userData))==PIESENCONGELADO)
					fix->SetUserData((void*)PIESEN);
			}
		}
		return;
	}

	// Determina, si esta saltando, si ya termino el salto.
	if (!isAirborne) {
		isJumping = false;
		if(isDownPressed) {
			isFalling = true;
		} else {
			isFalling = false;
		}
		if(!isDownPressed) {
			isFalling = false;
		} else {
			isFalling = true;
		}
	} else {
		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		if(vel.y >= 0) {
			isFalling = true;
		}
	}

	if(isSpacePressed && !isFrozzen){
			isThrowing=true;
			Fireball *fb= new Fireball(bodyB2D->GetPosition().x,bodyB2D->GetPosition().y,(int)orientation,bodyB2D->GetWorld(), 1.0f, 0.0f, 1.0f, bodyB2D->GetLinearVelocity());
			//this->timerThrow=TTHROW;
//				if( potenciaNieveSorpresa == 0.5 && impulsoNieveSorpresa == 1.0 )
//					sonido->sonido = DISPARO;
//				else
//					sonido->sonido = DISPARO_SORPRESA;
		}

	float32 desiredVel = 0, scale = 0;

	// Se mueve a la izquierda.
	if (isLeftPressed && wasLeftPressed1st){
		orientation = LEFT;
		desiredVel = -7 * velocidadSumergido;                         //// VERIFICAR QUE CUANDO ESTE SALTANDO NO CAMBIE LA VELOCIDAD EN Y!! ! ! ! ! ! !  11 1 1 1 1 one one one
		if (angulo <= 180 * DEGTORAD) scale = 0.33;
		else scale = 3;
		isMoving = true;
	}

	// Se mueve a la derecha.
	if (isRightPressed && !wasLeftPressed1st){
		orientation = RIGHT;
		desiredVel = 7 * velocidadSumergido;
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
	if ( (isUpPressed && (!isAirborne)) || (sumergido && isUpPressed)){
		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -19 * velocidadSumergido;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
		isJumping = true;
	}

	if(isDownPressed && !isFalling ) {
		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -200;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
	}

	// DETERMINA EL SPRITE QUE CORRESPONDE AL ESTADO DEL PJ.
	animationCounter++;
	switch ((animationCounter/100)){
		case 0:
			if (isAirborne){  // Si esta en el aire:
				if (isJumping) activeSprite = SALTANDOIZQUIERDA1; // Salta.
				else activeSprite = SALTANDOIZQUIERDA5; // Solo cae.
			}
			else {  // Si esta en el piso.
				if (isMoving) activeSprite = MOVIENDOIZQUIERDA1;
				else activeSprite = PARADOIZQUIERDA;
			}
			if(isThrowing)
						activeSprite = TIRANDOIZQUIERDA1;
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
			if(isThrowing)
						activeSprite = TIRANDOIZQUIERDA2;
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
			if(isThrowing)
						activeSprite = TIRANDOIZQUIERDA3;
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
				isThrowing= false;
			}
			if(isThrowing)
						activeSprite = TIRANDOIZQUIERDA1;
			break;
		default:
			if (isAirborne) activeSprite = SALTANDOIZQUIERDA5;
			if(isThrowing){
				activeSprite = TIRANDOIZQUIERDA2;
				if(animationCounter>500)
					animationCounter=0;
			}
			else animationCounter = 0;
			isThrowing= false;

		}


		// Si ya termino la animacion del salto,o cayo sin saltar, settea el sprite de 'cayendo'.
		if(bodyB2D->GetLinearVelocity().y>1 && numFootContacts < 1 ){
			 activeSprite = SALTANDOIZQUIERDA5;
		}
}

void EnemigoTiraFuego::restarTimerThrow() {
	if(timerThrow >= 0) {
		timerThrow--;
	} else {
		timerThrow = TTHROW;
	}
}

int EnemigoTiraFuego::getTimerThrow() {
	return timerThrow;
}
