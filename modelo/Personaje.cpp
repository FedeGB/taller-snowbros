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
	leftOriented = false;
	animationCounter = 0;
	angle = 0;
	isJumping = 0;
	isAirborne = false;
	isMoving = false;
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

bool Personaje::cargarImagen(std::string path){

	if (!IDibujable::cargarImagen(path)) return false;

	//Set sprite clips
	spriteRects[PARADOIZQUIERDA].x =   7;
	spriteRects[PARADOIZQUIERDA].y =   9;
	spriteRects[PARADOIZQUIERDA].w =  23;
	spriteRects[PARADOIZQUIERDA].h = 26;

	spriteRects[MOVIENDOIZQUIERDA1].x =  37;
	spriteRects[MOVIENDOIZQUIERDA1].y =   9;
	spriteRects[MOVIENDOIZQUIERDA1].w =  23;
	spriteRects[MOVIENDOIZQUIERDA1].h = 26;

	spriteRects[MOVIENDOIZQUIERDA2].x = 62;
	spriteRects[MOVIENDOIZQUIERDA2].y =   9;
	spriteRects[MOVIENDOIZQUIERDA2].w =  23;
	spriteRects[MOVIENDOIZQUIERDA2].h = 26;

	spriteRects[MOVIENDOIZQUIERDA3].x = 92;
	spriteRects[MOVIENDOIZQUIERDA3].y =   9;
	spriteRects[MOVIENDOIZQUIERDA3].w =  23;
	spriteRects[MOVIENDOIZQUIERDA3].h = 26;

	spriteRects[MOVIENDOIZQUIERDA4].x = 62;
	spriteRects[MOVIENDOIZQUIERDA4].y =   9;
	spriteRects[MOVIENDOIZQUIERDA4].w =  23;
	spriteRects[MOVIENDOIZQUIERDA4].h = 26;

	spriteRects[SALTANDOIZQUIERDA1].x = 152;
	spriteRects[SALTANDOIZQUIERDA1].y =   6;
	spriteRects[SALTANDOIZQUIERDA1].w =  23;
	spriteRects[SALTANDOIZQUIERDA1].h = 29;

	spriteRects[SALTANDOIZQUIERDA2].x = 184;
	spriteRects[SALTANDOIZQUIERDA2].y =   6;
	spriteRects[SALTANDOIZQUIERDA2].w =  23;
	spriteRects[SALTANDOIZQUIERDA2].h = 29;

	spriteRects[SALTANDOIZQUIERDA3].x = 215;
	spriteRects[SALTANDOIZQUIERDA3].y =   6;
	spriteRects[SALTANDOIZQUIERDA3].w =  23;
	spriteRects[SALTANDOIZQUIERDA3].h = 29;

	spriteRects[SALTANDOIZQUIERDA4].x = 249;
	spriteRects[SALTANDOIZQUIERDA4].y =   6;
	spriteRects[SALTANDOIZQUIERDA4].w =  23;
	spriteRects[SALTANDOIZQUIERDA4].h = 29;

	spriteRects[SALTANDOIZQUIERDA5].x = 118;
	spriteRects[SALTANDOIZQUIERDA5].y =   6;
	spriteRects[SALTANDOIZQUIERDA5].w =  23;
	spriteRects[SALTANDOIZQUIERDA5].h = 29;


	return true;
}

void Personaje::setNewAngle(float32 a){
	angle = a;
}


