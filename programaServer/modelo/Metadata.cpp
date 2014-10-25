/*
 * Metadata.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: rodrizapico
 */

#include "Metadata.h"

Metadata::Metadata() {
	escala = 0.05;
}

Metadata::~Metadata() {
}

std::string Metadata::serializar(){
	std::string buffer;
	buffer = SSTR(METADATA << " " << escala);
	return buffer;
}
