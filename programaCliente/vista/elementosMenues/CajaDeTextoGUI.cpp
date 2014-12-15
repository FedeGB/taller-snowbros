/*
 * CajaDeTextoGUI.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "CajaDeTextoGUI.h"

// Crea una caja de texto.
CajaDeTextoGUI::CajaDeTextoGUI(){
	texto = NULL;
	llena = false;
}

// Destruye la caja de texto.
CajaDeTextoGUI::~CajaDeTextoGUI(){
	if (texto) delete texto;
}

// Una vez asignadas la posicion y dimensiones, se debe llamar a este metodo,
// encargado de inicializar el objeto a un estado valido para ser utilizado.
void CajaDeTextoGUI::inicializar(){

	ElementoGUI::inicializar();

	// Inicializa el texto.
	texto = new TextoGUI;
	texto->asignarPosicion(rectanguloADibujar.x, rectanguloADibujar.y);
	texto->asignarDimensiones(rectanguloADibujar.w, rectanguloADibujar.h);
	texto->inicializar();
}

// Maneja el evento dado.
void CajaDeTextoGUI::manejarEvento(SDL_Event evento){

	SDL_Point posicionClick;

	// Checkea que tipo de evento es, y actua en consecuencia.
	switch(evento.type){
	case SDL_MOUSEBUTTONDOWN:

		// Analiza si se clickeo el boton.
		posicionClick.x = evento.button.x; posicionClick.y = evento.button.y;
		if (estaSiendoClickeado(posicionClick)) tieneFoco = true;
		else tieneFoco = false;
		break;
	case SDL_TEXTINPUT:

		// Registra lo que se escribio, si tiene foco. En caso contrario, lo ignora.
		if(tieneFoco) texto->agregarEnPosicion(evento.text.text, texto->tamanio());
		break;
	case SDL_KEYDOWN:

		// Maneja el caso BACKSPACE, borrando un caracter del texto registrado, si tiene foco.
		// En caso contrario, lo ignora.
		if( tieneFoco && evento.key.keysym.sym == SDLK_BACKSPACE && texto->tamanio() > 0 )
			texto->remover(texto->tamanio() - 1);

		// Maneja el caso ENTER, notificando.
		if( tieneFoco && evento.key.keysym.sym == SDLK_RETURN ){
			llena = true;
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(CAJADETEXTOLLENA);
		}
		break;
	}
}

// Dibuja el elemento en pantalla.
void CajaDeTextoGUI::dibujar(){

	// Obtiene la textura correspondiente a la caja de texto.
	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(CAJADETEXTO);

	FiguraGeometrica * sprite = forma->normalizar();
	tex->dibujar(forma, sprite);

	delete sprite;

	// Dibuja el texto
	texto->dibujar();
}

// Devuelve lo que esta escrito en la caja de texto.
std::string CajaDeTextoGUI::obtenerContenido(){
	return texto->obtenerTexto();
}

// Devuelve el estado de la caja de texto.
bool CajaDeTextoGUI::estaLlena(){
	return llena;
}

// Resetea la caja de texto.
void CajaDeTextoGUI::vaciar(){
	llena = false;
	while (texto->tamanio() != 0) texto->remover(0);
}

