/*
 * BotonGUI.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef BOTONGUI_H_
#define BOTONGUI_H_

#include "ElementoGUI.h"
#include "TextoGUI.h"

class BotonGUI: public ElementoGUI {
public:

	// Crea un boton.
	BotonGUI();

	// Destruye el boton.
	virtual ~BotonGUI();

	// Especifica el texto a ser mostrado en el boton.
	void asignarTexto(std::string t);

	// Maneja el evento dado.
	virtual void manejarEvento(SDL_Event evento);

	// Dibuja el elemento en pantalla.
	virtual void dibujar();

	// Devuelve el estado del boton.
	bool estaClickeado();

	// Resetea el boton.
	void declickear();

protected:

	// Elemento que representa el mensaje a mostrar en el boton.
	TextoGUI * texto;

	// Indica si el boton esta actualmente clickeado.
	bool clickeado;

};

#endif /* BOTONGUI_H_ */
