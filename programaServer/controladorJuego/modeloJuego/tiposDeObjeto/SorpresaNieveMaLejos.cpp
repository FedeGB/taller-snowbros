/*
 * SorpresaNieveMaLejos.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#include "SorpresaNieveMaLejos.h"

SorpresaNieveMaLejos::SorpresaNieveMaLejos() {
	// TODO Auto-generated constructor stub

}

SorpresaNieveMaLejos::~SorpresaNieveMaLejos() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string SorpresaNieveMaLejos::serializar(){

	std::string buff;

	buff = SSTR(TIPOSORPRESANIEVEMASLEJOS << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}

void SorpresaNieveMaLejos::aplicarAlPJ(Personaje* pj){

	std::cout << "aplique la sorpresa nieveLejos" << std::endl;

	pj->sorpresaNieveLejosActiva = true;
}
