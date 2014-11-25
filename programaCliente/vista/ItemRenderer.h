/*
 * ItemRenderer.h
 *
 *  Created on: Oct 19, 2014
 *      Author: rodrizapico
 */

#ifndef ITEMRENDERER_H_
#define ITEMRENDERER_H_

#include "../modelo/WorldItem.h"
#include "../modelo/Personaje.h"
#include "../modelo/poder.h"
#include "../modelo/EnemigoEstandar.h"
#include "../modelo/BolaEnemigo.h"
#include "../modelo/Metadata.h"
#include "../modelo/formas/Circulo.h"
#include "../modelo/formas/Cuadrilatero.h"
#include "../modelo/formas/PoligonoRegular.h"
#include "../utiles/tipos.h"
#include "../utiles/Logger.h"
#include "TextureMap.h"
#include <SDL2/SDL.h>

#include "SonidosMap.h"

#include "../modelo/Sorpresa.h"

class ItemRenderer {
public:
	ItemRenderer();
	virtual ~ItemRenderer();
	static void render(WorldItem * item, float escala);
	static float escalaPorDefecto;

private:

	static b2Vec2 tamanioMundo;
	static b2Vec2 posicionCamara;
	static TextureMap textureMap;
	static void renderCirculo(Circulo * item, float escala);
	static void renderCuadrilatero(Cuadrilatero * item, float escala);
	static void renderPoligono(PoligonoRegular * item, float escala);
	static void renderPJ(Personaje * item, float escala);
	static void renderENES(EnemigoEstandar * item, float escala);
	static void renderPoder(poder *item,float escala);
	static void renderMetadataFondo(Metadata * item);
	static void renderMetadataHUD(Metadata * item);
	static void renderBola(BolaEnemigo * item, float escala);

	static SonidosMap sonidosMap;
	static void renderSonido(Sonido * item);

	static void renderSorpresa(Sorpresa*, float);
};

#endif /* ITEMRENDERER_H_ */
