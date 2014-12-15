/*
 * TextoGUI.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "TextoGUI.h"

// Crea un texto.
TextoGUI::TextoGUI(){
	texto = " ";
	estilo = PANTALLAINICIARSESION;
}

// Destruye el texto.
TextoGUI::~TextoGUI(){

}

// Maneja el evento dado.
void TextoGUI::manejarEvento(SDL_Event evento){
}

// Dibuja el elemento en pantalla.
void TextoGUI::dibujar(){

	// Genera una textura en base al texto a renderear.
	ServicioControladorDeTexturas * controladorTexturas = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * texturaTexto = controladorTexturas->generarTexturaTexto(texto, estilo);

	FiguraGeometrica * sprite = forma->normalizar();
	texturaTexto->dibujar(forma, sprite);

	delete sprite;
	delete texturaTexto;
}

// Asigna el estilo de texto deseado.
void TextoGUI::asignarEstilo(estilo_texto_t e){
	estilo = e;
}

// Metodos para manejo del texto a renderear.
int TextoGUI::tamanio(){
	if (texto == " ") return 0;
	return texto.size();
}

std::string TextoGUI::obtenerTexto(){
	return texto;
}

void TextoGUI::reemplazarTexto(std::string nuevoTexto){
	if (nuevoTexto.empty()) texto = " ";
	else texto = nuevoTexto;
}

void TextoGUI::agregarEnPosicion(std::string agregado, int posicion){
	if (texto == " ") texto = agregado;
	else texto.insert(posicion, agregado);
}

void TextoGUI::remover(int posicion){
	texto.erase(posicion);
	if (texto.empty()) texto = " ";
}
