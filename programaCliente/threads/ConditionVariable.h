/*
 * ConditionVariable.h
 *
 *  Created on: Oct 24, 2014
 *      Author: rodrizapico
 */

#ifndef CONDITIONVARIABLE_H_
#define CONDITIONVARIABLE_H_

#include <pthread.h>

class ConditionVariable {
public:
	ConditionVariable();
	virtual ~ConditionVariable();
	void wait();
	void signal();
private:
    pthread_mutex_t  mutex;
    pthread_cond_t   cond;
};

#endif /* CONDITIONVARIABLE_H_ */
