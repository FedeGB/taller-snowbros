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
	ColaTrabajo();
	virtual ~ColaTrabajo();
	void add(T item);
	T remove();
	int size();

};

#endif /* COLATRABAJO_H_ */
