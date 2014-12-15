/*
 * TextureMap.h
 *
 *  Created on: Oct 23, 2014
 *      Author: rodrizapico
 */

#ifndef TEXTUREMAP_H_
#define TEXTUREMAP_H_

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utiles/Logger.h"
#include "../utiles/tipos.h"
#include "Textura.h"
#include "../servicios/ServicioControladorDeTexturas.h"


class TextureMap: public std::map<tipo_textura_t, Textura*>, public ServicioControladorDeTexturas {
public:

	// Crea un mapa de texturas.
	TextureMap();

	// Destruye el mapa de texturas.
	virtual ~TextureMap();

	// Carga todas las texturas que se utilizaran en el juego, junto con sus
	// areas de rendereo.
	bool inicializar();

	// Devuelve la textura correspondiente a tipoTextura.
	Textura * obtenerTextura(tipo_textura_t tipoTextura);

	// Devuelve una textura correspondiente al texto pedido.
	// A diferencia de las texturas de elementos de la UI, las texturas de
	// textos deben ser liberadas cuando se terminan de utilizar.
	virtual Textura * generarTexturaTexto(std::string texto, estilo_texto_t estilo);

private:

	// Carga las texturas correspondientes a los botones del juego.
	bool cargarTexturasBotones();

	// Carga las texturas correspondientes a los jugadores.
	bool cargarTexturasPJ();
	bool cargarTexturasEnemigos();
	bool cargarTexturasAuxiliares();
	//bool loadMetadataTex();
	//bool loadPJTex();
	//bool loadENESTex();
	//bool loadENTIFUETex();
	//bool loadCircleTex();
	//bool loadCuadTex();
	//bool loadGameOverTex();
	//bool inicializado;
	//bool loadSnowBallTex();
	//bool loadFireBallTex();
	//bool loadSorpresasTex();
	//bool loadLagunaTex();
};

#endif /* TEXTUREMAP_H_ */
