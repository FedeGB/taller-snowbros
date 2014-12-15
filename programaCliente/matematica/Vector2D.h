/*
 * Vector2D.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

class MatrizCuadrada2D;

const float PI = 3.14159265359;

class Vector2D {
public:
	Vector2D();
	virtual ~Vector2D();

	//Igualdad
	void operator=(const Vector2D&);

	// Suma vectorial.
	Vector2D operator+(const Vector2D&);

	// Diferencia vectorial.
	Vector2D operator-(const Vector2D&);

	// Producto escalar.
	float operator*(const Vector2D&);

	// Producto con matriz.
	Vector2D operator*(const MatrizCuadrada2D&);

	// Producto por escalar.
	Vector2D operator*(const float&);

	// Modulo cuadrado del vector.
	float moduloCuadrado();

	// Angulo respecto a otro vector.
	float angulo(Vector2D otro);

	float x, y;
};

#endif /* VECTOR2D_H_ */
