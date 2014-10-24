/*
 * Inicializador.h
 *
 *  Created on: Sep 21, 2014
 *      Author: rodrizapico
 */

#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

#include <Box2D/Box2D.h>

#include "utiles/tipos.h"
#include "utiles/Logger.h"
#include "parser/parser.h"

#include "modelo/formas/Circulo.h"
#include "modelo/formas/PoligonoRegular.h"
#include "modelo/formas/Cuadrilatero.h"

#include "control/ContactListener.h"

#include "modelo/Personaje.h"
#include "modelo/Camera.h"

class Inicializador {

public:

	bool init(std::string configFile, b2World ** worldB2D, ContactListener * contactListener);
	Personaje * pjInit(b2World ** worldB2D, ThreadSafeList<WorldItem*> & rList, std::string configFile, int num);

};



#endif /* INICIALIZADOR_H_ */
