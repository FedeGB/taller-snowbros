/*
 * BolaEnemigo.h
 *
 *  Created on: 24/11/2014
 *      Author: coco
 */

#ifndef BOLAENEMIGO_H_
#define BOLAENEMIGO_H_
#include "../modelo/formas/Circulo.h"
#include "../modelo/Sorpresa.h"
#include "../modelo/SorpresaVida.h"
#include "../modelo/SorpresaCorrer.h"
#include "../modelo/SorpresaNieveMasPotente.h"
#include "../modelo/SorpresaNieveMasLejos.h"

class BolaEnemigo:public Circulo {
public:
	BolaEnemigo(b2Body *);
	~BolaEnemigo();
	void Impulso(orientation_t);
	virtual std::string serializar();
	void aumentarTiempo();
	void setDelete(){
		toDelete = true;
	}
	bool forDelete(){
		return toDelete;
	}

	void setCayoPorAgujero(bool);
	bool cayoPorAgujero();
	void moverArriba();
	void notBounce();

protected:
	b2Body * bodyB2D;
	sprite_t activeSprite;
	int tiempoDeVida;
	bool toDelete;

	bool cayo;
};

#endif /* BOLAENEMIGO_H_ */
