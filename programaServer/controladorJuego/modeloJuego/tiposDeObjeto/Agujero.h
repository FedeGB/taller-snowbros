/*
 * Agujero.h
 *
 *  Created on: Dec 13, 2014
 *      Author: rodrizapico
 */

#ifndef AGUJERO_H_
#define AGUJERO_H_

#include "ObjetoInanimado.h"

class Agujero: public ObjetoInanimado {
public:
	Agujero();
	// Levanta el personaje desde el archivo de configuracion Json.
	Agujero(std::string sConfig, int numeroObjeto);
	virtual ~Agujero();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();
};

#endif /* AGUJERO_H_ */
