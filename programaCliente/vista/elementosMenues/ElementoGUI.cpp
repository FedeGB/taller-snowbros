/*
 * ElementoGUI.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "ElementoGUI.h"

// Destruye el elemento de la GUI.
ElementoGUI::~ElementoGUI(){
	delete forma;
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ElementoGUI::notificar(tipo_notificacion_t notificacion){

}

// Asigna una posicion en pantalla al elemento. Las coordenadas dadas son
// en la escala de pantalla.
void ElementoGUI::asignarPosicion(int x, int y){
	rectanguloADibujar.x = x;
	rectanguloADibujar.y = y;
}

// Asigna dimensiones del elemento. Las coordenadas dadas son en la escala
// de pantalla.
void ElementoGUI::asignarDimensiones(int ancho, int alto){
	rectanguloADibujar.w = ancho;
	rectanguloADibujar.h = alto;
}

// Una vez asignadas la posicion y dimensiones, se debe llamar a este metodo,
// encargado de inicializar el objeto a un estado valido para ser utilizado.
void ElementoGUI::inicializar(){

	forma = FiguraGeometrica::generarRectangulo(rectanguloADibujar.x, rectanguloADibujar.y,
			rectanguloADibujar.w, rectanguloADibujar.h, 0);
}

// Checkea si el elemento actual esta siendo clickeado.
// 'posicionMouse' es la representacion en coordenadas de la ventana de la posicion
// donde se clickeo.
// Devuelve true si la posicion del click cae dentro del area del elemento, false
// en caso contrario.
bool ElementoGUI::estaSiendoClickeado(SDL_Point posicionMouse){
	return ((posicionMouse.x >= rectanguloADibujar.x) && (posicionMouse.x < (rectanguloADibujar.x + rectanguloADibujar.w)) &&
			(posicionMouse.y >= rectanguloADibujar.y) && (posicionMouse.y < (rectanguloADibujar.y + rectanguloADibujar.h)));
}
