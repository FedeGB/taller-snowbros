/*
 * RecvThread.h
 *
 *  Created on: Oct 7, 2014
 *      Author: matias
 */

#ifndef RECVTHREAD_H_
#define RECVTHREAD_H_

#include "Message.h"
#include "ColaTrabajo.h"
#include "TCPStream.h"
#include "../Threads/Thread.h"

class RecvThread : public Thread {
	ColaTrabajo<Message*>& m_queue;
	TCPStream* m_stream;
	bool closed;

public:
	RecvThread(ColaTrabajo<Message*>& queue, TCPStream* stream);
	void* run();
	bool readyToClose();
};

#endif /* RECVTHREAD_H_ */
