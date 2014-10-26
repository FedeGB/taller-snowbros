/*
 * ThreadSafeList.h
 *
 *  Created on: Oct 16, 2014
 *      Author: rodrizapico
 */

#ifndef THREADSAFELIST_H_
#define THREADSAFELIST_H_

#include <pthread.h>
#include <list>

template <typename T> class ThreadSafeList: public std::list<T> {

	pthread_mutex_t m_mutex;
    pthread_cond_t m_condv;

public:
    ThreadSafeList() {
    	pthread_mutex_init(&m_mutex, NULL);
    	pthread_cond_init(&m_condv, NULL);

    }

    ~ThreadSafeList() {
    	pthread_mutex_destroy(&m_mutex);
    	pthread_cond_destroy(&m_condv);
    }

    void lock() {pthread_mutex_lock(&m_mutex);}

    void unlock() {pthread_mutex_unlock(&m_mutex);}

};


#endif /* THREADSAFELIST_H_ */
