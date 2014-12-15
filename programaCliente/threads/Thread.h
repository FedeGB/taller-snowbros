/*
 * Thread.h
 *
 *  Created on: Oct 3, 2014
 *      Author: matias
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread {
public:
	Thread();
	virtual ~Thread();

    int iniciar();
    int join();
    int detach();
    pthread_t self();

    virtual void* correr() = 0;

  private:
    pthread_t  m_tid;
    int        m_running;
    int        m_detached;
};

#endif /* THREAD_H_ */
