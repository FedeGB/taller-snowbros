/*
 * Ladrillo.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "Ladrillo.h"

Ladrillo::Ladrillo() {
	// TODO Auto-generated constructor stub
	reconocerDestruccion = 0;
}

// Levanta el personaje desde el archivo de configuracion Json.
Ladrillo::Ladrillo(std::string sConfig, int numeroObjeto){

	reconocerDestruccion = 0;
	rotacion = get_node("rot", "objetos", sConfig, numeroObjeto, 0.0f) * DEGTORAD;

	espacioOcupado = new FiguraGeometrica();
	Vector2D punto;

	if (get_node("tipo", "objetos", sConfig, numeroObjeto, "rect") == "rect"){

		// Obtiene el espacio ocupado por el ladrillo.
		float x = get_node("x", "objetos", sConfig, numeroObjeto, 20.0f);
		float y = get_node("y", "objetos", sConfig, numeroObjeto, 20.0f);
		float ancho = get_node("ancho", "objetos", sConfig, numeroObjeto, 20.0f);
		float alto = get_node("alto", "objetos", sConfig, numeroObjeto, 20.0f);

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

	if (get_node("tipo", "objetos", sConfig, numeroObjeto, "rect") == "poli"){

		// Obtiene el espacio ocupado por el ladrillo.
		float x = get_node("x", "objetos", sConfig, numeroObjeto, 20.0f);
		float y = get_node("y", "objetos", sConfig, numeroObjeto, 20.0f);
		float lados = get_node("lados", "objetos", sConfig, numeroObjeto, 20.0f);
		float escala = get_node("escala", "objetos", sConfig, numeroObjeto, 20.0f);

		// Calcula la posicion de los puntos, centrados en el origen.
		for (int i = 0; i < lados; i++) {
			float angulo = (2 * i * PI / lados);
			punto.x = escala * cos(angulo);
			punto.y = escala * sin(angulo);
			espacioOcupado->puntosOrdenados.push_back(punto);
		}

		// Desplaza el objeto a su posicion.
		punto.x = x;
		punto.y = y;
		espacioOcupado->trasladar(punto);
	}

	if (get_node("tipo", "objetos", sConfig, numeroObjeto, "rect") == "irreg"){

		// Obtiene el espacio ocupado por el ladrillo.
		float base = get_node("base", "objetos", sConfig, numeroObjeto, 1.0f);
		float tapa = get_node("tapa", "objetos", sConfig, numeroObjeto, 1.0f);
		float alto = get_node("alto", "objetos", sConfig, numeroObjeto, 1.0f);
		float desp = get_node("desp", "objetos", sConfig, numeroObjeto, 1.0f);

		float32 centroX = ((2 * tapa * desp + base * desp + base * tapa
				+ pow(base, 2) + pow(tapa, 2)) / (3 * (base + tapa)));
		float32 centroY = ((alto * (base + 2 * tapa)) / (3 * (base + tapa)));
		punto.x = -centroX; punto.y = centroY;
		espacioOcupado->puntosOrdenados.push_back(punto);
		punto.x = -centroX + base; punto.y = centroY;
		espacioOcupado->puntosOrdenados.push_back(punto);
		punto.x = -centroX + desp; punto.y = centroY - alto;
		espacioOcupado->puntosOrdenados.push_back(punto);
		punto.x = -centroX + desp + tapa; punto.y = centroY - alto;
		espacioOcupado->puntosOrdenados.push_back(punto);
	}

}

Ladrillo::~Ladrillo() {
	// TODO Auto-generated destructor stub
}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string Ladrillo::serializar(){

	std::string buff;

	buff = SSTR(TIPOLADRILLO << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}
