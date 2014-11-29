/*
 * SonidosMap.h
 *
 *  Created on: 7/11/2014
 *      Author: manuel
 */

#ifndef SONIDOSMAP_H_
#define SONIDOSMAP_H_

#include <map>
#include "../utiles/tipos.h"
#include "../modelo/Sonido.h"

class SonidosMap : public std::map<sonidos_t, Sonido*>{
public:
	SonidosMap();
	virtual ~SonidosMap();

	bool yaInicializado();
	bool init();
	void actualizarEstados();

private:
	bool inicializado;

	bool loadMusiquitaDeFondo();

	bool loadSonidoSalto();
	bool loadSonidoExplosion();
	bool loadSonidoDisparo();
	bool loadSonidoDisparoSorpresa();
	bool loadSonidoSaltoSumergido();
};

#endif /* SONIDOSMAP_H_ */
