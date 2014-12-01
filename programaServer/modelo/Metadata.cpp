/*
 * Metadata.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: rodrizapico
 */

#include "Metadata.h"


Metadata::Metadata() {
	escala = 0.05;
	puntaje = 1;
	posXCamara = 0;
	posYCamara = 0;
	anchoCamara = 0.5f;
	altoCamara = 0.3f;
	tamanioXMundo = tamanioYMundo = 1;
	tipo = METADATAHUD;
	mensaje = "NOMESSAGE";
	vidas[0]=0;
	vidas[1]=0;
	vidas[2]=0;
	vidas[3]=0;
	users[0]="offline";
	users[1]="offline";
	users[2]="offline";
	users[3]="offline";
}

Metadata::~Metadata() {
}

std::string Metadata::serializar(){
	std::string buffer;
	buffer = SSTR(tipo << " " << posXCamara << " " << posYCamara << " "
			<< altoCamara << " " << anchoCamara << " " << escala << " "
			<< vidas[0] << " " << puntaje << " " << tamanioXMundo << " " << tamanioYMundo << " "
			<< mensaje<<" " <<vidas[1]<<" " <<vidas[2]<<" " <<vidas[3]<<" "
			<<users[0]<<" " <<users[1]<<" " <<users[2]<<" " <<users[3]);
	return buffer;
}