void Personaje::render(){

	// Determina si el PJ esta en el aire.
	isAirborne = numFootContacts <= 0 ? true : false;

	// Determina, si el PJ esta saltando, si ya termino el salto.
	if (!isAirborne) isJumping = false;

	// Determina si esta sobre un plano inclinado para ajustar el angulo.
	if (!isAirborne) bodyB2D->SetTransform(bodyB2D->GetPosition(), 0);
	else bodyB2D->SetTransform(bodyB2D->GetPosition(), angle);

	std::cout << "esta en el aire: " << isAirborne << " siendo true=" << true << std::endl;
	std::cout << "el numero de footContacts es " << numFootContacts << std::endl;

	float32 desiredVel = 0, scale = 0;

	// Se mueve a la izquierda.
	if (isLeftPressed && wasLeftPressed1st){
		leftOriented=true;
		desiredVel = -14;                         //// VERIFICAR QUE CUANDO ESTE SALTANDO NO CAMBIE LA VELOCIDAD EN Y!! ! ! ! ! ! !  11 1 1 1 1 one one one
		if (angle <= 180 * DEGTORAD) scale = 0.25;
		else scale = 4;
		isMoving = true;
	}

	// Se mueve a la derecha.
	if (isRightPressed && !wasLeftPressed1st){
		leftOriented=false;
		desiredVel = 14;
		scale = 4;
		if (angle <= 180 * DEGTORAD) scale = 4;
		else scale = 0.25;
		isMoving = true;
	}

	// Calcula las velocidades deseadas segun la direccion de movimiento.
	b2Vec2 vel = bodyB2D->GetLinearVelocity();
	float32 velXChange = desiredVel * cos(angle) - vel.x;
	float32 velYChange = 0;
	if ( angle != 0 ) velYChange =  scale * desiredVel * sin(angle) - vel.y ;


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
		float desiredVel = -18;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
		isJumping = true;
	}

	// DETERMINA EL SPRITE QUE CORRESPONDE AL ESTADO DEL PJ.
	animationCounter++;
	switch ((animationCounter/8)){
	case 0:
		if (isAirborne){  // Si esta en el aire:
			if (isJumping) activeSprite = spriteRects[SALTANDOIZQUIERDA1]; // Si salta.
			else activeSprite = spriteRects[SALTANDOIZQUIERDA5]; // Si solo cae.
		}
		else {  // Si esta en el piso.
			if (isMoving) activeSprite = spriteRects[MOVIENDOIZQUIERDA1];
			else activeSprite = spriteRects[PARADOIZQUIERDA];
		}
		break;
	case 1:
		if (isAirborne){
			if (isJumping) activeSprite = spriteRects[SALTANDOIZQUIERDA2];
			else activeSprite = spriteRects[SALTANDOIZQUIERDA5];
		}
		else {
			if (isMoving) activeSprite = spriteRects[MOVIENDOIZQUIERDA2];
			else activeSprite = spriteRects[PARADOIZQUIERDA];
		}
		break;
	case 2:
		if (isAirborne){
			if (isJumping) activeSprite = spriteRects[SALTANDOIZQUIERDA3];
			else activeSprite = spriteRects[SALTANDOIZQUIERDA5];
		}
		else {
			if (isMoving) activeSprite = spriteRects[MOVIENDOIZQUIERDA3];
			else activeSprite = spriteRects[PARADOIZQUIERDA];
		}
		break;
	case 3:
		if (isAirborne){
			if (isJumping) activeSprite = spriteRects[SALTANDOIZQUIERDA4];
			else activeSprite = spriteRects[SALTANDOIZQUIERDA5];
		}
		else {
			if (isMoving) activeSprite = spriteRects[MOVIENDOIZQUIERDA4];
			else activeSprite = spriteRects[PARADOIZQUIERDA];
			animationCounter = 0;
		}
		break;
	default:
		if (isAirborne) activeSprite = spriteRects[SALTANDOIZQUIERDA5];
		else animationCounter = 0;
	}


	// Si ya termino la animacion del salto,o cayo sin saltar, settea el sprite de 'cayendo'.
	//if(bodyB2D->GetLinearVelocity().y>1 && numFootContacts < 1 ){
	//	 activeSprite = spriteRects[SALTANDOIZQUIERDA5];
	//}


	// Convierte los parametros de B2D en los necesarios para renderear el sprite.
	// Obtiene la seccion de la pantalla a renderear.
	int X = (posicion.x - halfWidth) * Window::wRatio;
	int Y = (posicion.y - halfHeight) * Window::hRatio;
	int width = halfWidth * 2 * Window::wRatio;
	int height = halfHeight * 2 * Window::hRatio;
	SDL_Rect pos = {X, Y, width, height};

	// Verifica si tiene que espejar la imagen (si esta mirando hacia la derecha, se espeja).
	SDL_RendererFlip flip;
	if (!leftOriented) flip = SDL_FLIP_HORIZONTAL;
	else flip = SDL_FLIP_NONE;

	// Modifica el angulo para ajustarlo al aspect ratio.
	float32 Yaux = width * sin(angle) * Window::hRatio, Xaux = width * cos(angle) * Window::wRatio;
	float32 modifiedAngle = atan(Yaux/Xaux) * RADTODEG;

	// Renderea.
	SDL_RenderCopyEx( dRenderer, dTextura, &activeSprite, &pos, modifiedAngle, NULL, flip);
}

