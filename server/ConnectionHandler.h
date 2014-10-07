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
#include "../Threads/Thread.h"


class ConnectionHandler : public Thread{
	ColaTrabajo<WorkItem*>& m_queue;
    TCPStream* m_stream;

  public:
    ConnectionHandler(ColaTrabajo<WorkItem*>& queue, TCPStream* item);
    void* run();
};

#endif /* CONNECTIONHANDLER_H_ */
