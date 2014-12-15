/*
 * Ladrillo.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef LADRILLO_H_
#define LADRILLO_H_

#include "ObjetoInanimado.h"

class Ladrillo: public ObjetoInanimado {
public:
	Ladrillo();
	// Levanta el personaje desde el archivo de configuracion Json.
	Ladrillo(std::string sConfig, int numeroObjeto);
	virtual ~Ladrillo();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();
};

#endif /* LADRILLO_H_ */
