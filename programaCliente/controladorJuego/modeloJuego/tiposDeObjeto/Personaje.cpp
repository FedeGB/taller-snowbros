/*
 * Personaje.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "Personaje.h"
#include "../Camara.h"

// Representacion de un personaje controlado por el usuario.
Personaje::Personaje(){
	orientacion = IZQUIERDA;
	estado = PARADO;
	inicializado = false;
	inmune = true;
	murio = false;
	acumuladorCaminando = 0;
	acumuladorSaltando = 0;
	acumuladorAtacando = 0;
	acumuladorAtrapado = 0;
	acumuladorInmunidad = 0;
	acumuladorMuerte = 0;
}

Personaje::~Personaje(){

}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string Personaje::serializar(){

	std::string buff;

	buff = SSTR(TIPOPERSONAJE << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << nombre << SEPARADORDATOS << estado << espacioOcupado->numeroVertices() << paraDestruir);

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	return buff;
}

// Inicializa al objeto.
void Personaje::inicializar(){

	LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(PERSONAJECREADO,this);
	inicializado = true;
}

// Elimina lo que sea necesario.
void Personaje::limpiar(){

	if (!inicializado) return;
	LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(PERSONAJEDESTRUIDO,this);
}

// Aplica la modificacion indicada sobre el SerVivo.
void Personaje::aplicar(Personaje * modificacion){

	SerVivo::aplicar((SerVivo*)modificacion);
	nombre = modificacion->nombre;
	inmune = modificacion->inmune;
	murio = modificacion->murio;
}


// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
void Personaje::aplicarSobre(ObjetoModelo * objeto){
	objeto->aplicar(this);
}


// Obtiene la textura que representa al objeto.
Textura * Personaje::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(PJ);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * Personaje::obtenerSprite(){

	SonidosMap * sonidos = LocalizadorDeServicios::obtenerSonidos();
	FiguraGeometrica * sprite;
	int x, y = 37, w = 21, h = 29;

	if (murio){
		/*if (acumuladorMuerte == 0){
			(*LocalizadorDeServicios::obtenerSonidos())[SONIDOMUERTE]->reproducir();
			(*LocalizadorDeServicios::obtenerSonidos())[MUSICA_DE_FONDO]->detener();
		}*/
		acumuladorMuerte++;
		switch ((acumuladorMuerte / 15) % 3){
		case 0:
			x = 126; y = 100; w = 28; h = 33;
			break;
		case 1:
			x = 158; y = 100; w = 28; h = 33;
			break;
		case 2:
			x = 190; y = 100; w = 28; h = 33;
			break;
		};
	} else{
		acumuladorMuerte = 0;

		switch (estado){
		case PARADO:
			acumuladorSaltando = 0;
			acumuladorAtacando = 0;
			acumuladorCaminando = 0;
			acumuladorAtrapado = 0;
			x = 23;
			break;
		case CAMINANDO:
			acumuladorSaltando = 0;
			acumuladorAtacando = 0;
			acumuladorAtrapado = 0;
			switch( (acumuladorCaminando / 15) % 4 ){
			case 0:
				x = 45;
				break;
			case 1:
				x = 89;
				break;
			case 2:
				x = 45;
				break;
			case 3:
				x = 68;
				break;
			}
			acumuladorCaminando++;
			break;
		case SALTANDO:
			acumuladorCaminando = 0;
			acumuladorAtacando = 0;
			acumuladorAtrapado = 0;
			if (acumuladorSaltando == 0) (*sonidos)[SALTO]->reproducir();
			switch( (acumuladorSaltando / 15) ){
			case 0:
				x = 202;
				break;
			case 1:
				x = 137;
				break;
			case 2:
				x = 159;
				break;
			case 3:
				x = 181;
				break;
			default:
				x = 116;
				break;
			}
			acumuladorSaltando++;
			break;

		case ATACANDO:
			acumuladorCaminando = 0;
			acumuladorSaltando = 0;
			acumuladorAtrapado = 0;
			y = 68;
			if (acumuladorAtacando % 45 == 44) (*sonidos)[DISPARO]->reproducir();
			switch( (acumuladorAtacando / 15) % 3 ){
			case 0:
				x = 27;
				break;
			case 1:
				x = 68; y = 37;
				break;
			case 2:
				x = 0;
				break;
			}
			acumuladorAtacando++;
			break;
		case ATRAPADO:
			acumuladorCaminando = 0;
			acumuladorSaltando = 0;
			acumuladorAtacando = 0;
			x = 1; y = 1;
		}

	}

	sprite = FiguraGeometrica::generarRectangulo(x / 444.0f, y / 133.0f, w / 444.0f, h / 133.0f, 0);

	return sprite;
}

// Dibuja la animacion de inmunidad del PJ.
void Personaje::dibujarInmunidad(Camara * camara){

	FiguraGeometrica * figuraEnCoordenadasCamara = espacioOcupado->cambiarDeCoordenadas(camara->obtenerOrigen());

	// Escala para que la inmunidad sea un poco mas grande que el enemigo.
	figuraEnCoordenadasCamara->escalar(figuraEnCoordenadasCamara->calcularBaricentro(), 1.2);

	// Escala al sistema de coordenadas de la pantalla.
	Vector2D origen; origen.x = 0; origen.y = 0;
	figuraEnCoordenadasCamara->escalar(origen, camara->obtenerEscala());

	// Obtiene la textura correspondiente al objeto.
	Textura * tex;
	tex = LocalizadorDeServicios::obtenerControladorDeTexturas()->obtenerTextura(INMUNIDAD);

	// Obtiene la region de la textura a utilizar
	FiguraGeometrica * sprite;
	acumuladorInmunidad++;
	switch ( (acumuladorInmunidad / 15) % 4){
	case 0:
		sprite = FiguraGeometrica::generarRectangulo(150/491.0f, 3/280.0f, 46/491.0f, 46/280.0f, 0);
		break;
	case 1:
		sprite = FiguraGeometrica::generarRectangulo(150/491.0f, 52/280.0f, 46/491.0f, 46/280.0f, 0);
		break;
	case 2:
		sprite = FiguraGeometrica::generarRectangulo(199/491.0f, 101/280.0f, 46/491.0f, 46/280.0f, 0);
		break;
	case 3:
		sprite = FiguraGeometrica::generarRectangulo(52/491.0f, 150/280.0f, 46/491.0f, 46/280.0f, 0);
		break;
	}

	// Dibuja el objeto.
	tex->dibujar(figuraEnCoordenadasCamara, sprite);

	delete figuraEnCoordenadasCamara;
	delete sprite;
}

// Dibuja el objeto en pantalla.
void Personaje::dibujar(Camara * camara){

	// Checkea que el objeto sea visible.
	if (!camara->esVisible(this)) return;

	// Dibuja al enemigo.
	ObjetoModelo::dibujar(camara);

	// Dibuja la animacion de inmunidad, si es que es inmune.
	if (inmune) dibujarInmunidad(camara);
	else {
/*		if (!murio && !(*LocalizadorDeServicios::obtenerSonidos())[MUSICA_DE_FONDO]->estaSonando())
			(*LocalizadorDeServicios::obtenerSonidos())[MUSICA_DE_FONDO]->reproducir();
*/		acumuladorInmunidad = 0;
	}
}
