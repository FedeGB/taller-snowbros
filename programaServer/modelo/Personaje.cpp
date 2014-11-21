/*
 * Personaje.cpp
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#include "Personaje.h"
#include "../modelo/snowball.h"

#define danio 0.5

Personaje::Personaje(){
	bodyB2D = NULL;
	numFootContacts = 0;
	isUpPressed = false;
	isLeftPressed = false;
	isRightPressed = false;
	isSpacePressed = false;
	wasLeftPressed1st = false;
	orientation = LEFT;
	activeSprite = PARADOIZQUIERDA;
	animationCounter = 0;
	angulo = 0;
	isJumping = 0;
	isAirborne = false;
	isMoving = false;
	isThrowing = false;
	camera = NULL;
	online = true;
	vida = 5;
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

void Personaje::eventoSpace() {
	isSpacePressed = true;
}

void Personaje::eventoSoltoSpace() {
	isSpacePressed = false;
}

void Personaje::setB2DBody(b2Body * pjB2D){
	bodyB2D = pjB2D;
}

void Personaje::modifyFootContacts(int i){
	numFootContacts += i;
}

void Personaje::setNewAngle(float32 a){
	angulo = a;
}

std::string Personaje::serializar(){

	std::string buffer;
	buffer = SSTR(PJ << " " << posicion.x << " " << posicion.y << " "
			<< angulo << "  " << baseMayor << " " << altura << " "
			<< activeSprite << " " << orientation<<" "<< online);
	return buffer;
}

void Personaje::update(Sonido* sonido){


	camera->update();
	if(isSpacePressed && !isAirborne){
		//TODO : ataque
		isThrowing=true;
		if(maxpower>500){
			snowball *sw= new snowball(bodyB2D->GetPosition().x,bodyB2D->GetPosition().y,(int)orientation,bodyB2D->GetWorld(), danio);
			maxpower=0;
		}

	}
		maxpower++;

	if(!this->isAlive()) {
		activeSprite = PARADOIZQUIERDA;
	}
	// Determina si el PJ esta en el aire.
	isAirborne = numFootContacts <= 0 ? true : false;

	//std::cout << "esta en el aire? " << (isAirborne == true ? "si" : "no") << std::endl;
	//std::cout << "la cantidad de contactos es: " << numFootContacts << std::endl;

	// Determina, si el PJ esta saltando, si ya termino el salto.
	if (!isAirborne) isJumping = false;

	// Determina si esta sobre un plano inclinado para ajustar el angulo.
	//if (angulo >= 90 * DEGTORAD && angulo <= 180 * DEGTORAD) angulo +=180 * DEGTORAD;
	//if (angulo >= 180 * DEGTORAD && angulo <= 270 * DEGTORAD) angulo -=180 * DEGTORAD;
	//if (isAirborne) bodyB2D->SetTransform(bodyB2D->GetPosition(), 0);
	//else bodyB2D->SetTransform(bodyB2D->GetPosition(), angulo);


	float32 desiredVel = 0, scale = 0;

	// Se mueve a la izquierda.
	if (isLeftPressed && wasLeftPressed1st){
		orientation = LEFT;
		desiredVel = -14;                         //// VERIFICAR QUE CUANDO ESTE SALTANDO NO CAMBIE LA VELOCIDAD EN Y!! ! ! ! ! ! !  11 1 1 1 1 one one one
		if (angulo <= 180 * DEGTORAD) scale = 0.33;
		else scale = 3;
		isMoving = true;
	}

	// Se mueve a la derecha.
	if (isRightPressed && !wasLeftPressed1st){
		orientation = RIGHT;
		desiredVel = 14;
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


	// Si ninguna tecla de direccion esta presionada, el PJ se debe quedar quieto.
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


	// Si se apreto UP y el personaje esta en el piso, salta.
	if (isUpPressed && (!isAirborne)){
		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -20;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
		isJumping = true;
		sonido->sonido=SALTO;
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
		if(isThrowing) activeSprite = TIRANDOIZQUIERDA2;
		else animationCounter = 0;
		isThrowing= false;

	}


	// Si ya termino la animacion del salto,o cayo sin saltar, settea el sprite de 'cayendo'.
	if(bodyB2D->GetLinearVelocity().y>1 && numFootContacts < 1 ){
		 activeSprite = SALTANDOIZQUIERDA5;
	}
}

bool Personaje::isAlive() {
	return (vida > 0.0f);
}

void Personaje::applyDamage(float dmg) {
	vida -= dmg;
}

void Personaje::eventoa(){
	b2World * mundo = bodyB2D->GetWorld();

	Sorpresa* sorpresa = new Sorpresa();
	sorpresa->agregarAMundo(10, 10, mundo);
}

void Personaje::aplicarSorpresa(Sorpresa* sorpresa){
	printf("APLICADAAAA\n");
}

