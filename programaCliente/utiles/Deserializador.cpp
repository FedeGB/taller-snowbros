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
	if (buff[0] == "USERNAME") return NULL;
	worlditem_t type = (worlditem_t) strtol(buff[0].c_str(),NULL,10);
	//printf("tipo cliente: %i\n", type);
	switch (type){

	// Deserializa metadata.
	case METADATAHUD:{

		Metadata * metadata = new Metadata();
		metadata->tipo = type;
		metadata->vidas = strtol(buff[6].c_str(),NULL,10);
		metadata->puntaje = strtol(buff[7].c_str(),NULL,10);
		metadata->mensaje = buff[10];
		return metadata;
	}

	case METADATAFONDO:{

		Metadata * metadata = new Metadata();
		metadata->tipo = type;
		metadata->posXCamara = (float)atof(buff[1].c_str());
		metadata->posYCamara = (float)atof(buff[2].c_str());
		metadata->altoCamara = (float)atof(buff[3].c_str());
		metadata->anchoCamara = (float)atof(buff[4].c_str());
		metadata->escala = (float)atof(buff[5].c_str());
		metadata->tamanioXMundo = (float)atof(buff[8].c_str());
		metadata->tamanioYMundo = (float)atof(buff[9].c_str());
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
		cuadrilatero->hielo=(bool)atoi(buff[8].c_str());
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

	case SONIDO:{
		//sonido = buff[1];
		Sonido * s = new Sonido();
		s->tipo = type;
		s->sonido = (sonidos_t) strtol(buff[1].c_str(),NULL,10);
		if( s->sonido == VACIO ) return NULL;
		std::cout << "sonido recibido: " << s->sonido << '\n';
		return s;
	}

	case PODERES:{
		poder * poderes = new poder();
		poderes->baseMayor =  (float)atof(buff[4].c_str());
		//poderes->baseMenor =  (float)atof(buff[5].c_str());
		poderes->altura =  (float)atof(buff[5].c_str());
		poderes->activeSprite =  PODER1;
		item = poderes;
		break;

	}

	case ENEMIGOESTANDAR:{
		EnemigoEstandar * en = new EnemigoEstandar();
		en->baseMayor =  (float)atof(buff[4].c_str());
		en->altura =  (float)atof(buff[5].c_str());

		en->activeSprite = (sprite_t) strtol(buff[6].c_str(),NULL,10);
		en->orientation = (Personaje::orientation_t) strtol(buff[7].c_str(),NULL,10);
		en->spriteStun = (sprite_t) strtol(buff[8].c_str(),NULL,10);
		item = en;
		break;
	}

	case SORPRESA:{
		Sorpresa * sorpresa = new Sorpresa();
		sorpresa->baseMayor =  (float)atof(buff[4].c_str());
		sorpresa->altura =  (float)atof(buff[5].c_str());

		sorpresa->activeSprite = (sprite_t) strtol(buff[6].c_str(),NULL,10);
		//en->orientation = (Personaje::orientation_t) strtol(buff[7].c_str(),NULL,10);
		item = sorpresa;
		break;
	}

	default: return NULL;

	}

	item->posicion.x = (float)atof(buff[1].c_str());
	item->posicion.y = (float)atof(buff[2].c_str());
	item->angulo = (float)atof(buff[3].c_str());
	item->tipo = type;

	return item;
}
