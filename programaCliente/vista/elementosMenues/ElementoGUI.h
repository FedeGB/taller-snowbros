/*
 * ElementoGUI.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef ELEMENTOGUI_H_
#define ELEMENTOGUI_H_

#include <SDL2/SDL.h>
#include "../../servicios/LocalizadorDeServicios.h"
#include "../../interfaces/Posicionable.h"
#include "../../matematica/FiguraGeometrica.h"

class ElementoGUI: public Posicionable {
public:

	// Destruye el elemento de la GUI.
	virtual ~ElementoGUI();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Asigna una posicion en pantalla al elemento. Las coordenadas dadas son
	// en la escala de pantalla.
	virtual void asignarPosicion(int x, int y);

	// Asigna dimensiones del elemento. Las coordenadas dadas son en la escala
	// de pantalla.
	virtual void asignarDimensiones(int ancho, int alto);

	// Una vez asignadas la posicion y dimensiones, se debe llamar a este metodo,
	// encargado de inicializar el objeto a un estado valido para ser utilizado.
	virtual void inicializar();

	// Maneja el evento dado.
	virtual void manejarEvento(SDL_Event evento) = 0;

	// Dibuja el elemento en pantalla.
	virtual void dibujar() = 0;
protected:

	SDL_Rect rectanguloADibujar;
	FiguraGeometrica * forma;
	bool tieneFoco;

	// Checkea si el elemento actual esta siendo clickeado.
	// 'posicionMouse' es la representacion en coordenadas de la ventana de la posicion
	// donde se clickeo.
	// Devuelve true si la posicion del click cae dentro del area del elemento, false
	// en caso contrario.
	bool estaSiendoClickeado(SDL_Point posicionMouse);

};

#endif /* ELEMENTOGUI_H_ */
