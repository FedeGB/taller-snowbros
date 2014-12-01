/*
 * snowball.cpp
 *
 *  Created on: 12/11/2014
 *      Author: coco
 */

#include "snowball.h"

snowball::~snowball() {
	this->poder->GetWorld()->DestroyBody(this->poder);
	this->poder=NULL;
}

snowball::snowball() {
	// TODO Auto-generated constructor stub

}
snowball::snowball(float32 posx,float32 posy,int orientation,b2World * world, float damage, float impulsoNieve, b2Vec2 vel_pj) {

		b2BodyDef b2dObjDef;
		b2FixtureDef myFixtureDef;
		b2PolygonShape polygon;
		b2dObjDef.type = b2_dynamicBody;
		b2dObjDef.gravityScale = 1;
		b2dObjDef.position.Set(posx, posy-1);
		b2dObjDef.angle = 0;
		b2dObjDef.fixedRotation = true;
	//	b2dObjDef.bullet=true;

		poder = world->CreateBody(&b2dObjDef);

		float32 halfWidth = 1.0f; // TODO: 0.05f = windowToWorldScale. HARDCODEADO!!!
		float32 halfHeight = 1.0f; // 0.05f = windowToWorldScale. HARDCODEADO!!!
		polygon.SetAsBox(halfWidth, halfHeight);
		myFixtureDef.shape = &polygon;
		myFixtureDef.isSensor = true;


		b2Fixture * bodyFixture = poder->CreateFixture(&myFixtureDef);
		bodyFixture->SetUserData( (void*)PODERHIELO );
		activeSprite=BOLANIEVE1;
		if(orientation==LEFT)
			poder->SetLinearVelocity(b2Vec2(-15.0f*impulsoNieve + vel_pj.x,-2.0f*impulsoNieve));
		else
			poder->SetLinearVelocity(b2Vec2(15.0f*impulsoNieve + vel_pj.x,-2.0f*impulsoNieve));
		toDelete = false;
		dmg = damage;
		std::cout<< "snowball constructor:" << damage << '\n';
		poder->SetUserData(this);
		hasAtacked=false;

}

std::string snowball::serializar(){

	std::string buffer;
	buffer = SSTR(NIEVE << " " << posicion.x << " " << posicion.y << " "
			<< angulo << "  " << baseMayor << " " << altura << " "
			<< activeSprite );
	return buffer;
}

void snowball::setDelete() {
	toDelete = true;
}
bool snowball::forDelete() {
	return toDelete;
}

float snowball::getDamage() {
	if(!hasAtacked){
		return this->dmg;
		hasAtacked=true;
	}
	return 0;
}

