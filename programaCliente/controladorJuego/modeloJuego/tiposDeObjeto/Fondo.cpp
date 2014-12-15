/*
 * Fondo.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: rodrizapico
 */

#include "Fondo.h"

Fondo::Fondo(Camara * c) {
	cam = c;
}

Fondo::~Fondo() {
	// TODO Auto-generated destructor stub
}

void Fondo::aplicarSobre(ObjetoModelo * objeto){

}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string Fondo::serializar(){
	return "hola";
}

// Obtiene la textura que representa al objeto.
Textura * Fondo::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(FONDO);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * Fondo::obtenerSprite(){

	float x = cam->obtenerOrigen().x / LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.x;
	float y = cam->obtenerOrigen().y / LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.y;
	float w = cam->calcularAncho() / LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.x;
	float h = cam->calcularAlto() / LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.y;
	FiguraGeometrica * sprite = FiguraGeometrica::generarRectangulo(x, y, w, h, 0);

	return sprite;
}

// Dibuja el objeto en pantalla.
void Fondo::dibujar(Camara * camara){

	FiguraGeometrica * aux = FiguraGeometrica::generarRectangulo(0,0,720,640,0);

	// Obtiene la textura correspondiente al objeto.
	Textura * tex = obtenerTextura();

	// Obtiene la region de la textura a utilizar
	FiguraGeometrica * sprite = obtenerSprite();

	// Dibuja el objeto.
	tex->dibujar(aux, sprite);

	delete aux;
	delete sprite;
}
