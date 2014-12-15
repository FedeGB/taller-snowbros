/*
 * Laguna.h
 *
 *  Created on: Dec 13, 2014
 *      Author: rodrizapico
 */

#ifndef LAGUNA_H_
#define LAGUNA_H_

#include "ObjetoInanimado.h"

class Laguna: public ObjetoInanimado {
public:
	Laguna();
	// Levanta el personaje desde el archivo de configuracion Json.
	Laguna(std::string sConfig, int numeroObjeto);
	virtual ~Laguna();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

};

#endif /* LAGUNA_H_ */
