/*
 * cajaDeTextoGUI.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef CAJADETEXTOGUI_H_
#define CAJADETEXTOGUI_H_

#include "ElementoGUI.h"
#include "TextoGUI.h"

class CajaDeTextoGUI: public ElementoGUI {
public:

	// Crea una caja de texto.
	CajaDeTextoGUI();

	// Destruye la caja de texto.
	virtual ~CajaDeTextoGUI();

	// Una vez asignadas la posicion y dimensiones, se debe llamar a este metodo,
	// encargado de inicializar el objeto a un estado valido para ser utilizado.
	virtual void inicializar();

	// Maneja el evento dado.
	virtual void manejarEvento(SDL_Event evento);

	// Dibuja el elemento en pantalla.
	virtual void dibujar();

	// Devuelve lo que esta escrito en la caja de texto.
	std::string obtenerContenido();

	// Devuelve el estado de la caja de texto.
	bool estaLlena();

	// Resetea la caja de texto.
	void vaciar();

protected:

	// Elemento que representa lo escrito por el usuario en la caja de texto.
	TextoGUI * texto;
	bool llena;
};

#endif /* CAJADETEXTOGUI_H_ */
