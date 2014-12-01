/*
 * Deserializador.h
 *
 *  Created on: Oct 18, 2014
 *      Author: rodrizapico
 */

#ifndef DESERIALIZADOR_H_
#define DESERIALIZADOR_H_

#include <string>
#include "../modelo/WorldItem.h"
#include "../modelo/Metadata.h"
#include "../modelo/Personaje.h"
#include "../modelo/Fireball.h"
#include "../modelo/EnemigoEstandar.h"
#include "../modelo/EnemigoTiraFuego.h"
#include "../modelo/BolaEnemigo.h"
#include "../modelo/formas/Circulo.h"
#include "../modelo/formas/Cuadrilatero.h"
#include "../modelo/formas/PoligonoRegular.h"

#include "../modelo/Sonido.h"
#include "../modelo/Sorpresa.h"
#include "../modelo/Laguna.h"

class Deserializador {
public:
	Deserializador();
	virtual ~Deserializador();
	static WorldItem * deserializar(std::string serializado);
};

#endif /* DESERIALIZADOR_H_ */
