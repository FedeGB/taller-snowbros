/*
 * Sorpresa.h
 *
 *  Created on: 17/11/2014
 *      Author: manuel
 */

#ifndef SORPRESA_H_
#define SORPRESA_H_

#include "../utiles/tipos.h"

class Sorpresa: public Cuadrilatero {
public:
	Sorpresa(){
		activeSprite = SORPRESA1;
		cuerpoB2D = NULL;
		toDelete = false;
	}
	virtual ~Sorpresa(){
		this->cuerpoB2D->GetWorld()->DestroyBody(this->cuerpoB2D);
	}

	sprite_t activeSprite;

	void agregarAMundo(float32 x, float32 y, b2World* w){
		// seteo el bodyDef
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.gravityScale = 2;
		bodyDef.position.Set(x, y-1);
		bodyDef.angle = 0;
		bodyDef.fixedRotation = true;
		bodyDef.bullet = true;

		cuerpoB2D = w->CreateBody(&bodyDef);

		// seteo el poligono
		b2PolygonShape caja;
		caja.SetAsBox(0.5, 0.5);

		// seteo la fixtureDef
		b2FixtureDef fixtDef;
		fixtDef.shape = &caja;
		fixtDef.density =  1.5f;
		fixtDef.restitution = 0.5f;
		fixtDef.friction=5.2;

		b2Fixture * fixt = cuerpoB2D->CreateFixture(&fixtDef);
		fixt->SetUserData( (void*) sensorSORPRESA );
		cuerpoB2D->SetLinearVelocity( b2Vec2(2.0f,-2.0f) );
		cuerpoB2D->SetUserData(this);
	}

	void setDelete(){
		toDelete = true;
	}

	bool forDelete(){
		return toDelete;
	}

protected:

	b2Body* cuerpoB2D;

	bool toDelete;

	virtual void aplicarSorpresaAlPJ(){}

	std::string serializar(){

		std::string buffer;
		buffer = SSTR(SORPRESA << " " << posicion.x << " " << posicion.y << " "
				<< angulo << "  " << baseMayor << " " << altura << " "
				<< activeSprite );
		return buffer;
	}
};



#endif /* SORPRESA_H_ */
