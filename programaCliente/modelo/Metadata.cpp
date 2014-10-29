/*
 * Metadata.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: rodrizapico
 */

#include "Metadata.h"


Metadata::Metadata() {
	escala = 0.05;
	vidas = 3;
	puntaje = 0;
	posXCamara = 0;
	posYCamara = 0;
	anchoCamara = 0.5f;
	altoCamara = 0.3f;
	tamanioXMundo = tamanioYMundo = 1;
	tipo = METADATAHUD;

}

Metadata::~Metadata() {
}

std::string Metadata::serializar(){
	std::string buffer;
	buffer = SSTR(tipo << " " << posXCamara << " " << posYCamara << " "
			<< altoCamara << " " << anchoCamara << " " << escala << " "
			<< vidas << " " << puntaje << " " << tamanioXMundo << " " << tamanioYMundo);
	return buffer;
}
