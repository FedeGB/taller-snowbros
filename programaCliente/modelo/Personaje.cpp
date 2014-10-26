/*
 * Personaje.cpp
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#include "Personaje.h"

Personaje::Personaje(){
	orientation = LEFT;
	activeSprite = PARADOIZQUIERDA;
	angulo = 0;
 	online=0;
}

Personaje::~Personaje() {}



std::string Personaje::serializar(){

	std::string buffer;
	buffer = SSTR(PJ << " " << posicion.x << " " << posicion.y << " "
			<< angulo << "  " << baseMayor << " " << altura << " "
			<< activeSprite << " " << orientation<< " "<<online);
	return buffer;
}

