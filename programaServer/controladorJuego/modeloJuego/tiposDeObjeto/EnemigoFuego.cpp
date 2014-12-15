/*
 * EnemigoFuego.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "EnemigoFuego.h"
#include "../../../servicios/LocalizadorDeServicios.h"
#include "../../../servicios/ServicioFabricaDeObjetos.h"

EnemigoFuego::EnemigoFuego() {
	// TODO Auto-generated constructor stub

}

// Levanta el personaje desde el archivo de configuracion Json.
EnemigoFuego::EnemigoFuego(std::string sConfig, int numeroObjeto): Enemigo(sConfig, numeroObjeto){

}

EnemigoFuego::~EnemigoFuego() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string EnemigoFuego::serializar(){

	std::string buff;

	buff = SSTR(TIPOENEMIGOFUEGO << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << estado << SEPARADORDATOS << salud << SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}

bool EnemigoFuego::isObjectInDirectionRange(b2World* world, Enemigo * unit, sensor_t obj, float angle, float length, int range) {
	int div;
	for(int i = -range/2; i < range/2; i++) {
		if(i < 0) div = -i-1;
		else if (i > 0) div = i+1;
		else div = 1;
		if(Enemigo::isObjectInDirection(world, this, obj, angle + i, length/div)) {
			return true;
		}
	}
	return false;
}

// Actualiza la informacion del objeto para poder dibujarlo.
void EnemigoFuego::actualizar(Personaje * pj){

	Enemigo::actualizar(pj);

	float SALUDINICIAL = 10;
	if (salud < SALUDINICIAL) return;

	if((isObjectInDirectionRange(cuerpoB2D->GetWorld(), this, PERSONAJE, 90, 8, 3.0f) && orientacion == DERECHA) || (isObjectInDirectionRange(cuerpoB2D->GetWorld(), this, PERSONAJE, 270, 8, 3.0f) && orientacion == IZQUIERDA)) {
		atacando = true;
	}

	// Ataque.
	if(atacando || comenzoAtaque){

		estado = ATACANDO;

		// Ataca.
		comenzoAtaque = true;
		if ( (acumuladorAtaque % 35) == 29) {
			LocalizadorDeServicios::obtenerFabricaDeObjetos()->fabricarBolaDeFuego(this);
			comenzoAtaque = false;
		}

		acumuladorAtaque++;
	} else acumuladorAtaque = 0;

}
