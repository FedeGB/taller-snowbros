/*
 * Circle.h
 *
 *  Created on: Oct 16, 2014
 *      Author: rodrizapico
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../WorldItem.h"
#include "../../utiles/tipos.h"
#include <vector>

class Circulo: public WorldItem {

public:

	float32 radio;

	Circulo() {
		radio = 1.0;
	}

	virtual ~Circulo() {}

	virtual std::string serializar(){
		std::string buffer;
		buffer = SSTR(CIRCULO << " " << posicion.x << " " << posicion.y << " "
				<< angulo << " " << radio);
		return buffer;
	}

};


#endif /* CIRCLE_H_ */
