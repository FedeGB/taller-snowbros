/*
 * ControladorEnemigos.h
 *
 *  Created on: Nov 8, 2014
 *      Author: fedevm
 */

#ifndef CONTROLADORENEMIGOS_H_
#define CONTROLADORENEMIGOS_H_

#define RADMIN 50.0f

#include "../modelo/EnemigoEstandar.h"
#include "../ControladorUsuarios.h"


class ControladorEnemigos: public map <int, EnemigoEstandar*> {
public:
	ControladorEnemigos();
	~ControladorEnemigos();
	void controlUnit(EnemigoEstandar*);
	void strategy(b2World*, ControladorUsuarios PJs);

	void update(bool);

private:
	void standarStrategy(EnemigoEstandar* unit, b2World* world, ControladorUsuarios PJs);
	b2Vec2 closerPJ(b2World* world, b2Vec2 unit, ControladorUsuarios PJs);
	bool isObjectInDirection(b2World* world, EnemigoEstandar* unit, sensor_t obj, float angle, float length);
	teclas_t getAction(EnemigoEstandar* unit, b2Vec2 enemy, b2World* world);
};


#endif /* CONTROLADORENEMIGOS_H_ */
