/*
 * PelotaDeNieve.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#include "PelotaDeNieve.h"
#include "Personaje.h"
#include "../../../servicios/ServicioFabricaDeObjetos.h"

PelotaDeNieve::PelotaDeNieve() {
	// TODO Auto-generated constructor stub
	reconocerDestruccion = 0;
	acumuladorParaDestruccion = 300;
	acumuladorCaida = 40;
	cayoPorAgujero = false;
	tiroSorpresa = false;
}

// Levanta el personaje desde el archivo de configuracion Json.
PelotaDeNieve::PelotaDeNieve(std::string sConfig, int numeroObjeto){

	reconocerDestruccion = 0;
	acumuladorParaDestruccion = 300;
	tiroSorpresa = false;

	// Obtiene la rotacion del objeto.
	rotacion = get_node("rot", "objetos", sConfig, numeroObjeto, 0.0f) * DEGTORAD;

	// Obtiene el espacio ocupado por el ladrillo.
	float x = get_node("x", "objetos", sConfig, numeroObjeto, 20.0f);
	float y = get_node("y", "objetos", sConfig, numeroObjeto, 20.0f);
	float escala = get_node("escala", "objetos", sConfig, numeroObjeto, 20.0f);
	float ancho, alto; ancho = alto = escala * 2;

	// Carga los puntos del ladrillo.
	espacioOcupado = new FiguraGeometrica();
	Vector2D punto;
	// Carga los puntos del ladrillo.
	punto.x = x - ancho / 2; punto.y = y - alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x + ancho / 2; punto.y = y - alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x + ancho / 2; punto.y = y + alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x - ancho / 2; punto.y = y + alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

}

PelotaDeNieve::~PelotaDeNieve() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string PelotaDeNieve::serializar(){

	std::string buff;

	buff = SSTR(TIPOPELOTADENIEVE << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}

// Agrega un personaje a la lista de personajes atrapados.
void PelotaDeNieve::atraparPersonaje(Personaje * pj){
	if (pj->acabaDePatear) return;
	atrapados.push_back(pj);
}

// Actualiza la informacion del objeto para poder dibujarlo.
void PelotaDeNieve::actualizar(){

	// Actualiza la posicion y rotacion.
	ObjetoModelo::actualizar();

	acumuladorParaDestruccion--;
	if (acumuladorParaDestruccion <= 0) {
		paraDestruir = true;
		b2Vec2 aux = cuerpoB2D->GetPosition();

		for (list<Personaje*>::iterator it = atrapados.begin(); it != atrapados.end(); it++){
			(*it)->cuerpoB2D->SetTransform(aux,0);
			(*it)->liberarDePelota();
		}

		// Determina si la pelota al destruirse deja una sorpresa, con probabilidad 35%.
		bool tiraSorpresa = (rand() % 100) < 35;
		if (tiraSorpresa && !tiroSorpresa) LocalizadorDeServicios::obtenerFabricaDeObjetos()->fabricarSorpresa(this);
		else tiroSorpresa = true;
	}

}
