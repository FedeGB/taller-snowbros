/*
 * ObjetoModelo.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "ObjetoModelo.h"

#include "../ControladorJuego.h"
#include "tiposDeObjeto/BolaDeFuego.h"
#include "tiposDeObjeto/BolaDeNieve.h"
#include "tiposDeObjeto/EnemigoEstandar.h"
#include "tiposDeObjeto/EnemigoFuego.h"
#include "tiposDeObjeto/Ladrillo.h"
#include "tiposDeObjeto/Personaje.h"

// Crea un elemento nuevo del modelo en base a los datos serializados.
ObjetoModelo * ObjetoModelo::deserializar(std::string serializado){

	ObjetoModelo * objeto;

	// Indica donde termina el parseo del tipo correspondiente y se debe comenzar a
	// parsear los puntos del objeto.
	int indice;

	// Separa el los campos del mensaje.
	std::vector<std::string> buff;
	split(buff, serializado, SEPARADORDATOS, no_empties);

	// Utilizo buff[0] para determinar el tipo de objeto a instanciar.
	switch(atoi(buff[0].c_str())){
	case TIPOPERSONAJE:{
		Personaje * personaje = new Personaje;
		personaje->nombre = buff[3];
		personaje->estado = (SerVivo::estado_t) atoi(buff[4].c_str());
		indice = 5;
		objeto = personaje;
		break;
		}
	case TIPOENEMIGOESTANDAR:{
		EnemigoEstandar * enemigo = new EnemigoEstandar;
		enemigo->estado = (SerVivo::estado_t) atoi(buff[3].c_str());
		indice = 4;
		objeto = enemigo;
		break;
		}
	case TIPOENEMIGOFUEGO:{
		EnemigoFuego * enemigo = new EnemigoFuego;
		enemigo->estado = (SerVivo::estado_t) atoi(buff[3].c_str());
		indice = 4;
		objeto = enemigo;
		break;
		}
	case TIPOLADRILLO:{
		Ladrillo * ladrillo = new Ladrillo;
		objeto = ladrillo;
		indice = 3;
		break;
		}
	case TIPOBOLADEFUEGO:{
		BolaDeFuego * bola = new BolaDeFuego;
		objeto = bola;
		indice = 3;
		break;
		}
	case TIPOBOLADENIEVE:{
		BolaDeNieve * bola = new BolaDeNieve;
		objeto = bola;
		indice = 3;
		break;
		}
	case TIPOBOLAENEMIGO:{
		indice = 3;
		break;
		}
	}

	objeto->orientacion = (orientacion_t) atoi(buff[1].c_str());
	objeto->rotacion = (float) atof(buff[2].c_str());

	objeto->espacioOcupado->puntosOrdenados.clear();

	// Lee el numero de lados.
	int numeroLados = atoi(buff[indice].c_str());

	// Carga uno por uno los puntos de la figura.
	for(int i = 0; i < numeroLados; i++){
		Vector2D punto;
		punto.x = (float) atoi(buff[indice + i].c_str());
		punto.y = (float) atoi(buff[indice + i + 1].c_str());
		objeto->espacioOcupado->puntosOrdenados.push_back(punto);
	}

	return objeto;
}


// Inicializa al objeto.
void ObjetoModelo::inicializar(){
}

// Elimina lo que sea necesario.
void ObjetoModelo::limpiar(){
	cuerpoB2D->GetWorld()->DestroyBody(cuerpoB2D);
	delete espacioOcupado;
}

// Actualiza la informacion del objeto para poder dibujarlo.
void ObjetoModelo::actualizar(){

	rotacion = cuerpoB2D->GetAngle();

	Vector2D posicionAnterior = espacioOcupado->calcularBaricentro();
	Vector2D posicionActual;
	posicionActual.x = cuerpoB2D->GetPosition().x;
	posicionActual.y = cuerpoB2D->GetPosition().y;

	espacioOcupado->trasladar(posicionActual - posicionAnterior);

	if (cayoPorAgujero){

		acumuladorCaida--;
		if (acumuladorCaida == 0){
			b2Vec2 p = cuerpoB2D->GetPosition();
			p.y = 1;
			this->cuerpoB2D->SetTransform( p, 0);
			cayoPorAgujero = false;
		}

	} else acumuladorCaida = 40;
}
