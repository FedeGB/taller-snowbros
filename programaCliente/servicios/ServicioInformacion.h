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

	std::string nombreUsuario;
	std::string IP;
	int puerto;
	Vector2D tamanioMapa;
	Vector2D resolucionPantalla;
	bool sonidoEncendido;
	bool pantallaCompleta;
};

#endif /* SERVICIOINFORMACION_H_ */
