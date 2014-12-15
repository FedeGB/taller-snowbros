/*
 * Fabrica.h
 *
 *  Created on: Dec 9, 2014
 *      Author: rodrizapico
 */

#ifndef FABRICA_H_
#define FABRICA_H_

#include "ServicioFabricaDeObjetos.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/BolaDeNieve.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/PelotaDeNieve.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/BolaDeFuego.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/EnemigoFuego.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/Sorpresa.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/SorpresaNieveMaLejos.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/SorpresaNieveMasPotente.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/SorpresaCorrer.h"


class Fabrica: public ServicioFabricaDeObjetos {
public:
	Fabrica(ControladorJuego * controlador);
	virtual ~Fabrica();

	// Fabrica una bola de nieve y la agrega al modelo.
	virtual void fabricarBolaDeNieve(Personaje * creador);

	// Fabrica una bola de fuego y la agrega al modelo.
	virtual void fabricarBolaDeFuego(EnemigoFuego * creador);

	// Fabrica una pelota de nieve y la agrega al modelo.
	virtual void fabricarPelotaDeNieve(Enemigo * creador);

	// Fabrica una sorpresa y la agrega al modelo.
	virtual void fabricarSorpresa(PelotaDeNieve * creador);

private:
	ControladorJuego * controlador;
};

#endif /* FABRICA_H_ */
