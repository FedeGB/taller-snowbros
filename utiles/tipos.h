/*
 * tipos.h
 *
 *  Created on: 2/9/2014
 *      Author: manuel
 */

#ifndef TIPOS_H_
#define TIPOS_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "../modelo/interfaces/IDibujable.h"
#include "../control/interfaces/IObservador.h"

#define PI 3.14159265
const float32 DEGTORAD = 0.0174532925199432957f;
const float32 RADTODEG = 57.295779513082320876f;


typedef std::vector<IObservador*> ListaObservadores;
//typedef std::vector<IDibujable*> ListaDibujables;

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

enum TECLAS
{
	ARRIBA,
	ABAJO,
	IZQUIERDA,
	DERECHA,
	SOLTOARRIBA,
	SOLTOABAJO,
	SOLTOIZQUIERDA,
	SOLTODERECHA,
	RESTART, // RESTART = tecla r
};

#endif /* TIPOS_H_ */
