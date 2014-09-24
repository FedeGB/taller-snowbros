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
	leftOriented=false;
	animationCounter = 0;
	angle = 0;
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
	spriteRects[PARADOIZQUIERDA].y =   6;
	spriteRects[PARADOIZQUIERDA].w =  23;
	spriteRects[PARADOIZQUIERDA].h = 29;

	spriteRects[MOVIENDOIZQUIERDA1].x =  37;
	spriteRects[MOVIENDOIZQUIERDA1].y =   6;
	spriteRects[MOVIENDOIZQUIERDA1].w =  23;
	spriteRects[MOVIENDOIZQUIERDA1].h = 29;

	spriteRects[MOVIENDOIZQUIERDA2].x = 62;
	spriteRects[MOVIENDOIZQUIERDA2].y =   6;
	spriteRects[MOVIENDOIZQUIERDA2].w =  23;
	spriteRects[MOVIENDOIZQUIERDA2].h = 29;

	spriteRects[MOVIENDOIZQUIERDA3].x = 92;
	spriteRects[MOVIENDOIZQUIERDA3].y =   6;
	spriteRects[MOVIENDOIZQUIERDA3].w =  23;
	spriteRects[MOVIENDOIZQUIERDA3].h = 29;

	spriteRects[MOVIENDOIZQUIERDA4].x = 62;
	spriteRects[MOVIENDOIZQUIERDA4].y =   6;
	spriteRects[MOVIENDOIZQUIERDA4].w =  23;
	spriteRects[MOVIENDOIZQUIERDA4].h = 29;

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

	bodyB2D->SetTransform(bodyB2D->GetPosition(), angle);

	float32 desiredVel = 0, scale = 0;
	if (isLeftPressed && wasLeftPressed1st){
		leftOriented=true;
		desiredVel = -15;
		scale = 0.25;
	}

	if (isRightPressed && !wasLeftPressed1st){
		leftOriented=false;
		desiredVel = 15;
		scale = 4;
	}

	animationCounter++;
	switch ((animationCounter/6)){
	case 0:
		if (numFootContacts >= 1) activeSprite = spriteRects[MOVIENDOIZQUIERDA1];
		else activeSprite = spriteRects[SALTANDOIZQUIERDA1];
		break;
	case 1:
		if (numFootContacts >= 1) activeSprite = spriteRects[MOVIENDOIZQUIERDA2];
		else activeSprite = spriteRects[SALTANDOIZQUIERDA2];
		break;
	case 2:
		if (numFootContacts >= 1) activeSprite = spriteRects[MOVIENDOIZQUIERDA3];
		else activeSprite = spriteRects[SALTANDOIZQUIERDA3];
		break;
	case 3:
		if (numFootContacts >= 1) {
			activeSprite = spriteRects[MOVIENDOIZQUIERDA4];
			animationCounter = 0;
		}
		else activeSprite = spriteRects[SALTANDOIZQUIERDA4];
		break;
	default:
		if (numFootContacts >= 1) animationCounter = 0;
		else activeSprite = spriteRects[SALTANDOIZQUIERDA5];
	}

	b2Vec2 vel = bodyB2D->GetLinearVelocity();
	float32 velXChange = desiredVel * cos(angle) - vel.x;
	float32 velYChange = 0;
	if ( angle != 0 ) velYChange =  scale * desiredVel * sin(angle) - vel.y ;

	if (!isRightPressed && !isLeftPressed ){
			velXChange = -vel.x; // I want the PJ to stop moving in the X axis.
			velYChange = 0; // I want the PJ to keep moving normally in the Y axis.
			if(numFootContacts >= 1){
				activeSprite = spriteRects[PARADOIZQUIERDA];
			animationCounter = 0;}
	}

	float impulseX = bodyB2D->GetMass() * velXChange;
	float impulseY = bodyB2D->GetMass() * velYChange;
	bodyB2D->ApplyLinearImpulse( b2Vec2(impulseX, impulseY), bodyB2D->GetWorldCenter(), true);


	if (isUpPressed && (numFootContacts >= 1)){
		b2Vec2 vel = bodyB2D->GetLinearVelocity();
		float desiredVel = -15;
		float velChange = desiredVel - vel.y;
		float impulse = bodyB2D->GetMass() * velChange;
		bodyB2D->ApplyLinearImpulse( b2Vec2(0,impulse), bodyB2D->GetWorldCenter(), true);
		animationCounter = 0;
	}

	if(bodyB2D->GetLinearVelocity().y>1 && numFootContacts < 1 ){
		 activeSprite = spriteRects[SALTANDOIZQUIERDA5];
	}

	int X = (posicion.x - halfWidth) * Window::wRatio;
	int Y = (posicion.y - halfHeight) * Window::hRatio;
	int width = halfWidth * 2 * Window::wRatio;
	int height = halfHeight * 2 * Window::hRatio;
	SDL_Rect pos = {X, Y, width, height};

	SDL_RendererFlip flip;
	if ((isRightPressed && !wasLeftPressed1st)||!leftOriented) flip = SDL_FLIP_HORIZONTAL;
	else flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx( dRenderer, dTextura, &activeSprite, &pos, angle * RADTODEG, NULL, flip);
}

