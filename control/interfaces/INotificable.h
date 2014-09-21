/*
 * INotificable.h
 *
 *  Created on: 4/9/2014
 *      Author: manuel
 */

#ifndef INOTIFICABLE_H_
#define INOTIFICABLE_H_

class INotificable {
public:
	INotificable(){};
	virtual ~INotificable() {};

	virtual void eventoArriba() = 0;
	virtual void eventoSoltoArriba() = 0;
	virtual void eventoDerecha() = 0;
	virtual void eventoSoltoDerecha() = 0;
	virtual void eventoIzquierda() = 0;
	virtual void eventoSoltoIzquierda() = 0;
	//virtual void eventoAbajo() = 0;
	//virtual void eventoSoltoAbajo() = 0;
	virtual void eventoRESTART() = 0;
};



#endif /* INOTIFICABLE_H_ */
