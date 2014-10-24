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

class TexAndRect{
public:
	SDL_Texture * tex;
	SDL_Rect * rect;
	TexAndRect(){ tex = NULL; rect = NULL;}
	virtual ~TexAndRect(){}
};

class TextureMap: public std::map<sprite_t, TexAndRect> {
public:
	TextureMap();
	virtual ~TextureMap();

	bool yaInicializado();
	bool init(SDL_Renderer* renderer);

private:
	bool loadPJTexAndRects(SDL_Renderer* renderer);
	bool inicializado;
};

#endif /* TEXTUREMAP_H_ */
