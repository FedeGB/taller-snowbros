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

class Vertexes{
public:
	float * x;
	float * y;
	Vertexes(int numVertexes){
		x = new float[numVertexes];
		y = new float[numVertexes];
	}
	~Vertexes(){
		delete[] x;
		delete[] y;
	}
};

class TexAndVertexes{
public:
	Textura * tex;
	Vertexes * vertexes;
	TexAndVertexes(){ tex = NULL; vertexes = NULL;}
	virtual ~TexAndVertexes(){

		if (tex){
			delete tex;
			tex = NULL;
		}
		if (vertexes != NULL) {
			delete vertexes;
			vertexes = NULL;
		}
	}

};

class TextureMap: public std::map<sprite_t, TexAndVertexes*> {
public:
	TextureMap();
	virtual ~TextureMap();

	bool yaInicializado();
	bool init();

private:
	bool loadMetadataTex();
	bool loadPJTex();
	bool loadENESTex();
	bool loadENTIFUETex();
	bool loadCircleTex();
	bool loadCuadTex();
	bool loadGameOverTex();
	bool inicializado;
	bool loadSnowBallTex();
	bool loadFireBallTex();
	bool loadSorpresasTex();
	bool loadLagunaTex();
	bool loadAgujeroTex();
};

#endif /* TEXTUREMAP_H_ */
