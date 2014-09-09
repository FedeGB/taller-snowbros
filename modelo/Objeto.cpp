/*
 * Objeto.cpp
 *
 *  Created on: 1/9/2014
 *      Author: manuel
 */

#include "Objeto.h"

Objeto::Objeto() :
	oPosicion(0.0, 0.0), oTamano(Tamano(100, 100)),
	oEscala(1.0), oAngulo(0), oMasa(10.0), oEsEstatico(true)
{
	oColor.r = 0.0; oColor.g = 0.0; oColor.b = 0.0; oColor.a = 1.0;
}

Objeto::~Objeto() {}

b2Vec2 Objeto::posicion(){
	return oPosicion;
}
void Objeto::posicion(b2Vec2 p){
	oPosicion.Set(p.x , p.y);
}
void Objeto::posicion(float32 x, float32 y){
	oPosicion.Set(x , y);
}

Tamano Objeto::tamano(){
	return oTamano;
}
void Objeto::tamano(Tamano t){
	oTamano = t;
}
void Objeto::tamano(uint32 alto, uint32 ancho){
	oTamano.alto(alto);
	oTamano.ancho(ancho);
}

int32 Objeto::escala(){
	return oEscala;
}
void Objeto::escala(int32 e){
	oEscala = e;
}

int32 Objeto::angulo(){
	return RADTODEG * oAngulo;
}
void Objeto::angulo(int32 a){
	oAngulo = DEGTORAD * a;
}

SDL_Color Objeto::color(){
	return oColor;
}
Uint32 Objeto::colorUint32(){
	Uint32 uint;
	Uint8* ptr = (Uint8*) &uint;

	*ptr = oColor.b; ptr++;
	*ptr = oColor.g; ptr++;
	*ptr = oColor.r; ptr++;
	*ptr = oColor.a;

	return uint;
}
void Objeto::color(SDL_Color c){
	oColor.r = c.r;
	oColor.g = c.g;
	oColor.b = c.b;
	oColor.a = c.a;
}

uint32 Objeto::masa(){
	return oMasa;
}
void Objeto::masa(uint32 m){
	oMasa = m;
}


void Objeto::moverX(float32 x){
	oPosicion.x += x;
}

void Objeto::moverY(float32 y){
	oPosicion.y += y;
}

void Objeto::moverXY(float32 x, float32 y){
	oPosicion.x += x;
	oPosicion.y += y;
}

SDL_Rect Objeto::getSDL_Rect()
{
	SDL_Rect r = {  (int)posicion().x , (int)posicion().y ,(int)tamano().ancho() , (int)tamano().alto() };
	return r;
}
