/*
 * Puntaje.h
 *
 *  Created on: 20/10/2014
 *      Author: manuel
 */

#ifndef PUNTAJE_H_
#define PUNTAJE_H_

#include "Texto.h"

class Puntaje{
public:
	Puntaje(){
		SDL_Color c = {255, 160, 100, 255};
		txt = new Texto("fuentes/ubuntu.ttf", 30, "HoLaNdA", c);
	}
	virtual ~Puntaje(){}


	void render(){
		txt->dibujar();
	}


private:
	Texto* txt;
};



#endif /* PUNTAJE_H_ */
