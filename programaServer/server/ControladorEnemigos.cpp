/*
 * ControladorEnemigos.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: fedevm
 */

#include "ControladorEnemigos.h"
//#include <cstdlib>
#include "../control/RayCaster.h"
//#include <random>

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
			if((*it).second && (*it).second->tipo == ENEMIGOTIRAFUEGO){
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
	case SPACE:
		if(unit->tipo == ENEMIGOTIRAFUEGO) {
			if(((EnemigoTiraFuego*)unit)->getTimerThrow() == 0) {
				if(!unit->isSpacePressed) {
					unit->eventoSpace();
				}
				((EnemigoTiraFuego*)unit)->restarTimerThrow();
			} else {
				((EnemigoTiraFuego*)unit)->restarTimerThrow();
				if(unit->isSpacePressed)
					unit->eventoSoltoSpace();
			}
		}
		break;
	default:
		break;
	}
}

//void ControladorEnemigos::fireStrategy(EnemigoEstandar* unit, b2World* world, ControladorUsuarios PJs){
//	b2Vec2 pos = unit->posicion;
//	b2Vec2 toAttack = this->closerPJ(world, pos, PJs);
//	teclas_t action = this->getAction(unit, toAttack, world);
//	switch(action) {
//	case ARRIBA:
//		unit->eventoSoltoArriba();
//		unit->eventoArriba();
//		unit->eventoSoltoSpace();
//		break;
//	case IZQUIERDA:
//		unit->eventoSoltoArriba();
//		unit->eventoSoltoDerecha();
//		unit->eventoSoltoAbajo();
//		unit->eventoIzquierda();
//		break;
//	case DERECHA:
//		unit->eventoSoltoArriba();
//		unit->eventoSoltoIzquierda();
//		unit->eventoSoltoAbajo();
//		unit->eventoDerecha();
//		break;
//	case ABAJO:
//		unit->eventoSoltoArriba();
//		unit->eventoSoltoIzquierda();
//		unit->eventoSoltoDerecha();
//		unit->eventoAbajo();
//		break;
//	case SPACE:
//		if(!unit->GetAirborne()) {
//			unit->eventoSpace();
//		} else {
//			unit->eventoSoltoSpace();
//		}
//		break;
//	default:
//		break;
//	}
//}

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
	b2Vec2 p2 =  p1 + b2Vec2(length * sinf(angle*DEGTORAD), length * cosf(angle*DEGTORAD) );
	RayCaster caster;
	world->RayCast(&caster, p1, p2);
	if(caster.m_fixture) {
		void* fixData = caster.m_fixture->GetUserData();
		if(fixData && *((int*)(&fixData)) == obj && caster.m_fraction <= 1) {
			std::cout << "OBJETO " << obj << " ENCONTRADO" << std::endl;
			std::cout << "fraction: " << caster.m_fraction << std::endl;
			std::cout << "point: " << caster.m_point.x << caster.m_point.y << std::endl;
			return true;
		}
	}
	return false;
}

bool ControladorEnemigos::isObjectInDirectionRange(b2World* world, EnemigoEstandar* unit, sensor_t obj, float angle, float length, int range) {
	int div;
	for(int i = -range/2; i < range/2; i++) {
		if(i < 0) div = -i*2.0;
		else if (i > 0) div = i*2.0;
		else div = 1;
		if(isObjectInDirection(world, unit, obj, angle + i, length/div)) {
			return true;
		}
	}
	return false;
}

teclas_t ControladorEnemigos::getAction(EnemigoEstandar* unit, b2Vec2 enemy, b2World* world) {
	b2Vec2 posUnit = unit->posicion;
	if(enemy.x != 0 && enemy.y != 0) {
		if(unit->tipo == ENEMIGOTIRAFUEGO) {
			if((isObjectInDirectionRange(world, unit, PERSONAJE, 90, unit->baseMayor*4.0, 5) && unit->orientation == RIGHT) || (isObjectInDirectionRange(world, unit, PERSONAJE, 270, unit->baseMayor*4.0, 5) && unit->orientation == LEFT)) {
				return SPACE;
			}
		}
		float32 dif_x, mod_x;
		dif_x = mod_x = posUnit.x - enemy.x;
		float32 dif_y, mod_y;
		dif_y = mod_y = posUnit.y - enemy.y;
		if(mod_x < 0) mod_x *= (-1.0f);
		if(mod_y < 0) mod_y *= (-1.0f);
		if(dif_y > 0.5) {
			if(this->isObjectInDirection(world, unit, ATRAVESABLE, 180, unit->altura*3) && mod_y + 5 > mod_x) {
				return ARRIBA;
			}
		} else if (dif_y < -0.5) {
			if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura* 1.5) && mod_y + 5 > mod_x) {
				return ABAJO;
			}
		} else {
			if(dif_x < 0) {
				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 90, unit->baseMayor* 2) || this->isObjectInDirection(world, unit, ESTATICO, 90, unit->baseMayor* 2)) {
					return IZQUIERDA;
				}
				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura* 1.2) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 85, unit->baseMayor*4.0)) {
					if(unit->GetAirborne()) {
						return DERECHA;
					} else {
						return ARRIBA;
					}
				}
				return DERECHA;
			}
			else {
				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 270, unit->baseMayor* 2) || this->isObjectInDirection(world, unit, ESTATICO, 270, unit->baseMayor* 2)) {
					return DERECHA;
				}
				if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura* 1.2) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 275, unit->baseMayor*4.0)) {
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
		if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura * 1.2) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 85, unit->baseMayor*4.0)) {
			if(unit->GetAirborne()) {
				return DERECHA;
			} else {
				return ARRIBA;
			}
		}
		if(this->isObjectInDirection(world, unit, ESTATICO, 90, unit->baseMayor * 2)) {
			return IZQUIERDA;
		}
		return DERECHA;
	}
	if(unit->isMovingLeft()) {
		if(this->isObjectInDirection(world, unit, ATRAVESABLE, 0, unit->altura * 1.2) && !this->isObjectInDirection(world, unit, ATRAVESABLE, 275, unit->baseMayor*4.0)) {
			if(unit->GetAirborne()) {
				return IZQUIERDA;
			} else {
				return ARRIBA;
			}
		}
		if(this->isObjectInDirection(world, unit, ESTATICO, 270, unit->baseMayor * 2)) {
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
