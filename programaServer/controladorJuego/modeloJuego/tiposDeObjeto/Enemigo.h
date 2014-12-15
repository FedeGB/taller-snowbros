/*
 * Enemigo.h
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include "SerVivo.h"
#include "../../../control/RayCaster.h"

class Enemigo: public SerVivo {
public:
	Enemigo();
	// Levanta el personaje desde el archivo de configuracion Json.
	Enemigo(std::string sConfig, int numeroObjeto);
	virtual ~Enemigo();

	// Indica que el enemigo fue pateado.
	void patear();

	// Actualiza la informacion del objeto para poder dibujarlo.
	virtual void actualizar(Personaje * pj);

protected:

	bool isObjectInDirection(b2World* world, Enemigo * unit, sensor_t obj, float angle, float length);

	// El enemigo se mueve semialeatoriamente, hasta encontrar a un personaje para seguir.
	void deambular();

	bool fuePateado;
};

#endif /* ENEMIGO_H_ */
