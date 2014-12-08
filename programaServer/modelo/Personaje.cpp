/*
 * Personaje.cpp
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#include "Personaje.h"
#include "EnemigoEstandar.h"
#include "EnemigoTiraFuego.h"
#include "../modelo/snowball.h"

float danio =0.5;

Personaje::Personaje(){
	tipo = PJ;
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
	isFalling = false;
	canKick = false;
	camera = NULL;
	online = true;
	vida = 2;
	maxpower = 0;
	for( int i = 0; i < 3; i++)
		sorpresasContador[i] = 0.0f;
	inmunityCounter=0.0f;
	sorpresaPaso = 0.2;
	velocidadPJSorpresa = 1.0f;
	potenciaNieveSorpresa = 0.5f;
	impulsoNieveSorpresa = 1.0f;
	enemigoParaEmpujar = NULL;
	sumergido = false;
	velocidadSumergido = 1.0f;
	cayo = false;
	isRespawnable=false;
	inmunity=true;
	toDelete=false;
	puntaje = 0;
	bindball=false;
}

Personaje::~Personaje() {
	this->bodyB2D->GetWorld()->DestroyBody(this->bodyB2D);
	this->bodyB2D=NULL;
}

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
	if(enemigoParaEmpujar!=NULL){
		puntaje += 50;
		((EnemigoEstandar*)enemigoParaEmpujar)->setAsKicked();
		((EnemigoEstandar*)enemigoParaEmpujar)->pushOrientation=orientation;
		enemigoParaEmpujar = NULL;
	}
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
			<< activeSprite << " " << orientation<<" "<< online<<" "<<inmunity);
	return buffer;
}

void Personaje::update(Sonido* sonido){


	camera->update();

	// si la velocidad del pj es mayor a la normal, y el sonido todavia no esta con una velocidad mayor, lo cambio
	if( velocidadPJSorpresa == 2.0f && sonido->velocidad != 2.0f ){
		sonido->sonido = MUSICA_DE_FONDO;
		sonido->velocidad = 2.0f;
	}

	// si la velocidad del pj es igual a la normal, y el sonido todavia no esta con una velocidad normal, lo cambio
	if( velocidadPJSorpresa != 2.0f && sonido->velocidad != 1.0f ){
		sonido->sonido = MUSICA_DE_FONDO;
		sonido->velocidad = 1.0f;
	}

	actualizarEfectos();

	if(isSpacePressed  && !bindball ){
		//TODO : ataque
		isThrowing=true;
		if(maxpower>250){
			snowball *sw= new snowball(bodyB2D->GetPosition().x,bodyB2D->GetPosition().y,(int)orientation,bodyB2D->GetWorld(), potenciaNieveSorpresa, impulsoNieveSorpresa, bodyB2D->GetLinearVelocity());
			maxpower=0;
			if( potenciaNieveSorpresa == 0.5 && impulsoNieveSorpresa == 1.0 )
				sonido->sonido = DISPARO;
			else
				sonido->sonido = DISPARO_SORPRESA;
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

	if( sumergido ){
		bodyB2D->SetGravityScale(0.5f);
		velocidadSumergido = 0.5f;
	}
	else{
		bodyB2D->SetGravityScale(1.0f);
		velocidadSumergido = 1.0f;
	}

	// Determina si esta sobre un plano inclinado para ajustar el angulo.
	//if (angulo >= 90 * DEGTORAD && angulo <= 180 * DEGTORAD) angulo +=180 * DEGTORAD;
	//if (angulo >= 180 * DEGTORAD && angulo <= 270 * DEGTORAD) angulo -=180 * DEGTORAD;
	//if (isAirborne) bodyB2D->SetTransform(bodyB2D->GetPosition(), 0);
	//else bodyB2D->SetTransform(bodyB2D->GetPosition(), angulo);


	float32 desiredVel = 0, scale = 0;

	// Se mueve a la izquierda.
	if (isLeftPressed && wasLeftPressed1st){
		orientation = LEFT;
		desiredVel = -14 * velocidadPJSorpresa * velocidadSumergido;                         //// VERIFICAR QUE CUANDO ESTE SALTANDO NO CAMBIE LA VELOCIDAD EN Y!! ! ! ! ! ! !  11 1 1 1 1 one one one
		if (angulo <= 180 * DEGTORAD) scale = 0.33;
		else scale = 3;
		isMoving = true;
	}

	// Se mueve a la derecha.
	if (isRightPressed && !wasLeftPressed1st){
		orientation = RIGHT;
		desiredVel = 14 * velocidadPJSorpresa * velocidadSumergido;
		scale = 4;
		if (angulo <= 180 * DEGTORAD) scale = 3;
		else scale = 0.33;
		isMoving = true;
	}

	// Calcula las velocidades deseadas segun la direccion de movimiento.
	b2Vec2 vel = bodyB2D->GetLinearVelocity() ;
	float32 velXChange = desiredVel * cos(angulo) - vel.x ;
	float32 velYChange = 0;
	if ( angulo != 0 ) velYChange =  scale * desiredVel * sin(angulo) - vel.y ;


	// Si ninguna tecla de direccion esta presionada, el PJ se debe quedar quieto.
	if (!isRightPressed && !isLeftPressed ){
		velXChange = -vel.x; // I want the PJ to stop moving in the X axis.
		if (isAirborne ) velYChange = 0; // I want the PJ to keep moving normally in the Y axis if it is falling.
		else velYChange = -vel.y; // I want the PJ to stop it's motion if it's in a slope.
		isMoving = false;
	}

	// Calcula los impulsos a aplicar segun en que direccion se esta moviendo el PJ.
	float impulseX = bodyB2D->GetMass() * velXChange ;
	float impulseY = bodyB2D->GetMass() * velYChange ;
	bodyB2D->ApplyLinearImpulse( b2Vec2(impulseX, impulseY), bodyB2D->GetWorldCenter(), true);


	// Si se apreto UP y si el personaje esta en el piso o si se apreto UP y el pj esta sumergido, salta.
	if ( (isUpPressed && (!isAirborne)) || (sumergido && isUpPressed) ){
		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -20 * velocidadSumergido;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
		isJumping = true;
		if( sumergido )
			sonido->sonido=SALTO_SUMERGIDO;
		else
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

bool Personaje::isAlive() {
	return (vida > 0.0f);
}

bool Personaje::GetAirborne(){
	return this->isAirborne;
}

void Personaje::applyDamage(float dmg) {
	if(inmunity)
		return;
	vida -= dmg;
	printf("vida restante: %f\n", vida);
	inmunity=true;
	isRespawnable=true;
}

b2World* Personaje::getMundo(){
	return bodyB2D->GetWorld();
}

void Personaje::agregarVida(){
	printf("AGREGAR VIDA\n");
	puntaje += 23;
	vida += 1.0f;
}

void Personaje::correrMasRapido(){
	printf("CORRER MAS RAPIDO\n");
	puntaje += 15;
	if( velocidadPJSorpresa == 1.0f )
		velocidadPJSorpresa = 2.0f;
}

void Personaje::nieveMasLejos(){
	printf("NIEVE MAS LEJOS\n");
	puntaje += 10;
	if( impulsoNieveSorpresa == 1.0f )
		impulsoNieveSorpresa = 2.0f;
}

void Personaje::nieveMasPotente(){
	printf("NIEVE MAS POTENTE\n");
	puntaje += 13;
	if( potenciaNieveSorpresa == 0.5f )
		potenciaNieveSorpresa = 2.0f;
}

void Personaje::actualizarEfectos(){
	if(inmunity){
		inmunityCounter+= sorpresaPaso;
		if( inmunityCounter > 500.0f  ){
			inmunity = false;
			inmunityCounter = 0.0f;
			printf("FIN INMUNIDADs\n");
		}
	}

	// actualiza contador de sopresa velocidad del pj
	if( velocidadPJSorpresa != 1.0f ){
		sorpresasContador[0] += sorpresaPaso;
//		printf("contador velocidad = %f\n", sorpresasContador[0]);
		if( sorpresasContador[0] > 3000.0f  ){
			velocidadPJSorpresa = 1.0f;
			sorpresasContador[0] = 0.0f;
			printf("FIN EFECTO RAPIDEZ\n");
		}
	}

	// actualiza contador de sopresa nieve mas potente
	if( potenciaNieveSorpresa != 0.5f ){
		sorpresasContador[1] += sorpresaPaso;
//		printf("contador nieve ṕotencia = %f\n", sorpresasContador[1]);
		if( sorpresasContador[1] > 3000.0f ){
			potenciaNieveSorpresa = 0.5f;
			sorpresasContador[1] = 0.0f;
			printf("FIN EFECTO NIEVE POTENTE\n");
		}
	}

	// actualiza contador de sopresa nieve mas lejos
	if( impulsoNieveSorpresa != 1.0f ){
		sorpresasContador[2] += sorpresaPaso;
//		printf("contador nieve lejos = %f\n", sorpresasContador[2]);
		if( sorpresasContador[2] > 3000.0f ){
			impulsoNieveSorpresa = 1.0f;
			sorpresasContador[2] = 0.0f;
			printf("FIN EFECTO NIEVE LEJOS\n");
		}
	}
}

void Personaje::Patear(){
	canKick=true;
}
void Personaje::NoPatear(){
	canKick=false;
}

int Personaje::GetOrientation(){
	return orientation;
}

bool Personaje::estaSumergido(){
	return sumergido;
}

void Personaje::setSumergido(bool s){
	if( sumergido != s)
		sumergido = s;
}

void Personaje::setFalling(bool fall) {
	isFalling = fall;
}

bool Personaje::getFalling() {
	return isFalling;
}

void Personaje::setCayoPorAgujero(bool b) {
	cayo = b;
}

bool Personaje::cayoPorAgujero(){
	return cayo;
}

bool Personaje::getThrowing() {
	return isThrowing;
}

void Personaje::respawn(){
	this->bodyB2D->SetTransform(initPos,0);
	this->bodyB2D->SetLinearVelocity(b2Vec2(0,0));
	this->camera->reposition(initPos);
	isRespawnable=false;
	inmunity=true;
}

void Personaje::respawnOut(){
	this->bodyB2D->SetTransform(b2Vec2(100000,100000),0);
	this->bodyB2D->SetLinearVelocity(b2Vec2(0,0));
	//this->camera->reposition(initPos);
	isRespawnable=false;
	inmunity=true;
}

void Personaje::moverArriba(){
	b2Vec2 p = this->bodyB2D->GetPosition();
	p.y = -1;
	this->bodyB2D->SetTransform( p, 0);
	cayo = false;
}

long int Personaje::getPuntaje() {
	return this->puntaje;
}

void Personaje::sumarPuntaje(int points) {
	puntaje += points;
}

void Personaje::inBall(b2Body* pos){
	bindball=true;
	posbind=pos;
}

void Personaje::fusionBola(){
	this->bodyB2D->SetTransform(posbind->GetPosition(),0);
	this->camera->reposition(b2Vec2(posbind->GetPosition().x,0));
}

