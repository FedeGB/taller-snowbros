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

class RectanguloDibujable: public Objeto, public IDibujable
{
public:

	RectanguloDibujable(){};
	virtual ~RectanguloDibujable(){};

	SDL_Rect getRecuadroDeDibujo()
	{
		return getSDL_Rect();
	}
};

#endif /* RECTANGULO_H_ */
