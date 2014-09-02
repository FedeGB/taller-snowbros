/*
 * Objeto.h
 *
 *  Created on: 1/9/2014
 *      Author: manuel
 */

#ifndef OBJETO_H_
#define OBJETO_H_

#include <Box2D/Box2D.h>
#include "../utiles/tipos.h"

 #define DEGTORAD 0.0174532925199432957f
 #define RADTODEG 57.295779513082320876f

class Objeto {
public:
	Objeto();
	virtual ~Objeto();

	b2Vec2 posicion();
	void posicion(b2Vec2);
	void posicion(float32 x, float32 y);

	Tamano tamano();
	virtual void tamano(Tamano);
	virtual void tamano(uint32 alto, uint32 ancho);

	int32 escala();
	void escala(int32);

	int32 angulo();
	void angulo(int32);

	SDL_Color color();
	Uint32 colorUint32();
	void color(SDL_Color);

	uint32 masa();
	void masa(uint32);

	bool esEstatico();
	void esEstatico(bool);

private:
	b2Vec2 oPosicion;
	Tamano oTamano;
	int32 oEscala;
	int32 oAngulo;
	SDL_Color oColor;
	uint32 oMasa;
	bool oEsEstatico;
};

#endif /* OBJETO_H_ */
