/*
 * MatrizCuadrada2D.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "MatrizCuadrada2D.h"
#include "Vector2D.h"

#include <iostream>

MatrizCuadrada2D::MatrizCuadrada2D() {

}

MatrizCuadrada2D::~MatrizCuadrada2D() {

}

//Igualdad
void MatrizCuadrada2D::operator=(const MatrizCuadrada2D& m){

	matriz[0][0] = m.matriz[0][0];
	matriz[1][0] = m.matriz[1][0];
	matriz[0][1] = m.matriz[0][1];
	matriz[1][1] = m.matriz[1][1];
}

// Suma matricial.
MatrizCuadrada2D MatrizCuadrada2D::operator+(const MatrizCuadrada2D& m){

	MatrizCuadrada2D temp;
	temp.matriz[0][0] = matriz[0][0] + m.matriz[0][0];
	temp.matriz[1][0] = matriz[0][0] + m.matriz[1][0];
	temp.matriz[0][1] = matriz[0][0] + m.matriz[0][1];
	temp.matriz[1][1] = matriz[0][0] + m.matriz[1][1];

	return temp;
}

// Diferencia matricial.
MatrizCuadrada2D MatrizCuadrada2D::operator-(const MatrizCuadrada2D& m){

	MatrizCuadrada2D temp;
	temp.matriz[0][0] = matriz[0][0] - m.matriz[0][0];
	temp.matriz[1][0] = matriz[0][0] - m.matriz[1][0];
	temp.matriz[0][1] = matriz[0][0] - m.matriz[0][1];
	temp.matriz[1][1] = matriz[0][0] - m.matriz[1][1];

	return temp;
}

// Producto matricial.
MatrizCuadrada2D MatrizCuadrada2D::operator*(const MatrizCuadrada2D& m){

	MatrizCuadrada2D temp;
	temp.matriz[0][0] = matriz[0][0] * m.matriz[0][0] + matriz[1][0] * m.matriz[0][1];
	temp.matriz[1][0] = matriz[0][0] * m.matriz[1][0] + matriz[1][0] * m.matriz[1][1];
	temp.matriz[0][1] = matriz[0][1] * m.matriz[0][0] + matriz[1][1] * m.matriz[0][1];
	temp.matriz[1][1] = matriz[0][1] * m.matriz[1][0] + matriz[1][1] * m.matriz[1][1];

	return temp;
}

// Producto con vector.
Vector2D MatrizCuadrada2D::operator*(const Vector2D& v){

	Vector2D temp;
	temp.x = matriz[0][0] * v.x + matriz[1][0] * v.y;
	temp.y = matriz[0][1] * v.x + matriz[1][1] * v.y;

	return temp;
}

// Producto por escalar.
MatrizCuadrada2D MatrizCuadrada2D::operator*(const float& f){

	MatrizCuadrada2D temp;
	temp.matriz[0][0] = matriz[0][0] * f;
	temp.matriz[1][0] = matriz[0][0] * f;
	temp.matriz[0][1] = matriz[0][0] * f;
	temp.matriz[1][1] = matriz[0][0] * f;

	return temp;
}

// Genera la matriz correspondiente a una rotacion de
// 'rotacion' grados.
MatrizCuadrada2D MatrizCuadrada2D::generarMatrizDeRotacion(float rotacion){

	MatrizCuadrada2D matriz;
	matriz.matriz[0][0] = cos(rotacion);
	matriz.matriz[1][0] = sin(rotacion);
	matriz.matriz[0][1] = -sin(rotacion);
	matriz.matriz[1][1] = cos(rotacion);

	return matriz;
}

// Genera una matriz que representa la reflexion sobre la recta de direccion
// 'direccion' que pasa por el origen.
MatrizCuadrada2D MatrizCuadrada2D::generarMatrizDeReflexion(Vector2D direccion){

	MatrizCuadrada2D matriz;
	float moduloCuadrado = direccion.moduloCuadrado();

	matriz.matriz[0][0] = ( pow(direccion.x,2) - pow(direccion.y,2) ) * (1 / moduloCuadrado);
	matriz.matriz[1][0] = ( 2 *  direccion.x * direccion.y ) * (1 / moduloCuadrado);
	matriz.matriz[0][1] = ( 2 *  direccion.x * direccion.y ) * (1 / moduloCuadrado);
	matriz.matriz[1][1] = ( pow(direccion.y,2) - pow(direccion.x,2) ) * (1 / moduloCuadrado);

	return matriz;
}

// Genera una matriz que representa la escala en X e Y por los factores escalaX
// y escalaY respectivamente, respecto al origen.
MatrizCuadrada2D MatrizCuadrada2D::generarMatrizDeEscala(float escalaX, float escalaY){

	MatrizCuadrada2D matriz;

	matriz.matriz[0][0] = escalaX;
	matriz.matriz[1][0] = 0;
	matriz.matriz[0][1] = 0;
	matriz.matriz[1][1] = escalaY;

	return matriz;
}
