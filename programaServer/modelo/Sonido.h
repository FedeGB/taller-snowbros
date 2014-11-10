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

	Sonido() {
		sonido = VACIO;
	}
	virtual ~Sonido() {}

	std::string serializar(){
		std::string buffer;
		buffer = SSTR(SONIDO << " " << sonido);
		return buffer;
	}

};



#endif /* SONIDO_H_ */
