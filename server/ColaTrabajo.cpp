/*
 * ColaTrabajo.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: matias
 */

#include "ColaTrabajo.h"

template <typename T> ColaTrabajo<T>::ColaTrabajo() {
	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_condv, NULL);

}

template <typename T> ColaTrabajo<T>::~ColaTrabajo() {
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_condv);
}

template <typename T> void ColaTrabajo<T>::add(T item) {
    pthread_mutex_lock(&m_mutex);
    m_cola.push_back(item);
    pthread_cond_signal(&m_condv);
    pthread_mutex_unlock(&m_mutex);
}

template <typename T> T ColaTrabajo<T>::remove() {
    pthread_mutex_lock(&m_mutex);
    while (m_cola.size() == 0) {
        pthread_cond_wait(&m_condv, &m_mutex);
    }
    T item = m_cola.front();
    m_cola.pop_front();
    pthread_mutex_unlock(&m_mutex);
    return item;
}

template <typename T> int ColaTrabajo<T>::size() {
    pthread_mutex_lock(&m_mutex);
    int size = m_cola.size();
    pthread_mutex_unlock(&m_mutex);
    return size;
}

