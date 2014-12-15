/*
 * WorldHandler.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef WORLDHANDLER_H_
#define WORLDHANDLER_H_

#include "../threads/Thread.h"
#include "../threads/ConditionVariable.h"
#include "../Inicializador.h"
#include "../utiles/tipos.h"
#include "../control/ContactListener.h"
#include "../controladorJuego/ControladorJuego.h"

class WorldHandler: public Thread {

	ControladorJuego * controlador;
	b2World * worldB2D;
	Inicializador inicializador;
	ContactListener contactListener;


	void esperar();
	resultado_t loopPrincipal();
	resultado_t simularPartida();
/*
	//void cleanPowers();
	void limpiarNivel();
*/

public:
	WorldHandler(ControladorJuego * controlador);
	void* run();
};

#endif /* WORLDHANDLER_H_ */
