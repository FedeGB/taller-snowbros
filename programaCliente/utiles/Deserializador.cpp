/*
 * Deserializador.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: rodrizapico
 */

#include "Deserializador.h"

Deserializador::Deserializador() {
	// TODO Auto-generated constructor stub

}

Deserializador::~Deserializador() {
	// TODO Auto-generated destructor stub
}

WorldItem * Deserializador::deserializar(std::string serializado){

	WorldItem * item;
	std::vector<std::string> buff;
	split(buff, serializado, " ", no_empties);
	int type = strtol(buff[0].c_str(),NULL,10);

	switch (type){

	// Deserializa metadata.
	case METADATA:{
		Metadata * metadata = new Metadata();
		metadata->tipo = type;
		metadata->escala = (float)atof(buff[1].c_str());
		metadata->vidas = strtol(buff[2].c_str(),NULL,10);
		metadata->puntaje = strtol(buff[3].c_str(),NULL,10);
		return metadata;
	}

	// Deserializa el circulo.
	case CIRCULO:{
		Circulo * circulo = new Circulo();
		circulo->radio = (float)atof(buff[4].c_str());

		item = circulo;
		break;
	}

	// Deserializa el cuadrilatero.
	case CUADRILATERO:{
		Cuadrilatero * cuadrilatero = new Cuadrilatero();
		cuadrilatero->baseMayor =  (float)atof(buff[4].c_str());
		cuadrilatero->baseMenor =  (float)atof(buff[5].c_str());
		cuadrilatero->altura =  (float)atof(buff[6].c_str());
		cuadrilatero->desplazamiento =  (float)atof(buff[7].c_str());

		item = cuadrilatero;
		break;
	}

	// Deserializa el poligono.
	case POLIGONOREGULAR:{
		PoligonoRegular * poligono = new PoligonoRegular();
		poligono->radio =  (float)atof(buff[4].c_str());
		poligono->nLados =  strtol(buff[5].c_str(),NULL,10);

		item = poligono;
		break;
	}

	// Deserializa el PJ.
	case PJ:{
		Personaje * pj = new Personaje();
		pj->baseMayor =  (float)atof(buff[4].c_str());
		pj->altura =  (float)atof(buff[5].c_str());

		pj->activeSprite = (sprite_t) strtol(buff[6].c_str(),NULL,10);
		pj->orientation = (Personaje::orientation_t) strtol(buff[7].c_str(),NULL,10);
		pj->online= (bool)strtol(buff[8].c_str(),NULL,10);
		item = pj;
		break;
	}

	}

	item->posicion.x = (float)atof(buff[1].c_str());
	item->posicion.y = (float)atof(buff[2].c_str());
	item->angulo = (float)atof(buff[3].c_str());
	item->tipo = type;

	return item;
}
