/*
 * BolaDeNieve.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "BolaDeNieve.h"

BolaDeNieve::BolaDeNieve() {
	// TODO Auto-generated constructor stub
	reconocerDestruccion = 0;
	danio = 1;
	cayoPorAgujero = false;
}

BolaDeNieve::~BolaDeNieve() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string BolaDeNieve::serializar(){

	std::string buff;

	buff = SSTR(TIPOBOLADENIEVE << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}
