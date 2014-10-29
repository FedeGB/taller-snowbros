/*
 * Metadata.h
 *
 *  Created on: Oct 25, 2014
 *      Author: rodrizapico
 */

#ifndef METADATA_H_
#define METADATA_H_

#include "WorldItem.h"

class Metadata: public WorldItem {
public:
	Metadata();
	virtual ~Metadata();
	virtual std::string serializar();

	float escala;
	int vidas;
	int puntaje;
	float posXCamara;
	float posYCamara;
	float tamanioXMundo;
	float tamanioYMundo;
	float anchoCamara;
	float altoCamara;
	std::string mensaje;
};

#endif /* METADATA_H_ */
