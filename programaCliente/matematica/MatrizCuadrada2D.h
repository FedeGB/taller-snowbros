/*
 * MatrizCuadrada2D.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef MATRIZCUADRADA2D_H_
#define MATRIZCUADRADA2D_H_

#include <math.h>

class Vector2D;

class MatrizCuadrada2D {
public:
	MatrizCuadrada2D();
	virtual ~MatrizCuadrada2D();

	//Igualdad
	void operator=(const MatrizCuadrada2D&);

	// Suma matricial.
	MatrizCuadrada2D operator+(const MatrizCuadrada2D&);

	// Diferencia matricial.
	MatrizCuadrada2D operator-(const MatrizCuadrada2D&);

	// Producto matricial.
	MatrizCuadrada2D operator*(const MatrizCuadrada2D&);

	// Producto con vector.
	Vector2D operator*(const Vector2D&);

	// Producto por escalar.
	MatrizCuadrada2D operator*(const float&);

	// Genera una matriz que representa la rotacion en 'rotacion' radianes
	// respecto al origen.
	static MatrizCuadrada2D generarMatrizDeRotacion(float rotacion);

	// Genera una matriz que representa la reflexion sobre la recta de direccion
	// 'direccion' que pasa por el origen.
	static MatrizCuadrada2D generarMatrizDeReflexion(Vector2D direccion);

	// Genera una matriz que representa la escala en X e Y por los factores escalaX
	// y escalaY respectivamente, respecto al origen.
	static MatrizCuadrada2D generarMatrizDeEscala(float escalaX, float escalaY);

	float matriz[2][2]; // [row]x[col]
};

#endif /* MATRIZCUADRADA2D_H_ */
