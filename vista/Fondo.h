/*
 * Fondo.h
 *
 *  Created on: 8/9/2014
 *      Author: manuel
 */

#ifndef FONDO_H_
#define FONDO_H_

#include <string.h>
#include <SDL2/SDL_image.h>

#include "../modelo/interfaces/IDibujable.h"

class Fondo : public IDibujable {
public:
	Fondo() : path(""), width(640), heigth(480) {};
	Fondo(int w, int h) : path("") , width(w), heigth(h){};
	virtual ~Fondo(){};

	bool cargarImagen(std::string path)
	{
		Logger& log = * Logger::Instancia();

		this->path = path;

		SDL_Surface* imagenCargada = IMG_Load(path.c_str());
		if( !imagenCargada )
		{
			if (!log.abrirLog(WINDOWLOG)) {
				std::cout << "Error al abrir archivo de log" << std::endl;
				return false;
			}
			log.escribirLog("WAR", "No se pudo cargar la imagen "+ path + "!");
			log.cerrarLog();
			return false;
		}
		else
		{
			dTextura = SDL_CreateTextureFromSurface(dRenderer, imagenCargada);
		}

		return true;
	}

	SDL_Rect getRecuadroDeDibujo()
	{
		SDL_Rect r = { 0, 0, width, heigth };
		return r;
	}

	void dibujar()
	{
		render();
	};

private:
	std::string path;
	int width, heigth;
};



#endif /* FONDO_H_ */
