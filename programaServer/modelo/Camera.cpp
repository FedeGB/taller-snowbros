/*
 * Camera.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: rodrizapico
 */

#include "Camera.h"
#include <iostream>

float Camera::WINDOWTOWORLDSCALE, Camera::WORLDTOWINDOWSCALE;

Camera::Camera(ThreadSafeList<WorldItem*> & rList, int windowWidth, int windowHeight,
		float32 windowToWorldScale): renderList(rList){
	cameraB2D = NULL;
	width = windowWidth;
	height = windowHeight;
	WINDOWTOWORLDSCALE = windowToWorldScale;
	WORLDTOWINDOWSCALE = 1.0f / WINDOWTOWORLDSCALE;
	canMoveLeft = canMoveRight = canMoveUp = canMoveDown = true;
	PJ = NULL;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::eventoArriba(){}
void Camera::eventoSoltoArriba(){}
void Camera::eventoDerecha(){}
void Camera::eventoSoltoDerecha(){}
void Camera::eventoIzquierda(){}
void Camera::eventoSoltoIzquierda(){}
void Camera::eventoRESTART(){}

void Camera::eventoZoomIn(){

	b2Vec2 posPJCamera;
	b2Body * body;

	static int count = -1;
	count++;
	if (count % 4 != 0) return;

	bool contactFound = false;
	// Hallo la posicion relativa del personaje respecto a la camara, para mantenerla luego de zoomear.
	for (b2ContactEdge* ce = cameraB2D->GetContactList(); ce; ce = ce->next) {
		void* fixtureAUserData = ce->contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = ce->contact->GetFixtureB()->GetUserData();

		if ( *((int*)(&fixtureAUserData)) == 3 || *((int*)(&fixtureBUserData)) == 3 ) {
			if ( *((int*)(&fixtureAUserData)) == 3 ) body = ce->contact->GetFixtureA()->GetBody();
			else body = ce->contact->GetFixtureB()->GetBody();

			// Determino la posicion del PJ relativo al origen de coordenadas de la camara.
			posPJCamera = body->GetPosition() - cameraB2D->GetPosition();
			posPJCamera.x += (width / 2) * WINDOWTOWORLDSCALE;
			posPJCamera.y += (height / 2) * WINDOWTOWORLDSCALE + 1.3f;//( (Personaje *) body->GetUserData() )->getHeight() / 2;
			posPJCamera.x = posPJCamera.x / (width * WINDOWTOWORLDSCALE);
			posPJCamera.y = posPJCamera.y / (height * WINDOWTOWORLDSCALE);

			contactFound = true;
			break;
		}
	}

	if (!contactFound) {
		std::cout << "no se encontro PJ. " << std::endl;
		eventoZoomOut();
		return;
	}

	std::cout << "Se encontro PJ. " << std::endl;
	std::cout << "la posicion relativa es: " << posPJCamera.x << ", " << posPJCamera.y << std::endl;

	if (WINDOWTOWORLDSCALE < 0.01) return;


	WINDOWTOWORLDSCALE -= 0.001f;
	WORLDTOWINDOWSCALE = 1.0f / WINDOWTOWORLDSCALE;


	// Resizeo el objeto B2D asociado a la camara de acuerdo al nuevo zoom.
	cameraB2D->DestroyFixture(cameraB2D->GetFixtureList());
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;
	float32 halfWidth = (width / 2) * WINDOWTOWORLDSCALE;
	float32 halfHeight = (height / 2) * WINDOWTOWORLDSCALE;
	polygon.SetAsBox(halfWidth, halfHeight);
	myFixtureDef.shape = &polygon;
	myFixtureDef.isSensor = true;

	b2Fixture * bodyFixture = cameraB2D->CreateFixture(&myFixtureDef);
	bodyFixture->SetUserData( (void*)4 );


	// Recalculo la posicion de la camara para mantener la posicion relativa del personaje.
	b2Vec2 newPosCamera;
	newPosCamera.x = body->GetPosition().x - posPJCamera.x * (width * WINDOWTOWORLDSCALE) + (width / 2) * WINDOWTOWORLDSCALE;
	newPosCamera.y = body->GetPosition().y + + 1.3f //( (Personaje *) body->GetUserData() )->getHeight() / 2
			- posPJCamera.y * (height * WINDOWTOWORLDSCALE) + (height / 2) * WINDOWTOWORLDSCALE;

	cameraB2D->SetTransform(newPosCamera, 0);
}
void Camera::eventoZoomOut(){

	calculateBorderConstraints();
	std::cout << "la condicion de borde inferior es: " << canMoveDown << " con true = " << true << std::endl;
	bool minZoomReached = false;
	if(!canMoveRight || !canMoveLeft) minZoomReached = true;
	if(!canMoveUp || !canMoveDown) minZoomReached = true;

	if (minZoomReached) return;
	WINDOWTOWORLDSCALE += 0.001f;
	WORLDTOWINDOWSCALE = 1.0f / WINDOWTOWORLDSCALE;

	cameraB2D->DestroyFixture(cameraB2D->GetFixtureList());

	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;
	float32 halfWidth = (width / 2) * WINDOWTOWORLDSCALE;
	float32 halfHeight = (height / 2) * WINDOWTOWORLDSCALE;
	polygon.SetAsBox(halfWidth, halfHeight);
	myFixtureDef.shape = &polygon;
	myFixtureDef.isSensor = true;

	b2Fixture * bodyFixture = cameraB2D->CreateFixture(&myFixtureDef);
	bodyFixture->SetUserData( (void*)4 );
}

void Camera::setB2DBody(b2Body * cB2D){
	cameraB2D = cB2D;
}

void Camera::setPJ(b2Body * pjB2D){
	PJ = pjB2D;
}

void Camera::setWINDOWTOWORLDSCALE(float32 windowToWorld){
	WINDOWTOWORLDSCALE = windowToWorld;
	WORLDTOWINDOWSCALE = 1.0f / WINDOWTOWORLDSCALE;
}

void Camera::calculateBorderConstraints(){

	canMoveLeft = canMoveRight = canMoveUp = canMoveDown = true;

	for (b2ContactEdge* ce = cameraB2D->GetContactList(); ce; ce = ce->next) {

		void* fixtureAUserData = ce->contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = ce->contact->GetFixtureB()->GetUserData();

		b2Vec2 pos;
		// World left border.
		if ( *((int*)(&fixtureAUserData)) == 5 || *((int*)(&fixtureBUserData)) == 5 ) {
			canMoveLeft = false;
		}
		// World right border.
		else if ( *((int*)(&fixtureAUserData)) == 6 || *((int*)(&fixtureBUserData)) == 6 ) {
			canMoveRight = false;
		}
		// World upper border.
		else if ( *((int*)(&fixtureAUserData)) == 7 || *((int*)(&fixtureBUserData)) == 7 ) {
			canMoveUp = false;
		}
		// World bottom border.
		else if ( *((int*)(&fixtureAUserData)) == 8 || *((int*)(&fixtureBUserData)) == 8 ) {
			canMoveDown = false;
		}
	}
}

void Camera::updatePosition(){

	// Calcula en que direcciones es posible mover la camara.
	calculateBorderConstraints();

	// Determino la posicion del PJ relativo al origen de coordenadas de la camara.
	b2Vec2 posPJCamera = PJ->GetPosition() - cameraB2D->GetPosition();
	posPJCamera.x += (width / 2) * WINDOWTOWORLDSCALE;
	posPJCamera.y += (height / 2) * WINDOWTOWORLDSCALE;

	//std::cout << " la posicion relativa del PJ es : " << posPJCamera.x / ( width * WINDOWTOWORLDSCALE ) << ", " << posPJCamera.y / ( height * WINDOWTOWORLDSCALE ) << std::endl;
	//std::cout << " la posicion del borde inf der es: " << width * WINDOWTOWORLDSCALE << ", " << height * WINDOWTOWORLDSCALE << std::endl;

	// Determino el impulso necesario para mover en X la camara.
	float32 desiredXVel = 0;
	if ( (posPJCamera.x > width * WINDOWTOWORLDSCALE * 0.7 && canMoveRight && PJ->GetLinearVelocity().x >= 0) ||
			(posPJCamera.x < width * WINDOWTOWORLDSCALE * 0.3 && canMoveLeft && PJ->GetLinearVelocity().x <= 0) ){
		desiredXVel = 1.05f * PJ->GetLinearVelocity().x;
	}

	b2Vec2 vel = cameraB2D->GetLinearVelocity();
	float32 velXChange = desiredXVel - vel.x;
	float impulseX = cameraB2D->GetMass() * velXChange;

	// Determino el impulso necesario para mover en Y la camara.
	float32 desiredYVel = 0;
	if ( (posPJCamera.y > height * WINDOWTOWORLDSCALE * 0.7 && canMoveDown && PJ->GetLinearVelocity().y > 0) ||
			(posPJCamera.y < height * WINDOWTOWORLDSCALE * 0.3 && canMoveUp && PJ->GetLinearVelocity().y < 0) ){
		desiredYVel = 1.05f * PJ->GetLinearVelocity().y;
	}

	float32 velYChange = desiredYVel - vel.y;
	float impulseY = cameraB2D->GetMass() * velYChange;

	// Aplico el impulso calculado para mover la camara.
	cameraB2D->ApplyLinearImpulse( b2Vec2(impulseX, impulseY), cameraB2D->GetWorldCenter(), true);
}

void Camera::updateRenderList(){

	// Bloquea renderList, para evitar que se modifique mientras se la esta cargando.
	renderList.lock();

	// Vacia la lista.
	renderList.clear();
	//while (!renderList.empty())	renderList.pop_back();

	// Itera sobre todos los objetos que esten en contacto con la camara,
	// obteniendo sus modelos y agregandolos a la lista de objetos a renderear
	// por el cliente.
	for (b2ContactEdge* ce = cameraB2D->GetContactList(); ce; ce = ce->next) {
		b2Body * body;

		// Obtiene la informacion sobre los fixtures que estan en contacto.
		// (la camara + el cuerpo)
		void* fixtureAUserData = ce->contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = ce->contact->GetFixtureB()->GetUserData();

		// Obtiene la informacion del cuerpo que esta en contacto con la camara.
		// TODO: sacar estas constantes hardcodeadas.
		if ( *((int*)(&fixtureAUserData)) != 4 ) body = ce->contact->GetFixtureA()->GetBody();
		else body = ce->contact->GetFixtureB()->GetBody();

		// Saltea los bordes del mundo.
		// TODO: sacar estas constantes hardcodeadas.
		if ( *((int*)(&fixtureAUserData)) == 5 || *((int*)(&fixtureAUserData)) == 6 ||
				*((int*)(&fixtureAUserData)) == 7 || *((int*)(&fixtureAUserData)) == 8)
			continue;
		else if ( *((int*)(&fixtureBUserData)) == 5 || *((int*)(&fixtureBUserData)) == 6 ||
				*((int*)(&fixtureBUserData)) == 7 || *((int*)(&fixtureBUserData)) == 8)
			continue;

		// Saltea los apendices de los personajes.
		// TODO: sacar estas constantes hardcodeadas.
		if ( *((int*)(&fixtureAUserData)) == 3 || *((int*)(&fixtureBUserData)) == 3 )
			continue;

		// Actualiza la posicion y angulo.
		// TODO: ESCALA HARDCODEADA!!!
		b2Vec2 pos = body->GetPosition() - cameraB2D->GetPosition();
		pos.x += (width / 2) * 0.05f;
		pos.y += (height / 2) * 0.05f;
		((WorldItem*)body->GetUserData())->posicion = pos;
		((WorldItem*)body->GetUserData())->angulo = body->GetAngle();

		// Agrega a la lista de cosas a renderear.
		renderList.push_back( ((WorldItem*)body->GetUserData()) );
	}

	// Ya finalizo de cargar la lista, la libera.
	renderList.unlock();
}

void Camera::update(){

	// Mueve la camara segun la posicion del PJ al que esta asociada.
	updatePosition();

	// Actualiza la lista de objetos en el scope de la camara, que deben
	// ser rendereados por el cliente.
	updateRenderList();

}
