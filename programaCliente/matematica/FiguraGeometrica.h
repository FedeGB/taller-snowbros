/*
 * FiguraGeometrica.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef FIGURAGEOMETRICA_H_
#define FIGURAGEOMETRICA_H_

#include <list>
#include <stdlib.h>
#include "MatrizCuadrada2D.h"
#include "Vector2D.h"

class FiguraGeometrica {
public:
	FiguraGeometrica();
	virtual ~FiguraGeometrica();

	// Agrega un punto a la figura.
	void agregarPunto(Vector2D punto);

	// Devuelve la cantidad de vertices de la figura.
	int numeroVertices();

	// Rota la figura alrededor del punto de pivot, en la cantidad indicada por
	// 'rotacion'.
	void rotar(Vector2D pivot, float rotacion);

	// Rota la figura alrededor del centro de masa, en la cantidad indicada por
	// 'rotacion'.
	void rotar(float rotacion);

	// Calcula el baricentro de la figura.
	Vector2D calcularBaricentro();

	// Refleja la figura sobre la recta en direccion 'direccion' que pasa por
	// el punto 'pivot'.
	void espejar(Vector2D direccion, Vector2D pivot);

	// Translada la figura segun el vector de traslacion dado.
	void trasladar(Vector2D traslacion);

	// Escala la figura en un factor 'escalaX' sobre el eje X, y en un factor 'escalaY'
	// sobre el eje Y, con respecto al punto 'pivot'.
	void escalar(Vector2D pivot, float escalaX, float escalaY);

	// Escala la figura uniformemente en un factor 'escala', con respecto al punto 'pivot'.
	void escalar(Vector2D pivot, float escala);

	// Devuelve una copia de la figura transladada al sistema de coordenadas deseado.
	// 'origen' contiene las coordenadas del nuevo eje de coordenadas en el anterior
	// sistema de referencia.
	FiguraGeometrica * cambiarDeCoordenadas(Vector2D origen);

	// Analiza si el punto dado pertenece al interior de la figura.
	bool pertenece(Vector2D punto);

	// Devuelve una copia de la figura escalada hasta que quepa en el cuadrado unidad.
	FiguraGeometrica * normalizar();

	// Por comodidad, ya que los rectangulos son las figuras geometricas mas utilizadas,
	// este metodo genera un rectangulo con los parametros de posicion y dimensiones
	// dados.
	static FiguraGeometrica * generarRectangulo(float x, float y, float w, float h, float rotacion);

	// Igualdad.
	void operator=(const FiguraGeometrica& f);

	std::list<Vector2D> puntosOrdenados;
};

#endif /* FIGURAGEOMETRICA_H_ */
