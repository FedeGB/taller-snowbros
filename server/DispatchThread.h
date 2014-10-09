/*
 * DispatchThread.h
 *
 *  Created on: Oct 8, 2014
 *      Author: matias
 */

#ifndef DISPATCHTHREAD_H_
#define DISPATCHTHREAD_H_

#include "../Threads/Thread.h"
#include "Message.h"
#include "ColaTrabajo.h"
#include "ConnectionHandler.h"
#include <list>

class DispatchThread: public Thread {
	list<ConnectionHandler*> m_connections;
	ColaTrabajo<Message*>& m_queue;

public:
	DispatchThread(ColaTrabajo<Message*>& queue, list<ConnectionHandler*> connections);
	void* run();
};

#endif /* DISPATCHTHREAD_H_ */
