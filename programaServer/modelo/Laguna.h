/*
 * Laguna.h
 *
 *  Created on: 26/11/2014
 *      Author: manuel
 */

#ifndef LAGUNA_H_
#define LAGUNA_H_

#include "../utiles/tipos.h"
#include "formas/Cuadrilatero.h"

class Laguna : public Cuadrilatero{
public:
	Laguna(){}
	virtual ~Laguna(){}

	std::string serializar(){
		std::string buffer;
		buffer = SSTR(LAGUNA << " " << posicion.x << " " << posicion.y << " "
				<< angulo << "  " << baseMayor << " " << altura);
		return buffer;
	}

private:

};



#endif /* LAGUNA_H_ */
