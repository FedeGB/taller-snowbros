/*
 * ConnectionHandler.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

#include "TCPStream.h"
#include "ColaTrabajo.h"
#include "WorkItem.h"
#include "../modelo/WorldItem.h"
#include "../Threads/Thread.h"
#include "../Threads/ThreadSafeList.h"
#include "../Threads/ConditionVariable.h"

class ConnectionHandler : public Thread{
	ColaTrabajo<WorkItem*>& m_queue;
	ThreadSafeList<WorldItem*> & renderList;
    TCPStream* m_stream;
	int clientNumber;
	ConditionVariable & cond;

  public:
    ConnectionHandler(ColaTrabajo<WorkItem*>& queue,
    		ThreadSafeList<WorldItem*> & rList,
    		TCPStream* item,
    		ConditionVariable & c,
    		int num);
    void* run();
};

#endif /* CONNECTIONHANDLER_H_ */
