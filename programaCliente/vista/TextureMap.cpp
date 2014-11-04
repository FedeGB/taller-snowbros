/*
 * TextureMap.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: rodrizapico
 */

#include "TextureMap.h"


TextureMap::TextureMap() {
	inicializado = false;
}

bool TextureMap::yaInicializado(){
	return inicializado;
}

bool TextureMap::init(){

	if (inicializado) return false;
	if (!loadMetadataTex()) return false;
	if (!loadPJTex()) return false;
	if (!loadCircleTex()) return false;
	if (!loadCuadTex()) return false;
	inicializado = true;
	return true;
}

bool TextureMap::loadMetadataTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(TEXTURA_VIDA);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	temp->tex = tex;
	(*this)[VIDAS1] = temp;

	tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}

	SDL_Color c = {255, 160, 100, 255};
	tex->generarTexto(FONT_TTF, 30, "Puntaje: 0", c);

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	temp->tex = tex;
	(*this)[PUNTAJE1] = temp;

	tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(IMAGEN_FONDO);

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	temp->tex = tex;
	(*this)[FONDO1] = temp;

	return true;
}

bool TextureMap::loadPJTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(SPRITE_SHEET);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 7 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 9 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 30 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[PJ1] = temp;

	return true;
}

bool TextureMap::loadCircleTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(TEXTURA_PELOTA);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(20);

	for (int i = 0; i < 20; i++) {
		float thita = (2 * i * PI / 20);
		temp->vertexes->x[i] = ( 128 + 128 * cos(thita) ) / 256.0f;
		temp->vertexes->y[i] = ( 128 - 128 * sin(thita) ) / 256.0f;
	}
	temp->tex = tex;
	(*this)[CIRCULO1] = temp;

	return true;
}

bool TextureMap::loadCuadTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(TEXTURA_LADRILLO);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;

	temp->tex = tex;
	(*this)[CUADRILATERO1] = temp;

	tex= new Textura();
	 temp = new TexAndVertexes;
		temp->vertexes = new Vertexes(4);
		temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
		temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
		temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
		temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	tex->generar(TEXTURA_HIELO);
	temp->tex =tex;
	(*this)[CUADRILATERO2] = temp;

	return true;
}

TextureMap::~TextureMap() {

	 for (TextureMap::iterator it = this->begin(); it != this->end(); it++){
		 if ((*it).second) {
			 delete (*it).second;
			 (*it).second = NULL;
		 }
	 }

}

