/*
 * EnemigoTiraFuego.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: fedevm
 */

#include "EnemigoTiraFuego.h"

EnemigoTiraFuego::EnemigoTiraFuego(){
	orientation = LEFT;
	activeSprite = PARADOIZQUIERDA;
	angulo = 0;
 	online= true;
}

EnemigoTiraFuego::~EnemigoTiraFuego(){}


std::string EnemigoTiraFuego::serializar(){

	std::string buffer;
	buffer = SSTR(ENTIFUE << " " << posicion.x << " " << posicion.y << " "
			<< angulo << "  " << baseMayor << " " << altura << " "
			<< activeSprite << " " << orientation<<""<<spriteStun);
	return buffer;
}
