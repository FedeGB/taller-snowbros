/*
 * EnemigoEstandar.h
 *
 *  Created on: Nov 8, 2014
 *      Author: fedevm
 */

#ifndef ENEMIGOESTANDAR_H_
#define ENEMIGOESTANDAR_H_

#include "Personaje.h"
#include <SDL2/SDL.h>
#include "../utiles/tipos.h"


class EnemigoEstandar: public Personaje {

public:
	sprite_t spriteStun;
	EnemigoEstandar();
	virtual ~EnemigoEstandar();

	virtual std::string serializar();
};



#endif /* ENEMIGOESTANDAR_H_ */
