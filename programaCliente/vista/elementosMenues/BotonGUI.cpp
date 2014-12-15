/*
 * BotonGUI.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "BotonGUI.h"

// Crea un boton.
BotonGUI::BotonGUI(){
	tieneFoco = false;
	clickeado = false;
	texto = NULL;
}

// Destruye el boton.
BotonGUI::~BotonGUI(){
	if(texto) delete texto;
}

// Especifica el texto a ser mostrado en el boton.
void BotonGUI::asignarTexto(std::string t){
	if(!texto) {
		texto = new TextoGUI;
		texto->asignarPosicion(rectanguloADibujar.x, rectanguloADibujar.y);
		texto->asignarDimensiones(rectanguloADibujar.w, rectanguloADibujar.h);
		texto->inicializar();
	}
	while (texto->tamanio() != 0) texto->remover(0);
	texto->agregarEnPosicion(t, texto->tamanio());
}

// Maneja el evento dado.
void BotonGUI::manejarEvento(SDL_Event evento){
	switch(evento.type){
	case SDL_MOUSEBUTTONDOWN:

		// Analiza si se clickeo el boton.
		SDL_Point posicionClick = {evento.button.x, evento.button.y};
		if (estaSiendoClickeado(posicionClick)) tieneFoco = true;
		else tieneFoco = false;
		break;
	}

	// Si se clickeo en el boton, notifica que ya se eligio nombre de usuario.
	if (tieneFoco) {
		clickeado = true;
		LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(BOTONCLICKEADO);
	}
}

// Dibuja el elemento en pantalla.
void BotonGUI::dibujar(){

	// Obtiene la textura correspondiente al boton.
	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(BOTON1);

	FiguraGeometrica * sprite = forma->normalizar();
	tex->dibujar(forma, sprite);

	delete sprite;

	// Dibuja el texto del boton, si lo hay.
	if (texto) texto->dibujar();
}

// Devuelve el estado del boton.
bool BotonGUI::estaClickeado(){
	return clickeado;
}

// Resetea el boton.
void BotonGUI::declickear(){
	clickeado = false;
	tieneFoco = false;
}
