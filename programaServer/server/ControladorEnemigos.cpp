/*
 * ControladorEnemigos.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: fedevm
 */

#include "ControladorEnemigos.h"
#include <cstdlib>

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
	b2Vec2 pos = b2Vec2(unit->posicion.x, unit->posicion.y);
	b2Vec2 toAttack = this->closerPJ(world, pos, PJs);
	teclas_t action = this->getAction(pos, toAttack, world);
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
		// Should not enter here.
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

teclas_t ControladorEnemigos::getAction(b2Vec2 unit, b2Vec2 enemy, b2World* world) {
	if(enemy.x != 0 && enemy.y != 0) {
		float32 dif_x, mod_x;
		dif_x = mod_x = unit.x - enemy.x;
		float32 dif_y, mod_y;
		dif_y = mod_y = unit.y - enemy.y;
		if(mod_x < 0) mod_x *= (-1.0f);
		if(mod_y < 0) mod_y *= (-1.0f);
		if(mod_y > mod_x) {
			if(dif_y > 0) {
				return ARRIBA;
			} else {
				return ABAJO;
			}
		} else {
			if(dif_x < 0) return DERECHA;
			else return IZQUIERDA;
		}
	}
	// Romear
	return SPACE;

}

void ControladorEnemigos::update(bool online) {
	if(online) {
		for(ControladorEnemigos::iterator it = (*this).begin(); it != (*this).end(); ++it) {
			if((*it).second) {
				(*it).second->update();
			}
		}
	}
}
