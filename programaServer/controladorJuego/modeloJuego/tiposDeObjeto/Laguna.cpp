/*
 * Laguna.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: rodrizapico
 */

#include "Laguna.h"

Laguna::Laguna() {
	// TODO Auto-generated constructor stub

}


// Levanta el personaje desde el archivo de configuracion Json.
Laguna::Laguna(std::string sConfig, int numeroObjeto){

	reconocerDestruccion = 0;
	rotacion = get_node("rot", "objetos", sConfig, numeroObjeto, 0.0f) * DEGTORAD;

	espacioOcupado = new FiguraGeometrica();
	Vector2D punto;


	// Obtiene el espacio ocupado por el ladrillo.
	float x = get_node("x", "objetos", sConfig, numeroObjeto, 20.0f);
	float y = get_node("y", "objetos", sConfig, numeroObjeto, 20.0f);
	float ancho = get_node("ancho", "objetos", sConfig, numeroObjeto, 20.0f);
	float alto = get_node("alto", "objetos", sConfig, numeroObjeto, 20.0f);

	// Carga los puntos del ladrillo.
	punto.x = x - ancho / 2; punto.y = y - alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x + ancho / 2; punto.y = y - alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x + ancho / 2; punto.y = y + alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x - ancho / 2; punto.y = y + alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

}

Laguna::~Laguna() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string Laguna::serializar(){

	std::string buff;

	buff = SSTR(TIPOLAGUNA << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}
