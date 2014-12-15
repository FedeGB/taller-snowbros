/*
 * EnemigoEstandar.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef ENEMIGOESTANDAR_H_
#define ENEMIGOESTANDAR_H_

#include "Enemigo.h"
#include "../../../control/RayCaster.h"

class EnemigoEstandar: public Enemigo {
public:
	EnemigoEstandar();
	// Levanta el personaje desde el archivo de configuracion Json.
	EnemigoEstandar(std::string sConfig, int numeroObjeto);
	virtual ~EnemigoEstandar();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

};

#endif /* ENEMIGOESTANDAR_H_ */
