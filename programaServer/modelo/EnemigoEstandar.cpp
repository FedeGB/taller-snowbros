/*
 * EnemigoEstandar.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: fedevm
 */

#include "EnemigoEstandar.h"
#include "../utiles/tipos.h"
#include "formas/Circulo.h"

EnemigoEstandar::EnemigoEstandar(int number){
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
	vida = 10;
	isTrapped = false;
	stunCounter=0;
	isPushable=false;
}

EnemigoEstandar::~EnemigoEstandar() {
	orientation_t temp=this->pushOrientation;


	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	WorldItem * figura;

	b2dObjDef.type = b2_dynamicBody;
	b2dObjDef.bullet = true;

	b2dObjDef.position.x = this->bodyB2D->GetPosition().x;
	b2dObjDef.position.y = this->bodyB2D->GetPosition().y;

	circle.m_radius = 1.5f; //defino el tamaño
	myFixtureDef.shape = &circle; //defino que es un circulo

			// Determina el tipo de figura para poder dibujarla.
	Circulo * circ = new Circulo();
	circ->radio = circle.m_radius;
	figura = circ;
	//lo vinculo al mundo
	b2Body *_shape = this->bodyB2D->GetWorld()->CreateBody(&b2dObjDef);
	myFixtureDef.density =1.0f; //le doy masa
	myFixtureDef.restitution = 0.15f;

	myFixtureDef.friction = 0.3f;

		b2Fixture * shapeFixture = _shape->CreateFixture(&myFixtureDef); //le asigno la forma
		if (b2dObjDef.type == b2_dynamicBody) shapeFixture->SetUserData((void*) DINAMICO);
		else {
			shapeFixture->SetUserData((void*) ESTATICO);
		}

		//Me fijo si el objeto que creo es atravesable.

		// Setea los ultimos parametros de la figura y vincula al bodyB2D.
		figura->posicion.x = b2dObjDef.position.x;
		figura->posicion.y = b2dObjDef.position.y;
		figura->angulo = b2dObjDef.angle;
		_shape->SetUserData(figura);
		if(temp==LEFT)
			_shape->ApplyForceToCenter(b2Vec2(10.0f,0),true);
		else
			_shape->ApplyForceToCenter(b2Vec2(10.0f,0),true);

	this->bodyB2D->GetWorld()->DestroyBody(this->bodyB2D);
};

std::string EnemigoEstandar::serializar(){

	std::string buffer;
	buffer = SSTR(ENEMIGOESTANDAR << " " << posicion.x << " " << posicion.y << " "
			<< angulo << "  " << baseMayor << " " << altura << " "
			<< activeSprite << " " << orientation<<" "<<spriteStun);
	return buffer;
}

void EnemigoEstandar::update(){
	// Determina si esta en el aire.
	isAirborne = numFootContacts <= 0 ? true : false;
	if(vida<=0) spriteStun=STUN0;
	else if(vida<=3) spriteStun=STUN3;
	else if(vida<=6) spriteStun=STUN2;
	else if(vida<10) spriteStun=STUN1;
	else if(vida>=10) spriteStun=STUN0;

	if(isPushable){
		animationCounter++;
			if(pushOrientation==LEFT)
				bodyB2D->ApplyLinearImpulse( b2Vec2(-10.0f, 0.0), bodyB2D->GetWorldCenter(), true);
			else
				bodyB2D->ApplyLinearImpulse( b2Vec2(10.0f, 0.0), bodyB2D->GetWorldCenter(), true);
			if(animationCounter==200)
				isPushable=false;
			return;
		}

	if(isFrozzen){
		stunCounter++;
		if(stunCounter==10000){
			isFrozzen=false;
			for(b2Fixture * fix= bodyB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
				void* userData =fix->GetUserData();
				if(*((int*)(&userData))==ENEMIGOBOLA) fix->SetUserData((void*)ENEMIGOCONGELADO);
				if(*((int*)(&userData))==PIESENBOLA) fix->SetUserData((void*)PIESENCONGELADO);
			}
		}
		activeSprite=CONGELADO;
		return;
	}

	if(isTrapped) {
		// TODO: Acciones a realizar si esta atrapado
		animationCounter++;
		if(animationCounter<100)
			activeSprite=ATRAPADO1;
		else if (animationCounter<200)
			activeSprite=ATRAPADO2;
		else {animationCounter=0;
				stunCounter++;
		}
		if(stunCounter>=10){
			vida++;
			stunCounter=0;
		}
		if(vida>=10){
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
			// TODO: En ContactListener falta contacto con plataformas
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

void EnemigoEstandar::eventoSpace() {
	std::cout<<"space";
	isSpacePressed = true;
}

void EnemigoEstandar::eventoSoltoSpace() {
	isSpacePressed = false;
}

void EnemigoEstandar::eventoAbajo() {
	isDownPressed = true;
}

void EnemigoEstandar::eventoSoltoAbajo() {
	isDownPressed = false;
}

void EnemigoEstandar::setOnBorder(bool border) {
	isOnBorder = border;
}
bool EnemigoEstandar::itsOnBorder() {
	return isOnBorder;
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
bool EnemigoEstandar::trapped() {
	return isTrapped;
}

void EnemigoEstandar::applyDamage(float dmg) {
	stunCounter=0;
	if(!isTrapped) {
		isTrapped = true;
		animationCounter=0;
		for(b2Fixture * fix= bodyB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
			void* userData =fix->GetUserData();
			if(*((int*)(&userData))==ENEMIGO){
				fix->SetUserData((void*)ENEMIGOCONGELADO);
			}
			if(*((int*)(&userData))==PIESEN)
							fix->SetUserData((void*)PIESENCONGELADO);
		}

	}
	vida -= 1;//TODO: dmg no se por que tiene basura por eso harcodie este 1
	if (vida<0){
		isFrozzen=true;
		vida=0;
		for(b2Fixture * fix= bodyB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
						void* userData =fix->GetUserData();
								if(*((int*)(&userData))==ENEMIGOCONGELADO)
									fix->SetUserData((void*)ENEMIGOBOLA);
								if(*((int*)(&userData))==PIESENCONGELADO)
												fix->SetUserData((void*)PIESENBOLA);
							}
	}
//	std::cout<<dmg<<std::endl;
}

void EnemigoEstandar::empujar(orientation_t ori){
	setDelete();

}

void EnemigoEstandar::Noempujar(){
		//isPushable=false;
}

