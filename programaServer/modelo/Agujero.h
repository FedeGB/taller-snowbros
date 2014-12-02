/*
 * Agujero.h
 *
 *  Created on: 30/11/2014
 *      Author: manuel
 */

#ifndef AGUJERO_H_
#define AGUJERO_H_

#include "../utiles/tipos.h"
#include "formas/Cuadrilatero.h"

class Agujero : public Cuadrilatero {
public:
	Agujero(){}
	virtual ~Agujero(){}

	std::string serializar(){
		std::string buffer;
		buffer = SSTR(AGUJERO << " " << posicion.x << " " << posicion.y << " "
				<< angulo << "  " << baseMayor << " " << altura);
		return buffer;
	}
};


#endif /* AGUJERO_H_ */
