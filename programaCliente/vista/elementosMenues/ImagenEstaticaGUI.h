/*
 * ImagenEstaticaGUI.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef IMAGENESTATICAGUI_H_
#define IMAGENESTATICAGUI_H_

#include "ElementoGUI.h"

class ImagenEstaticaGUI: public ElementoGUI {
public:

	// Crea una imagen estatica.
	ImagenEstaticaGUI();

	// Destruye la imagen estatica.
	virtual ~ImagenEstaticaGUI();

	// Maneja el evento dado.
	virtual void manejarEvento(SDL_Event evento);

	// Dibuja el elemento en pantalla.
	virtual void dibujar();

};

#endif /* IMAGENESTATICAGUI_H_ */
