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

class RectanguloDibujable: public Objeto, public IDibujable
{
public:
	RectanguloDibujable(){};
	virtual ~RectanguloDibujable(){};

	inline void dibujar(SDL_Renderer* renderer)
	{
		SDL_Rect rectangulo = getSDL_Rect();
		SDL_SetRenderDrawColor( renderer, color().r, color().g, color().b, color().a);
		SDL_RenderFillRect( renderer, &rectangulo );
	}

	inline void dibujar(SDL_Surface* surface)
	{
		SDL_Rect rectangulo = getSDL_Rect();
		SDL_FillRect(surface, &rectangulo, colorUint32());
	}

	inline SDL_Rect getSDL_Rect()
	{
		SDL_Rect r = {  (int)posicion().x , (int)posicion().y ,(int)tamano().ancho() , (int)tamano().alto() };
		return r;
	}
};

#endif /* RECTANGULO_H_ */
