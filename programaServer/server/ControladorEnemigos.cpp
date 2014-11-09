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

void ControladorEnemigos::strategy(bool online) {
	if(online) {
		for(ControladorEnemigos::iterator it = (*this).begin(); it != (*this).end(); ++it) {
			if((*it).second && (*it).second->tipo == ENEMIGOESTANDAR){
					standarStrategy((*it).second);
			}
		}
	}
}

void ControladorEnemigos::standarStrategy(EnemigoEstandar* unit){
	unit->eventoDerecha();
	unit->eventoArriba();
}

void ControladorEnemigos::update(bool online) {
	if(online) {
		for(ControladorEnemigos::iterator it = (*this).begin(); it != (*this).end(); ++it) {
			if((*it).second)
				(*it).second->update();
		}
	}
}
