/*
 * tipos.h
 *
 *  Created on: 2/9/2014
 *      Author: manuel
 */

#ifndef TIPOS_H_
#define TIPOS_H_

#include <SDL2/SDL.h>

class Tamano {
public:
	Tamano();
	inline Tamano(int alto, int ancho) : tAlto(alto) , tAncho(ancho) {};
	virtual ~Tamano(){};

	inline int alto(){
		return tAlto;
	}

	inline void alto(int a){
		tAlto = a;
	}

	inline int ancho(){
		return tAncho;
	}

	inline void ancho(int a){
		tAncho = a;
	}

	inline void operator=(Tamano otroTamano){
		tAlto = otroTamano.alto();
		tAncho = otroTamano.ancho();
	}

private:
	int tAlto, tAncho;
};



#endif /* TIPOS_H_ */
