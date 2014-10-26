/*
 * WorldHandler.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef WORLDHANDLER_H_
#define WORLDHANDLER_H_

#include "../threads/ColaTrabajo.h"
#include "WorkItem.h"
#include "../modelo/WorldItem.h"
#include "../threads/Thread.h"
#include "../threads/ThreadSafeList.h"
#include "../threads/ConditionVariable.h"
#include "../control/ContactListener.h"
#include "../Inicializador.h"
#include "../ControladorUsuarios.h"
#include <Box2D/Box2D.h>


class WorldHandler: public Thread {

	ControladorUsuarios & controlador;
	b2World *worldB2D;
	Inicializador inicializador;
	ContactListener contactListener;

	bool loopPrincipal();

public:
	WorldHandler(ControladorUsuarios & c);
	void* run();
};

#endif /* WORLDHANDLER_H_ */
