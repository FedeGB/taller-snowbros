/*
 * TextoGUI.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef TEXTOGUI_H_
#define TEXTOGUI_H_

#include "ElementoGUI.h"

class TextoGUI: public ElementoGUI {
public:

	// Crea un texto.
	TextoGUI();

	// Destruye el texto.
	virtual ~TextoGUI();

	// Maneja el evento dado.
	virtual void manejarEvento(SDL_Event evento);

	// Dibuja el elemento en pantalla.
	virtual void dibujar();

	// Asigna el estilo de texto deseado.
	void asignarEstilo(estilo_texto_t e);

	// Metodos para manejo del texto a renderear.
	int tamanio();
	std::string obtenerTexto();
	void reemplazarTexto(std::string nuevoTexto);
	void agregarEnPosicion(std::string agregado, int posicion);
	void remover(int posicion);

protected:

	// Buffer que almacena lo que se escribio en el elemento.
	std::string texto;
	estilo_texto_t estilo;
};

#endif /* TEXTOGUI_H_ */
