/*
 * IObservador.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef IOBSERVADOR_H_
#define IOBSERVADOR_H_

class IObservador {
public:
	IObservador() {};
	virtual ~IObservador() {};

	virtual void notificar(int EVENTO) = 0;
};



#endif /* IOBSERVADOR_H_ */
