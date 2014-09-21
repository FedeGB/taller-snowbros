/*
 * Inicializador.h
 *
 *  Created on: Sep 21, 2014
 *      Author: rodrizapico
 */

#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

#include <Box2D/Box2D.h>

#include "utiles/Logger.h"
#include "parser/parser.h"

#include "modelo/formas/CirculoDibujable.h"
#include "modelo/formas/PoligonoRegularDibujable.h"
#include "modelo/formas/PoligonoIrregularDibujable.h"
#include "modelo/formas/RectanguloDibujable.h"

#include "control/HandlerDeEventos.h"
#include "control/ContactListener.h"

#include "modelo/Personaje.h"
#include "Window.h"

class Inicializador {

public:

	bool init(Window ** w, b2World ** worldB2D, ContactListener * contactListener, HandlerDeEventos * wHandlerEventos);

};



#endif /* INICIALIZADOR_H_ */
