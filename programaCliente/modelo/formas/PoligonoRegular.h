/*
 * PoligonoRegular.h
 *
 *  Created on: Oct 17, 2014
 *      Author: rodrizapico
 */

#ifndef POLIGONOREGULAR_H_
#define POLIGONOREGULAR_H_

#include "../WorldItem.h"
#include "../../utiles/tipos.h"

class PoligonoRegular: public WorldItem {

public:

	int nLados;
	float32 radio;

	PoligonoRegular() {
		nLados = 4;
		radio = 1;
	}

	virtual ~PoligonoRegular() {}

	virtual std::string serializar(){
		std::string buffer;
		buffer = SSTR(POLIGONOREGULAR << " " << posicion.x << " " << posicion.y << " "
				<< angulo << " " << radio << " " << nLados);
		return buffer;
	}

};



#endif /* POLIGONOREGULAR_H_ */
