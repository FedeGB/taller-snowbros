/*
 * Rectangulo.h
 *
 *  Created on: 2/9/2014
 *      Author: manuel
 */

#ifndef RECTANGULO_H_
#define RECTANGULO_H_

#include "../Objeto.h"
#include "../interfaces/IDibujable.h"
#include "../../control/interfaces/INotificable.h"

class RectanguloDibujable: public Objeto, public IDibujable, public INotificable
{
public:

	RectanguloDibujable(){};
	virtual ~RectanguloDibujable(){};

	SDL_Rect getRecuadroDeDibujo()
	{
		return getSDL_Rect();
	}

	virtual void eventoArriba(){
		moverY(-10.0);
	}

	virtual void eventoAbajo(){
		moverY(10.0);
	}

	virtual void eventoDerecha(){
		moverX(10.0);
	}

	virtual void eventoIzquierda(){
		moverX(-10.0);
	}

	virtual void eventoRESTART(){
		posicion( 30.0, 30.0);
	}
};

#endif /* RECTANGULO_H_ */
