/*
 * EnemigoFuego.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef ENEMIGOFUEGO_H_
#define ENEMIGOFUEGO_H_

#include "Enemigo.h"

class EnemigoFuego: public Enemigo {
public:
	EnemigoFuego();
	// Levanta el personaje desde el archivo de configuracion Json.
	EnemigoFuego(std::string sConfig, int numeroObjeto);
	virtual ~EnemigoFuego();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	// Actualiza la informacion del objeto para poder dibujarlo.
	virtual void actualizar(Personaje * pj);

private:

	bool isObjectInDirectionRange(b2World* world, Enemigo * unit, sensor_t obj, float angle, float length, int range) ;
};

#endif /* ENEMIGOFUEGO_H_ */
