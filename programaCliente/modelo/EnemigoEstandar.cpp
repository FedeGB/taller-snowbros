/*
 * EnemigoEstandar.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: fedevm
 */

#include "EnemigoEstandar.h"

EnemigoEstandar::EnemigoEstandar(){
	orientation = LEFT;
	activeSprite = PARADOIZQUIERDA;
	angulo = 0;
 	online= true;
}

EnemigoEstandar::~EnemigoEstandar(){}


std::string EnemigoEstandar::serializar(){

	std::string buffer;
	buffer = SSTR(PJ << " " << posicion.x << " " << posicion.y << " "
			<< angulo << "  " << baseMayor << " " << altura << " "
			<< activeSprite << " " << orientation<<""<<spriteStun);
	return buffer;
}

