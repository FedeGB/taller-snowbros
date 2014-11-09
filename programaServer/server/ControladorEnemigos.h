/*
 * ControladorEnemigos.h
 *
 *  Created on: Nov 8, 2014
 *      Author: fedevm
 */

#ifndef CONTROLADORENEMIGOS_H_
#define CONTROLADORENEMIGOS_H_

#include <map>
#include "../modelo/EnemigoEstandar.h"
#include "../utiles/tipos.h"
#include "../threads/ColaTrabajo.h"

class ControladorEnemigos: public map <int, EnemigoEstandar*> {
public:
	ControladorEnemigos();
	~ControladorEnemigos();
	void controlUnit(EnemigoEstandar*);
	void strategy(bool);
	void update(bool);

private:
	void standarStrategy(EnemigoEstandar*);
};


#endif /* CONTROLADORENEMIGOS_H_ */
