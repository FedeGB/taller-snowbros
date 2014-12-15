/*
 * Fabrica.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: rodrizapico
 */

#include "Fabrica.h"

Fabrica::Fabrica(ControladorJuego * c) {
	controlador = c;
}

Fabrica::~Fabrica() {
	// TODO Auto-generated destructor stub
}

// Fabrica una bola de nieve y la agrega al modelo.
void Fabrica::fabricarBolaDeNieve(Personaje * creador){

	BolaDeNieve * bola = new BolaDeNieve();

	b2Vec2 posicion = creador->cuerpoB2D->GetPosition();
	b2Vec2 velocidad = creador->cuerpoB2D->GetLinearVelocity();
	b2World * mundo = creador->cuerpoB2D->GetWorld();

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;
	b2dObjDef.type = b2_dynamicBody;
	b2dObjDef.gravityScale = 1;
	b2dObjDef.position.Set(posicion.x, posicion.y);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;
	b2dObjDef.bullet=true;
//	cayo = false;

	bola->cuerpoB2D = mundo->CreateBody(&b2dObjDef);
	bola->cuerpoB2D->SetUserData(bola);

	float32 halfWidth = 0.5f; // TODO: 0.05f = windowToWorldScale. HARDCODEADO!!!
	float32 halfHeight = 0.5f; // 0.05f = windowToWorldScale. HARDCODEADO!!!
	polygon.SetAsBox(halfWidth, halfHeight);
	myFixtureDef.shape = &polygon;
	myFixtureDef.isSensor = true;


	b2Fixture * bodyFixture = bola->cuerpoB2D->CreateFixture(&myFixtureDef);
	bodyFixture->SetUserData( (void*)PODERHIELO );

	float escala = creador->sorpresaNieveLejosActiva ? 2.5f : 1.0f;

	if(creador->orientacion == ObjetoModelo::IZQUIERDA)
		bola->cuerpoB2D->SetLinearVelocity(b2Vec2(-25.0f * escala + velocidad.x, -5.0f * escala));
	else
		bola->cuerpoB2D->SetLinearVelocity(b2Vec2(25.0f * escala + velocidad.x, -5.0f * escala));



	bola->paraDestruir = false;
	bola->modificado = true;
	bola->rotacion = 0.0f;
	bola->orientacion = creador->orientacion;
	if (creador->sorpresaNievePotenteActiva) bola->danio = 5;
	else bola->danio = 1;

	bola->espacioOcupado = FiguraGeometrica::generarRectangulo(posicion.x, posicion.y, 0.5, 0.5, 0);
	//hasAtacked=false;

	bola->inicializar();
	controlador->modelo.agregarObjeto(bola);
}

// Fabrica una bola de fuego y la agrega al modelo.
void Fabrica::fabricarBolaDeFuego(EnemigoFuego * creador){

	BolaDeFuego * bola = new BolaDeFuego();

	b2Vec2 posicion = creador->cuerpoB2D->GetPosition();
	b2Vec2 velocidad = creador->cuerpoB2D->GetLinearVelocity();
	b2World * mundo = creador->cuerpoB2D->GetWorld();

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;
	b2dObjDef.type = b2_dynamicBody;
	b2dObjDef.gravityScale = 1;
	b2dObjDef.position.Set(posicion.x, posicion.y);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;
	b2dObjDef.bullet=true;
//	cayo = false;

	bola->cuerpoB2D = mundo->CreateBody(&b2dObjDef);
	bola->cuerpoB2D->SetUserData(bola);

	float32 halfWidth = 0.5f; // TODO: 0.05f = windowToWorldScale. HARDCODEADO!!!
	float32 halfHeight = 0.5f; // 0.05f = windowToWorldScale. HARDCODEADO!!!
	polygon.SetAsBox(halfWidth, halfHeight);
	myFixtureDef.shape = &polygon;
	myFixtureDef.isSensor = true;


	b2Fixture * bodyFixture = bola->cuerpoB2D->CreateFixture(&myFixtureDef);
	bodyFixture->SetUserData( (void*)PODERFUEGO );
	if(creador->orientacion == ObjetoModelo::IZQUIERDA)
		bola->cuerpoB2D->SetLinearVelocity(b2Vec2(-25.0f + velocidad.x, -5.0f));
	else
		bola->cuerpoB2D->SetLinearVelocity(b2Vec2(25.0f + velocidad.x, -5.0f));



	bola->paraDestruir = false;
	bola->modificado = true;
	bola->rotacion = 0.0f;
	bola->orientacion = creador->orientacion;
	bola->danio = 1;

	bola->espacioOcupado = FiguraGeometrica::generarRectangulo(posicion.x, posicion.y, 0.5, 0.5, 0);
	//hasAtacked=false;

	bola->inicializar();
	controlador->modelo.agregarObjeto(bola);
}


