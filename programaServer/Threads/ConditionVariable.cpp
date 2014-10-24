/*
 * ConditionVariable.cpp
 *
 *  Created on: Oct 24, 2014
 *      Author: rodrizapico
 */

#include "ConditionVariable.h"

ConditionVariable::ConditionVariable() {
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
}

ConditionVariable::~ConditionVariable() {
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}

void ConditionVariable::wait(){
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void ConditionVariable::signal(){
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}
