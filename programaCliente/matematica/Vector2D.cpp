/*
 * Vector2D.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "Vector2D.h"
#include "MatrizCuadrada2D.h"

#include <iostream>

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::~Vector2D() {

}

//Igualdad
void Vector2D::operator=(const Vector2D& v){
	x = v.x;
	y = v.y;
}

// Suma vectorial.
Vector2D Vector2D::operator+(const Vector2D& v){

	Vector2D temp;
	temp.x = x + v.x;
	temp.y = y + v.y;

	return temp;
}

// Diferencia vectorial.
Vector2D Vector2D::operator-(const Vector2D& v){

	Vector2D temp;
	temp.x = x - v.x;
	temp.y = y - v.y;

	return temp;
}

// Producto escalar.
float Vector2D::operator*(const Vector2D& v){
	return (x * v.x + y * v.y);
}

// Producto con matriz.
Vector2D Vector2D::operator*(const MatrizCuadrada2D& m){

	Vector2D temp;
	temp.x = m.matriz[0][0] * x + m.matriz[0][1] * y;
	temp.y = m.matriz[1][0] * x + m.matriz[1][1] * y;

	return temp;
}

// Producto por escalar.
Vector2D Vector2D::operator*(const float& f){

	Vector2D temp;
	temp.x = x * f;
	temp.y = y * f;

	return temp;
}

// Modulo cuadrado del vector.
float Vector2D::moduloCuadrado(){
	return ( x * x + y * y);
}

// Angulo respecto a otro vector.
float Vector2D::angulo(Vector2D otro){

	double dtheta,theta1,theta2;

	theta1 = atan2(y,x);
	theta2 = atan2(otro.y,otro.x);
	dtheta = theta2 - theta1;
	while (dtheta > PI)
	  dtheta -= 2 * PI;
	while (dtheta < -PI)
	  dtheta += 2 * PI;

	return(dtheta);
}