// Fabrica una pelota de nieve y la agrega al modelo.
void Fabrica::fabricarPelotaDeNieve(Enemigo * creador){

	PelotaDeNieve * pelota = new PelotaDeNieve();

	b2Vec2 posicion = creador->cuerpoB2D->GetPosition();
	b2World * mundo = creador->cuerpoB2D->GetWorld();

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;

	b2dObjDef.type = b2_dynamicBody;
	b2dObjDef.bullet = true;

	b2dObjDef.position.x = posicion.x;
	b2dObjDef.position.y = posicion.y;

	circle.m_radius = 1.5; //defino el tamaño
	myFixtureDef.shape = &circle; //defino que es un circulo

	//lo vinculo al mundo
	pelota->cuerpoB2D = mundo->CreateBody(&b2dObjDef);
	pelota->cuerpoB2D->SetUserData(pelota);

	myFixtureDef.density =100.0f; //le doy masa
	myFixtureDef.restitution = 0.4f;
	myFixtureDef.friction = 0.3f;

	b2Fixture * shapeFixture = pelota->cuerpoB2D->CreateFixture(&myFixtureDef); //le asigno la forma
	shapeFixture->SetUserData((void*) BOLASNOW);

	if(creador->orientacion == ObjetoModelo::IZQUIERDA)
		pelota->cuerpoB2D->ApplyLinearImpulse(b2Vec2(-100000.0f,0), pelota->cuerpoB2D->GetWorldCenter(),true);
	else
		pelota->cuerpoB2D->ApplyLinearImpulse(b2Vec2(100000.0f,0), pelota->cuerpoB2D->GetWorldCenter(),true);

	pelota->paraDestruir = false;
	pelota->modificado = true;
	pelota->rotacion = 0.0f;
	pelota->orientacion = creador->orientacion;

	pelota->espacioOcupado = FiguraGeometrica::generarRectangulo(posicion.x, posicion.y, 3, 3, 0);
	Vector2D aux; aux.x = posicion.x; aux.y = posicion.y;
	Vector2D traslacion = pelota->espacioOcupado->calcularBaricentro() - aux;
	pelota->espacioOcupado->trasladar(traslacion);
	//hasAtacked=false;

	pelota->inicializar();
	controlador->modelo.agregarObjeto(pelota);
}

// Fabrica una sorpresa y la agrega al modelo.
void Fabrica::fabricarSorpresa(PelotaDeNieve * creador){

	Sorpresa * sorpresa;

	int random = rand();
	switch (random % 3){
	case 0:
		sorpresa = new SorpresaNieveMaLejos();
		break;
	case 1:
		sorpresa = new SorpresaNieveMasPotente();
		break;
	case 2:
		sorpresa = new SorpresaCorrer();
		break;
	}

	b2Vec2 posicion = creador->cuerpoB2D->GetPosition();
	b2World * mundo = creador->cuerpoB2D->GetWorld();

	// seteo el bodyDef
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.gravityScale = 0;
	bodyDef.position.Set(posicion.x, posicion.y);
	bodyDef.angle = 0;
	bodyDef.fixedRotation = true;
	bodyDef.bullet = true;

	sorpresa->cuerpoB2D = mundo->CreateBody(&bodyDef);

	// seteo el poligono
	b2PolygonShape caja;
	caja.SetAsBox(0.5, 0.5);

	// seteo la fixtureDef
	b2FixtureDef fixtDef;
	fixtDef.shape = &caja;
	fixtDef.density =  1.5f;
	fixtDef.restitution = 0.5f;
	fixtDef.friction=5.2;
	fixtDef.isSensor = true;

	b2Fixture * fixt = sorpresa->cuerpoB2D->CreateFixture(&fixtDef);
	fixt->SetUserData( (void*) sensorSORPRESA );
	sorpresa->cuerpoB2D->SetUserData(sorpresa);

	sorpresa->paraDestruir = false;
	sorpresa->modificado = true;
	sorpresa->rotacion = 0.0f;
	sorpresa->orientacion = creador->orientacion;

	sorpresa->espacioOcupado = FiguraGeometrica::generarRectangulo(posicion.x, posicion.y, 0.5, 0.5, 0);
	Vector2D aux; aux.x = posicion.x; aux.y = posicion.y;
	Vector2D traslacion = sorpresa->espacioOcupado->calcularBaricentro() - aux;
	sorpresa->espacioOcupado->trasladar(traslacion);
	//hasAtacked=false;

	sorpresa->inicializar();
	controlador->modelo.agregarObjeto(sorpresa);

}
