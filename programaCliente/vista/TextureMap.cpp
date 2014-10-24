/*
 * TextureMap.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: rodrizapico
 */

#include "TextureMap.h"



SDL_Texture * cargarImagen(SDL_Renderer* renderer, std::string path) {
	Logger& log = * Logger::Instancia();

	// textura final
	SDL_Texture * texturaNueva = NULL;
	//cargamos imagen
	SDL_Surface* surfaceCargada = IMG_Load( path.c_str() );
	if( surfaceCargada  == NULL ){
		log.log(DIBUJABLELOG, ERROR, "Imposible cargar la imagen " +path+ " " + IMG_GetError());
		return NULL;
	}
	else
	{ 	//Setear color transparente
		//SDL_SetColorKey( surfaceCargada , SDL_TRUE, SDL_MapRGB( surfaceCargada ->format, 0, 0xFF, 0xFF ) );
		//crea nueva textura de la surface
		texturaNueva = SDL_CreateTextureFromSurface( renderer, surfaceCargada  );
		if( texturaNueva == NULL ){
			log.log(DIBUJABLELOG,ERROR, "Imposible crear textura desde "+path);
			return NULL;
		}
		//eliminamos la vieja surface
		SDL_FreeSurface( surfaceCargada );
	}
	//devuelve el valor de exito
	return texturaNueva;
}




TextureMap::TextureMap() {
	inicializado = false;
}

bool TextureMap::yaInicializado(){
	return inicializado;
}

bool TextureMap::init(SDL_Renderer* renderer){

	if (!loadPJTexAndRects(renderer)) return false;
	inicializado = true;
	return true;
}

bool TextureMap::loadPJTexAndRects(SDL_Renderer* renderer){

	// TODO: sacar hardcodeo del path de imagen.
	SDL_Texture *  tex = cargarImagen(renderer, "imagenes/playerSpritesheet.png");
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}

	TexAndRect temp; // = (*this)[PARADOIZQUIERDA];
	temp.rect = new SDL_Rect();
	temp.rect->x =   7;
	temp.rect->y =   9;
	temp.rect->w =  23;
	temp.rect->h = 26;
	temp.tex = tex;
	(*this)[PARADOIZQUIERDA] = temp;

	//temp = (*this)[MOVIENDOIZQUIERDA1];
	temp.rect = new SDL_Rect();
	temp.rect->x =  37;
	temp.rect->y =   9;
	temp.rect->w =  23;
	temp.rect->h = 26;
	temp.tex = tex;
	(*this)[MOVIENDOIZQUIERDA1] = temp;

	//temp = (*this)[MOVIENDOIZQUIERDA2];
	temp.rect = new SDL_Rect();
	temp.rect->x = 62;
	temp.rect->y =   9;
	temp.rect->w =  23;
	temp.rect->h = 26;
	temp.tex = tex;
	(*this)[MOVIENDOIZQUIERDA2] = temp;

	//temp = (*this)[MOVIENDOIZQUIERDA3];
	temp.rect = new SDL_Rect();
	temp.rect->x = 92;
	temp.rect->y =   9;
	temp.rect->w =  23;
	temp.rect->h = 26;
	temp.tex = tex;
	(*this)[MOVIENDOIZQUIERDA3] = temp;

	//temp = (*this)[MOVIENDOIZQUIERDA4];
	temp.rect = new SDL_Rect();
	temp.rect->x = 62;
	temp.rect->y =   9;
	temp.rect->w =  23;
	temp.rect->h = 26;
	temp.tex = tex;
	(*this)[MOVIENDOIZQUIERDA4] = temp;

	//temp = (*this)[SALTANDOIZQUIERDA1];
	temp.rect = new SDL_Rect();
	temp.rect->x = 152;
	temp.rect->y =   6;
	temp.rect->w =  23;
	temp.rect->h = 29;
	temp.tex = tex;
	(*this)[SALTANDOIZQUIERDA1] = temp;

	//temp = (*this)[SALTANDOIZQUIERDA2];
	temp.rect = new SDL_Rect();
	temp.rect->x = 184;
	temp.rect->y =   6;
	temp.rect->w =  23;
	temp.rect->h = 29;
	temp.tex = tex;
	(*this)[SALTANDOIZQUIERDA2] = temp;

	//temp = (*this)[SALTANDOIZQUIERDA3];
	temp.rect = new SDL_Rect();
	temp.rect->x = 215;
	temp.rect->y =   6;
	temp.rect->w =  23;
	temp.rect->h = 29;
	temp.tex = tex;
	(*this)[SALTANDOIZQUIERDA3] = temp;

	//temp = (*this)[SALTANDOIZQUIERDA4];
	temp.rect = new SDL_Rect();
	temp.rect->x = 249;
	temp.rect->y =   6;
	temp.rect->w =  23;
	temp.rect->h = 29;
	temp.tex = tex;
	(*this)[SALTANDOIZQUIERDA4] = temp;

	//temp = (*this)[SALTANDOIZQUIERDA5];
	temp.rect = new SDL_Rect();
	temp.rect->x = 118;
	temp.rect->y =   6;
	temp.rect->w =  23;
	temp.rect->h = 29;
	temp.tex = tex;
	(*this)[SALTANDOIZQUIERDA5] = temp;

	return true;
}

TextureMap::~TextureMap() {
	// TODO Auto-generated destructor stub
}

