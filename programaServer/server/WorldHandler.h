/*
 * WorldHandler.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef WORLDHANDLER_H_
#define WORLDHANDLER_H_

#include "ColaTrabajo.h"
#include "WorkItem.h"
#include "../modelo/WorldItem.h"
#include "../Threads/Thread.h"
#include "../Threads/ThreadSafeList.h"
#include "../Threads/ConditionVariable.h"
#include "../control/ContactListener.h"
#include "../Inicializador.h"
#include <Box2D/Box2D.h>


class WorldHandler: public Thread {
	ColaTrabajo<WorkItem*> & m_queue;
	ThreadSafeList<WorldItem*> (&renderList)[4];
	b2World *worldB2D;
	ConditionVariable (& cond)[4];
	Inicializador inicializador;
	ContactListener contactListener;
	vector<Personaje*> vectorPJ;
	int numJugadores;

	bool loopPrincipal();

public:
	WorldHandler(ColaTrabajo<WorkItem*> & queue,
			ThreadSafeList<WorldItem*> (&rList)[4], ConditionVariable (& c)[4]);
	void* run();
};

#endif /* WORLDHANDLER_H_ */
