/*
 * EnemigoEstandar.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "EnemigoEstandar.h"
#include "Personaje.h"

EnemigoEstandar::EnemigoEstandar() {
	// TODO Auto-generated constructor stub

}

// Levanta el personaje desde el archivo de configuracion Json.
EnemigoEstandar::EnemigoEstandar(std::string sConfig, int numeroObjeto): Enemigo(sConfig, numeroObjeto){

}

EnemigoEstandar::~EnemigoEstandar() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string EnemigoEstandar::serializar(){

	std::string buff;

	buff = SSTR(TIPOENEMIGOESTANDAR << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << estado << SEPARADORDATOS << salud << SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}
