/*
 * Fireball.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: fedevm
 */

#include "Fireball.h"

Fireball::Fireball(){
}

Fireball::Fireball(float32 posx,float32 posy,int orientation,b2World * world, float damage, float potenciaFuego, float impulsoFuego, b2Vec2 vel_unit) {
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;
	b2dObjDef.type = b2_dynamicBody;
	b2dObjDef.gravityScale = 1;
	b2dObjDef.position.Set(posx, posy-1);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;

	poder = world->CreateBody(&b2dObjDef);

	float32 halfWidth = 1.0f; // TODO: 0.05f = windowToWorldScale. HARDCODEADO!!!
	float32 halfHeight = 1.0f; // 0.05f = windowToWorldScale. HARDCODEADO!!!
	polygon.SetAsBox(halfWidth, halfHeight);
	myFixtureDef.shape = &polygon;
	myFixtureDef.isSensor = true;


	b2Fixture * bodyFixture = poder->CreateFixture(&myFixtureDef);
	bodyFixture->SetUserData( (void*)PODERFUEGO );
	activeSprite=BOLAFUEGO1;
	if(orientation==LEFT)
		poder->SetLinearVelocity(b2Vec2(-15.0f*impulsoFuego + vel_unit.x,-2.0f*impulsoFuego));
	else
		poder->SetLinearVelocity(b2Vec2(15.0f*impulsoFuego + vel_unit.x,-2.0f*impulsoFuego));
	toDelete = false;
	dmg = damage;
	std::cout<< "fireball constructor:" << damage << '\n';
	poder->SetUserData(this);
	hasAtacked=false;

}

Fireball::~Fireball() {
	this->poder->GetWorld()->DestroyBody(this->poder);
}



std::string Fireball::serializar(){
	std::string buffer;
	buffer = SSTR(FUEGO << " " << posicion.x << " " << posicion.y << " "
		<< angulo << "  " << baseMayor << " " << altura << " "
		<< activeSprite );
	return buffer;
}


