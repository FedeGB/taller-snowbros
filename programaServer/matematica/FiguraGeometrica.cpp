/*
 * FiguraGeometrica.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "FiguraGeometrica.h"

#include <iostream>

FiguraGeometrica::FiguraGeometrica() {
	// TODO Auto-generated constructor stub

}

FiguraGeometrica::~FiguraGeometrica() {
	// TODO Auto-generated destructor stub
}

// Agrega un punto a la figura.
void FiguraGeometrica::agregarPunto(Vector2D punto){
	puntosOrdenados.push_back(punto);
}

// Devuelve la cantidad de vertices de la figura.
int FiguraGeometrica::numeroVertices(){
	return puntosOrdenados.size();
}

// Rota la figura alrededor del punto de pivot, en la cantidad indicada por
// 'rotacion'.
void FiguraGeometrica::rotar(Vector2D pivot, float rotacion){

	MatrizCuadrada2D matrizRotacion = MatrizCuadrada2D::generarMatrizDeRotacion(rotacion);

	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		(*it) = ((*it) - pivot) * matrizRotacion + pivot;
	}
}

// Rota la figura alrededor del centro de masa, en la cantidad indicada por
// 'rotacion'.
void FiguraGeometrica::rotar(float rotacion){

	Vector2D pivot = calcularBaricentro();
	rotar(pivot, rotacion);
}

// Calcula el baricentro de la figura.
Vector2D FiguraGeometrica::calcularBaricentro(){

	Vector2D pivot;

	float acumuladorX = 0.0f, acumuladorY = 0.0f;

	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		acumuladorX += (*it).x;
		acumuladorY += (*it).y;
	}

	pivot.x = acumuladorX / puntosOrdenados.size();
	pivot.y = acumuladorY / puntosOrdenados.size();

	return pivot;
}

// Refleja la figura sobre la recta en direccion 'direccion' que pasa por
// el punto 'pivot'.
void FiguraGeometrica::espejar(Vector2D direccion, Vector2D pivot){

	MatrizCuadrada2D matrizReflexion = MatrizCuadrada2D::generarMatrizDeReflexion(direccion);

	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		(*it) = ((*it) - pivot) * matrizReflexion + pivot;
	}
}

// Translada la figura segun el vector de traslacion dado.
void FiguraGeometrica::trasladar(Vector2D traslacion){

	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		(*it) = (*it) + traslacion;
	}
}

// Escala la figura en un factor 'escalaX' sobre el eje X, y en un factor 'escalaY'
// sobre el eje Y.
void FiguraGeometrica::escalar(Vector2D pivot, float escalaX, float escalaY){

	MatrizCuadrada2D matrizEscala = MatrizCuadrada2D::generarMatrizDeEscala(escalaX, escalaY);

	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		(*it) = ((*it) - pivot) * matrizEscala + pivot;
	}
}

// Escala la figura uniformemente en un factor 'escala'.
void FiguraGeometrica::escalar(Vector2D pivot, float escala){
	escalar(pivot, escala,escala);
}

// Devuelve una copia de la figura transladada al sistema de coordenadas deseado.
// 'origen' contiene las coordenadas del nuevo eje de coordenadas en el anterior
// sistema de referencia.
FiguraGeometrica * FiguraGeometrica::cambiarDeCoordenadas(Vector2D origen){

	FiguraGeometrica * figura = new FiguraGeometrica();
	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		figura->agregarPunto( (*it) - origen );
	}

	return figura;
}

// Analiza si el punto dado pertenece al interior de la figura.
bool FiguraGeometrica::pertenece(Vector2D punto){

	Vector2D anterior, actual;

	float angulo = 0;

	std::list<Vector2D>::iterator it = puntosOrdenados.begin();
	anterior = *it;
	it++;

	// Recorre todos los pares de vertices, para analizar para cada
	// lado si la recta que pasa por el origen y el punto 'punto'
	// lo interseca.
	for(; it != puntosOrdenados.end(); it++){
		actual = *it;

		Vector2D resultado1 = actual - punto;
		Vector2D resultado2 = anterior - punto;
		angulo += resultado1.angulo(resultado2);

		anterior = actual;
	}

	actual = *(puntosOrdenados.begin());

	Vector2D resultado1 = actual - punto;
	Vector2D resultado2 = anterior - punto;
	angulo += resultado1.angulo(resultado2);

	if (abs(angulo) < PI) return false;
	return true;
}

// Devuelve una copia de la figura escalada hasta que quepa en el cuadrado unidad.
FiguraGeometrica * FiguraGeometrica::normalizar(){

	FiguraGeometrica * temp = new FiguraGeometrica;
	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		temp->puntosOrdenados.push_back(*it);
	}

	// Halla el minimo x e y.
	Vector2D min;
	min.x = 6000.0f, min.y = 6000.0f;
	Vector2D max;
	max.x = -6000.0f, max.y = -6000.0f;
	for(std::list<Vector2D>::iterator it = puntosOrdenados.begin(); it != puntosOrdenados.end(); it++){
		if ((*it).x < min.x) min.x = (*it).x;
		if ((*it).y < min.y) min.y = (*it).y;
		if ((*it).x > max.x) max.x = (*it).x;
		if ((*it).y > max.y) max.y = (*it).y;
	}

	// Traslada los minimos al origen de coordenadas, asegurando asi que la figura se
	// encuentra en el primer cuadrante.
	min.x = -min.x; min.y = -min.y;
	temp->trasladar(min);

	// Halla el maximo valor de X o Y.
	//float maximo = (max.x - min.x > max.y - min.y ? max.x - min.x : max.y - min.y);
	max.x = max.x + min.x;
	max.y = max.y + min.y;

	for(std::list<Vector2D>::iterator it = temp->puntosOrdenados.begin(); it != temp->puntosOrdenados.end(); it++){
		(*it).x = (*it).x * (1.0f/max.x);
		(*it).y = (*it).y * (1.0f/max.y);
	}

	return temp;
}

// Por comodidad, ya que los rectangulos son las figuras geometricas mas utilizadas,
// este metodo genera un rectangulo con los parametros de posicion y dimensiones
// dados.
FiguraGeometrica * FiguraGeometrica::generarRectangulo(float x, float y, float w, float h, float rotacion){

	FiguraGeometrica * figura = new FiguraGeometrica();

	Vector2D temp;
	temp.x = x; temp.y = y;
	figura->agregarPunto(temp);

	temp.x = x + w;	temp.y = y;
	figura->agregarPunto(temp);

	temp.x = x + w;	temp.y = y + h;
	figura->agregarPunto(temp);

	temp.x = x;	temp.y = y + h;
	figura->agregarPunto(temp);

	figura->rotar(rotacion);

	return figura;
}

// Igualdad.
void FiguraGeometrica::operator=(const FiguraGeometrica& f){
	puntosOrdenados = f.puntosOrdenados;
}
