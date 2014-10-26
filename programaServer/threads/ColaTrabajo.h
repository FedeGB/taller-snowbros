/*
 * ColaTrabajo.h
 *
 *  Created on: Oct 3, 2014
 *      Author: matias
 */

#ifndef COLATRABAJO_H_
#define COLATRABAJO_H_

#include <pthread.h>
#include <list>

using namespace std;

template <typename T> class ColaTrabajo {

    list<T>          m_cola;
    pthread_mutex_t  m_mutex;
    pthread_cond_t   m_condv;

public:
    ColaTrabajo() {
    	pthread_mutex_init(&m_mutex, NULL);
    	pthread_cond_init(&m_condv, NULL);

    }

    ~ColaTrabajo() {
    	pthread_mutex_destroy(&m_mutex);
    	pthread_cond_destroy(&m_condv);
    }

    void add(T item) {
        pthread_mutex_lock(&m_mutex);
        m_cola.push_back(item);
        pthread_cond_signal(&m_condv);
        pthread_mutex_unlock(&m_mutex);
    }

    T remove() {
        pthread_mutex_lock(&m_mutex);
        while (m_cola.size() == 0) {
            pthread_cond_wait(&m_condv, &m_mutex);
        }
        T item = m_cola.front();
        m_cola.pop_front();
        pthread_mutex_unlock(&m_mutex);
        return item;
    }

    T nonLockingRemove() {
        pthread_mutex_lock(&m_mutex);

        T item = NULL;
        if(m_cola.size() != 0){
        	item = m_cola.front();
			m_cola.pop_front();
        }
        pthread_mutex_unlock(&m_mutex);
        return item;
    }

    int size() {
        pthread_mutex_lock(&m_mutex);
        int size = m_cola.size();
        pthread_mutex_unlock(&m_mutex);
        return size;
    }

};



#endif /* COLATRABAJO_H_ */
