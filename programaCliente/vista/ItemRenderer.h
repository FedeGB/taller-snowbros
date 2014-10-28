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
#include "../modelo/formas/Circulo.h"
#include "../modelo/formas/Cuadrilatero.h"
#include "../modelo/formas/PoligonoRegular.h"
#include "../utiles/tipos.h"
#include "../utiles/Logger.h"
#include "TextureMap.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class ItemRenderer {
public:
	ItemRenderer();
	virtual ~ItemRenderer();
	static void render(SDL_Renderer* wRenderer, WorldItem * item, float escala);
	static float escalaPorDefecto;

private:

	static TextureMap textureMap;
	static void renderCirculo(Circulo * item, float escala);
	static void renderCuadrilatero(Cuadrilatero * item, float escala);
	static void renderPoligono(SDL_Renderer* renderer, PoligonoRegular * item, float escala);
	static void renderPJ(Personaje * item, float escala);
};

#endif /* ITEMRENDERER_H_ */
