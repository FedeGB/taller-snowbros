/*
 * Sonido.h
 *
 *  Created on: 6/11/2014
 *      Author: manuel
 */

#ifndef SONIDO_H_
#define SONIDO_H_

#include "../utiles/tipos.h"
class Sonido {

public:
	sonidos_t sonido;
	float velocidad;

	Sonido() {
		sonido = VACIO;
		velocidad = 1.0f;
	}
	virtual ~Sonido() {}

	std::string serializar(){
		std::string buffer;
		buffer = SSTR(SONIDO << " " << sonido << " " << velocidad);
		return buffer;
	}

};



#endif /* SONIDO_H_ */
