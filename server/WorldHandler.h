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
#include "../Threads/Thread.h"

class WorldHandler: public Thread {
	ColaTrabajo<WorkItem*>& m_queue;

public:
	WorldHandler(ColaTrabajo<WorkItem*>& queue);
	void* run();
};

#endif /* WORLDHANDLER_H_ */
