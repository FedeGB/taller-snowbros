/*
 * ObjetoModelo.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "ObjetoModelo.h"

#include "../ControladorJuego.h"
#include "Camara.h"
#include "tiposDeObjeto/BolaDeFuego.h"
#include "tiposDeObjeto/BolaDeNieve.h"
#include "tiposDeObjeto/PelotaDeNieve.h"
#include "tiposDeObjeto/EnemigoEstandar.h"
#include "tiposDeObjeto/EnemigoFuego.h"
#include "tiposDeObjeto/Ladrillo.h"
#include "tiposDeObjeto/Laguna.h"
#include "tiposDeObjeto/Agujero.h"
#include "tiposDeObjeto/Personaje.h"
#include "tiposDeObjeto/SorpresaCorrer.h"
#include "tiposDeObjeto/SorpresaNieveMaLejos.h"
#include "tiposDeObjeto/SorpresaNieveMasPotente.h"

// Crea un elemento nuevo del modelo en base a los datos serializados.
ObjetoModelo * ObjetoModelo::deserializar(std::string serializado){

	ObjetoModelo * objeto;

	// Indica donde termina el parseo del tipo correspondiente y se debe comenzar a
	// parsear los puntos del objeto.
	int indice;

	// Separa los campos del mensaje.
	std::vector<std::string> buff;
	split(buff, serializado, SEPARADORDATOS, no_empties);

	// Utilizo buff[0] para determinar el tipo de objeto a instanciar.
	switch(atoi(buff[0].c_str())){
	case TIPOPERSONAJE:{

		Personaje * personaje = new Personaje;
		personaje->nombre = buff[3];
		personaje->estado = (SerVivo::estado_t) atoi(buff[4].c_str());
		personaje->inmune = (buff[5] == "1");
		personaje->murio = (buff[6] == "1");
		indice = 7;
		objeto = personaje;
		break;
		}
	case TIPOENEMIGOESTANDAR:{
		EnemigoEstandar * enemigo = new EnemigoEstandar;
		enemigo->estado = (SerVivo::estado_t) atoi(buff[3].c_str());
		enemigo->salud = (float) atof(buff[4].c_str());
		indice = 5;
		objeto = enemigo;
		break;
		}
	case TIPOENEMIGOFUEGO:{
		EnemigoFuego * enemigo = new EnemigoFuego;
		enemigo->estado = (SerVivo::estado_t) atoi(buff[3].c_str());
		enemigo->salud = (float) atof(buff[4].c_str());
		indice = 5;
		objeto = enemigo;
		break;
		}
	case TIPOLADRILLO:{
		Ladrillo * ladrillo = new Ladrillo;
		objeto = ladrillo;
		indice = 3;
		break;
		}
	case TIPOLAGUNA:{
		Laguna * ladrillo = new Laguna;
		objeto = ladrillo;
		indice = 3;
		break;
		}
	case TIPOAGUJERO:{
		Agujero * ladrillo = new Agujero;
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
	case TIPOPELOTADENIEVE:{
		// TODO: implementar pelota nieve.
		PelotaDeNieve * pelota = new PelotaDeNieve;
		objeto = pelota;
		indice = 3;
		break;
		}
	case TIPOSORPRESACORRER:{
		// TODO: implementar pelota nieve.
		SorpresaCorrer * sorpresa = new SorpresaCorrer;
		objeto = sorpresa;
		indice = 3;
		std::cout << "sorpresa para destruir?" << ( (buff[12] == "1")  ? "si" : "no" )<< std::endl;
		break;
		}
	case TIPOSORPRESANIEVEMASLEJOS:{
		// TODO: implementar pelota nieve.
		SorpresaNieveMaLejos * sorpresa = new SorpresaNieveMaLejos;
		objeto = sorpresa;
		indice = 3;
		std::cout << "sorpresa para destruir?" << ( (buff[12] == "1")  ? "si" : "no" )<< std::endl;
		break;
		}
	case TIPOSORPRESANIEVEMASPOTENTE:{
		// TODO: implementar pelota nieve.
		SorpresaNieveMasPotente * sorpresa = new SorpresaNieveMasPotente;
		objeto = sorpresa;
		indice = 3;
		std::cout << "sorpresa para destruir?" << ( (buff[12] == "1")  ? "si" : "no" )<< std::endl;
		break;
		}
	}

	objeto->orientacion = (orientacion_t) atoi(buff[1].c_str());
	objeto->rotacion = (float) atof(buff[2].c_str());

	objeto->espacioOcupado = new FiguraGeometrica();
	objeto->espacioOcupado->puntosOrdenados.clear();

	// Lee el numero de lados.
	int numeroLados = atoi(buff[indice].c_str());

	// Carga uno por uno los puntos de la figura.
	for(int i = 1; i < numeroLados * 2; i += 2){
		Vector2D punto;
		punto.x = (float) atof(buff[indice + i].c_str());
		punto.y = (float) atof(buff[indice + i + 1].c_str());
		objeto->espacioOcupado->puntosOrdenados.push_back(punto);
	}

	objeto->paraDestruir = (buff[indice + numeroLados * 2 + 1] == "1");

	objeto->ID = buff[indice + numeroLados * 2 + 2];

	return objeto;
}


// Inicializa al objeto.
void ObjetoModelo::inicializar(){

}

// Elimina lo que sea necesario.
void ObjetoModelo::limpiar(){
	delete espacioOcupado;
}

// Actualiza la informacion del objeto para poder dibujarlo.
void ObjetoModelo::actualizar(){

}

// Dibuja el objeto en pantalla.
void ObjetoModelo::dibujar(Camara * camara){

	// Checkea que el objeto sea visible.
	if (!camara->esVisible(this)) return;

	FiguraGeometrica * figuraEnCoordenadasCamara = espacioOcupado->cambiarDeCoordenadas(camara->obtenerOrigen());

	Vector2D origen; origen.x = 0; origen.y = 0;
	figuraEnCoordenadasCamara->escalar(origen, camara->obtenerEscala());

	// Obtiene la textura correspondiente al objeto.
	Textura * tex = obtenerTextura();

	// Obtiene la region de la textura a utilizar
	FiguraGeometrica * sprite = obtenerSprite();

	// Dibuja el objeto.
	tex->dibujar(figuraEnCoordenadasCamara, sprite);

	delete figuraEnCoordenadasCamara;
	delete sprite;
}

// Aplica la modificacion indicada sobre el ObjetoModelo.
void ObjetoModelo::aplicar(ObjetoModelo * modificacion){

	orientacion = modificacion->orientacion;
	rotacion = modificacion->rotacion;

	espacioOcupado->puntosOrdenados.clear();
	for(std::list<Vector2D>::iterator it = modificacion->espacioOcupado->puntosOrdenados.begin();
			it != modificacion->espacioOcupado->puntosOrdenados.end(); it++){
		espacioOcupado->puntosOrdenados.push_back(*it);
	}

	espacioOcupado->rotar(rotacion);
	Vector2D y; y.x = 0; y.y = 1;
	if (orientacion == DERECHA) espacioOcupado->espejar(y, espacioOcupado->calcularBaricentro());
}

// Aplica una modificacion.
void ObjetoModelo::aplicarModificacion(ControladorJuego * juego){
	juego->aplicar(this);
}

