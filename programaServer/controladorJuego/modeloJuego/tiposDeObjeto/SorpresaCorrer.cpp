/*
 * SorpresaCorrer.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#include "SorpresaCorrer.h"

SorpresaCorrer::SorpresaCorrer() {
	// TODO Auto-generated constructor stub
	cayoPorAgujero = false;
	acumuladorCaida = 0;
	reconocerDestruccion = 0;
}

SorpresaCorrer::~SorpresaCorrer() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string SorpresaCorrer::serializar(){

	std::string buff;

	buff = SSTR(TIPOSORPRESACORRER << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}

void SorpresaCorrer::aplicarAlPJ(Personaje* pj){

	pj->sorpresaCorrerActiva = true;
}
