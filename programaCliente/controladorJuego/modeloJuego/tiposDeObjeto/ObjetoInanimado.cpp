/*
 * ObjetoInanimado.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "ObjetoInanimado.h"


ObjetoInanimado::~ObjetoInanimado() {
	// TODO Auto-generated destructor stub
}


// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string ObjetoInanimado::serializar(){

	std::string buff;

	buff = SSTR(TIPOPERSONAJE << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	return buff;
}

// Aplica la modificacion indicada sobre el SerVivo.
void ObjetoInanimado::aplicar(ObjetoInanimado * modificacion){

	ObjetoModelo::aplicar((ObjetoModelo*)modificacion);
}


// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
void ObjetoInanimado::aplicarSobre(ObjetoModelo * objeto){
	objeto->aplicar(this);
}
