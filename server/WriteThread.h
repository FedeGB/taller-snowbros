/*
 * WriteThread.h
 *
 *  Created on: Oct 8, 2014
 *      Author: matias
 */

#ifndef WRITETHREAD_H_
#define WRITETHREAD_H_

#include "../Threads/Thread.h"
#include "ColaTrabajo.h"
#include "Message.h"
#include "TCPStream.h"

class WriteThread: public Thread {
	ColaTrabajo<Message*>& m_queue;
	TCPStream* m_stream;
	bool closed;

public:
	WriteThread(ColaTrabajo<Message*> queue, TCPStream* stream);
	void* run();
	bool readyToClose();
};

#endif /* WRITETHREAD_H_ */
