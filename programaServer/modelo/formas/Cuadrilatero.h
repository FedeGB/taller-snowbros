/*
 * Cuadrilatero.h
 *
 *  Created on: Oct 17, 2014
 *      Author: rodrizapico
 */

#ifndef CUADRILATERO_H_
#define CUADRILATERO_H_

#include "../WorldItem.h"
#include "../../utiles/tipos.h"
#include <iostream>


class Cuadrilatero: public WorldItem {

public:

	float32 baseMayor;
	float32 baseMenor;
	float32 altura;
	float32 desplazamiento;
	Cuadrilatero() {
		tipo = CUADRILATERO;
		baseMayor = 1;
		baseMenor = 1;
		altura = 1;
		desplazamiento = 0;
	}

	virtual ~Cuadrilatero() {}
	virtual std::string serializar(){
		std::string buffer;
		buffer = SSTR(CUADRILATERO << " " << posicion.x << " " << posicion.y << " "
				<< angulo << "  " << baseMayor << " " << baseMenor << " "
				<< altura << " " << desplazamiento<<" "<<hielo);
		return buffer;
	}

};



#endif /* CUADRILATERO_H_ */
