/*
 * ControladorEnemigos.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: fedevm
 */

#include "ControladorEnemigos.h"
//#include <cstdlib>
#include "../control/RayCaster.h"
#include <random>

ControladorEnemigos::ControladorEnemigos(){}

ControladorEnemigos::~ControladorEnemigos(){}

void ControladorEnemigos::controlUnit(EnemigoEstandar* unit) {
	(*this)[unit->enemyNumber] = unit;
}

void ControladorEnemigos::strategy(b2World* world, ControladorUsuarios PJs) {
	if(world) {
		for(ControladorEnemigos::iterator it = (*this).begin(); it != (*this).end(); ++it) {
			if((*it).second && (*it).second->tipo == ENEMIGOESTANDAR){
				if(!(*it).second->trapped()) {
					standarStrategy((*it).second, world, PJs);
				}
			}
		}
	}
}

void ControladorEnemigos::standarStrategy(EnemigoEstandar* unit, b2World* world, ControladorUsuarios PJs){
	b2Vec2 pos = unit->posicion;
	b2Vec2 toAttack = this->closerPJ(world, pos, PJs);
	teclas_t action = this->getAction(unit, toAttack, world);
	switch(action) {
	case ARRIBA:
		unit->eventoSoltoArriba();
		unit->eventoArriba();
		break;
	case IZQUIERDA:
		unit->eventoSoltoArriba();
		unit->eventoSoltoDerecha();
		unit->eventoSoltoAbajo();
		unit->eventoIzquierda();
		break;
	case DERECHA:
		unit->eventoSoltoArriba();
		unit->eventoSoltoIzquierda();
		unit->eventoSoltoAbajo();
		unit->eventoDerecha();
		break;
	case ABAJO:
		unit->eventoSoltoArriba();
		unit->eventoSoltoIzquierda();
		unit->eventoSoltoDerecha();
		unit->eventoAbajo();
		break;
	default:
		break;
	}
}

b2Vec2 ControladorEnemigos::closerPJ(b2World* world, b2Vec2 unit, ControladorUsuarios PJs) {
	b2Vec2 closer = b2Vec2(0, 0);
	float32 closer_mod = INFINITY;
	for(ControladorUsuarios::iterator it=PJs.begin(); it!=PJs.end(); ++it) {
		if(!((*it).second)->isPJAlive()) {
			continue;
		}
		b2Vec2 posPJ = ((*it).second)->getPosition();
		float32 dif_x = unit.x - posPJ.x;
		float32 dif_y = unit.y - posPJ.y;
		float32 mod = pow(dif_x*dif_x + dif_y*dif_y, 0.5);
		if(mod < closer_mod && mod < RADMIN) {
			closer_mod = mod;
			closer = posPJ;
		}
	}
	return closer;
}

bool ControladorEnemigos::isObjectInDirection(b2World* world, EnemigoEstandar* unit, sensor_t obj, float angle, float length) {
	b2Vec2 p1 = unit->posicion;
	b2Vec2 p2 =  p1 + length * b2Vec2( sinf(angle), cosf(angle) );
	RayCaster caster;
	world->RayCast(&caster, p1, p2);
	void* fixData = caster.m_fixture->GetUserData();
	if( *((int*)(&fixData)) == obj) {
		return true;
	}
	return false;
}

teclas_t ControladorEnemigos::getAction(EnemigoEstandar* unit, b2Vec2 enemy, b2World* world) {
	b2Vec2 posUnit = unit->posicion;
	if(enemy.x != 0 && enemy.y != 0) {
		float32 dif_x, mod_x;
		dif_x = mod_x = posUnit.x - enemy.x;
		float32 dif_y, mod_y;
		dif_y = mod_y = posUnit.y - enemy.y;
		if(mod_x < 0) mod_x *= (-1.0f);
		if(mod_y < 0) mod_y *= (-1.0f);
		if(dif_y > 0.5) {
			if(this->isObjectInDirection(world, unit, ATRAVESABLE, 180, unit->altura*2.5) && mod_y + 5 > mod_x) {
				return ARRIBA;
			}
		} else if (dif_y < -0.5) {
			if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura* 1.5) && mod_y + 5 > mod_x) {
				return ABAJO;
			}
		} else {
			if(dif_x < 0) {
//				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 90, unit->baseMayor* 2) || this->isObjectInDirection(world, unit, ESTATICO, 90, unit->baseMayor* 2)) {
//					return IZQUIERDA;
//				}
				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura* 1.5) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 25, unit->baseMayor*4.0)) {
					if(unit->GetAirborne()) {
						return DERECHA;
					} else {
						return ARRIBA;
					}
				}
				return DERECHA;
			}
			else {
//				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 270, unit->baseMayor* 2) || this->isObjectInDirection(world, unit, ESTATICO, 270, unit->baseMayor* 2)) {
//					return DERECHA;
//				}
				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura* 1.5) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 295, unit->baseMayor*4.0)) {
					if(unit->GetAirborne()) {
						return IZQUIERDA;
					} else {
						return ARRIBA;
					}
				}
				return IZQUIERDA;
			}
		}
	}
	// Romear
	if(unit->isMovingRight()) {
		if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura * 1.5) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 25, unit->baseMayor*4.0)) {
			if(unit->GetAirborne()) {
				return DERECHA;
			} else {
				return ARRIBA;
			}
		}
		if(this->isObjectInDirection(world, unit, ESTATICO, 90, unit->baseMayor * 1.3)) {
			return IZQUIERDA;
		}
		return DERECHA;
	}
	if(unit->isMovingLeft()) {
		if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura * 1.5) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 295, unit->baseMayor*4.0)) {
			if(unit->GetAirborne()) {
				return IZQUIERDA;
			} else {
				return ARRIBA;
			}
		}
		if(this->isObjectInDirection(world, unit, ESTATICO, 270, unit->baseMayor * 1.3)) {
			return DERECHA;
		}
		return IZQUIERDA;
	}

	int numero = rand();
	if(numero%5 == 0) {
		return IZQUIERDA;
	}else {
		return DERECHA;
	}
}

void ControladorEnemigos::update(bool online) {
	if(online) {
		for(ControladorEnemigos::iterator it = (*this).begin(); it != (*this).end(); ++it) {
			if((*it).second) {

				if((*it).second->forDelete()){
					delete (*it).second;
					(*it).second=NULL;
				}
				else
				(*it).second->update();
			}
		}
	}
}
