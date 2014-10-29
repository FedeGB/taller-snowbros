/*
 * WorldItem.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: rodrizapico
 */

#include "WorldItem.h"

WorldItem::WorldItem() {
	angulo = 0;
	tipo = CUADRILATERO;
}

WorldItem::~WorldItem() {

}

void WorldItem::aCoordenadasLocales(b2Vec2 posicionCamara){
	posicion = posicion - posicionCamara;
}
