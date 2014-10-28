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
	tex->generar("imagenes/vida.png");

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
	tex->generarTexto("fuentes/Ubuntu-B.ttf", 30, "Puntaje: 0", c);

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
	tex->generar("imagenes/fondo2.png");

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
	tex->generar("imagenes/playerSpritesheet1.png");

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 7 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 9 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 30 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[PARADOIZQUIERDA] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 37 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 9 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 60 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[MOVIENDOIZQUIERDA1] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 62 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 9 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 85 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[MOVIENDOIZQUIERDA2] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 92 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 9 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 115 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[MOVIENDOIZQUIERDA3] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 62 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 9 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 85 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[MOVIENDOIZQUIERDA4] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 152 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 6 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 175 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[SALTANDOIZQUIERDA1] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 184 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 6 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 207 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[SALTANDOIZQUIERDA2] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 215 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 6 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 238 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[SALTANDOIZQUIERDA3] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 249 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 6 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 272 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[SALTANDOIZQUIERDA4] = temp;

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 118 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 6 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 141 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[SALTANDOIZQUIERDA5] = temp;

	return true;
}

bool TextureMap::loadCircleTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar("imagenes/pelota.png");

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
	tex->generar("imagenes/ladrillo.png");

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;

	temp->tex = tex;
	(*this)[CUADRILATERO1] = temp;

	return true;
}

TextureMap::~TextureMap() {
	// TODO Auto-generated destructor stub
}

