/*
 * Enemigo.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#include "Enemigo.h"

Enemigo::Enemigo() {
	salud = 10;
}

Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}


// Aplica la modificacion indicada sobre el SerVivo.
void Enemigo::aplicar(Enemigo * modificacion){

	SerVivo::aplicar((SerVivo*)modificacion);
	salud = modificacion->salud;
}

// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
void Enemigo::aplicarSobre(ObjetoModelo * objeto){
	objeto->aplicar(this);
}

// Dibuja la bola de nieve que cubre al enemigo, si este esta atrapado.
void Enemigo::dibujarBolaDeNieve(Camara * camara){

	FiguraGeometrica * figuraEnCoordenadasCamara = espacioOcupado->cambiarDeCoordenadas(camara->obtenerOrigen());


	// Escala para que la bola sea un poco mas grande que el enemigo.
	figuraEnCoordenadasCamara->escalar(figuraEnCoordenadasCamara->calcularBaricentro(), 1.2);

	// Escala al sistema de coordenadas de la pantalla.
	Vector2D origen; origen.x = 0; origen.y = 0;
	figuraEnCoordenadasCamara->escalar(origen, camara->obtenerEscala());

	// Obtiene la textura correspondiente al objeto.
	Textura * tex;
	if (salud <= 0) tex = LocalizadorDeServicios::obtenerControladorDeTexturas()->obtenerTextura(PELOTADENIEVE);
	else tex = LocalizadorDeServicios::obtenerControladorDeTexturas()->obtenerTextura(BOLAENEMIGOPARCIAL);


	const float SALUDINICIAL = 10;
	// Obtiene la region de la textura a utilizar
	FiguraGeometrica * sprite;
	if (salud <= 0) sprite = FiguraGeometrica::generarRectangulo(1,1,1,1,0);
	else if (salud <= SALUDINICIAL / 2) sprite = FiguraGeometrica::generarRectangulo(24/46.0f,0,20/46.0f,1.0f,0);
	else if (salud < SALUDINICIAL) sprite = FiguraGeometrica::generarRectangulo(0,0,20/46.0f,1.0f,0);

	// Dibuja el objeto.
	tex->dibujar(figuraEnCoordenadasCamara, sprite);

	delete figuraEnCoordenadasCamara;
	delete sprite;
}

// Dibuja el objeto en pantalla.
void Enemigo::dibujar(Camara * camara){

	// Checkea que el objeto sea visible.
	if (!camara->esVisible(this)) return;

	// Dibuja al enemigo.
	ObjetoModelo::dibujar(camara);

	// Dibuja la animacion de bola de nieve, si es que esta atrapado.
	const float SALUDINICIAL = 10;
	if (salud < SALUDINICIAL) dibujarBolaDeNieve(camara);
}
