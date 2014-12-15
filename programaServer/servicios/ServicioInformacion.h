/*
 * ServicioInformacion.h
 *
 *  Created on: Dec 7, 2014
 *      Author: rodrizapico
 */

#ifndef SERVICIOINFORMACION_H_
#define SERVICIOINFORMACION_H_

#include <string>
#include "../matematica/Vector2D.h"

class ServicioInformacion {
public:
	ServicioInformacion();
	virtual ~ServicioInformacion();

	std::string IP;
	int puerto;
	std::string archivoConfiguracion;
	Vector2D tamanioMapa;
	int numJugadores;

};

#endif /* SERVICIOINFORMACION_H_ */
