/*
 * ObjetoDibujable.h
 *
 *  Created on: Sep 15, 2014
 *      Author: rodrizapico
 */

#ifndef OBJETODIBUJABLE_H_
#define OBJETODIBUJABLE_H_

#include "interfaces/IDibujable.h"
#include "Objeto.h"

class ObjetoDibujable: public IDibujable, public Objeto {
public:
	ObjetoDibujable(){};
	virtual ~ObjetoDibujable(){};
};

#endif /* OBJETODIBUJABLE_H_ */
