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
#include "../utiles/Logger.h"
#include "interfaces/IDibujable.h"

class Fondo : public IDibujable {
public:
	Fondo() : path(""), width(640), height(480) {
	};
	Fondo(int w, int h) : path("") , width(w), height(h){
/*		r = new SDL_Rect();
		r->x = 0;
		r->y = 0;
		r->h = height;
		r->w = width;*/
	};
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
			log.escribirLog(WARNING, "No se pudo cargar la imagen "+ path + "!");
			log.cerrarLog();
			return false;
		}
		else
		{
			dTextura = SDL_CreateTextureFromSurface(dRenderer, imagenCargada);
			if(!dTextura) {
				if (!log.abrirLog(WINDOWLOG)) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return false;
				}
				log.escribirLog(WARNING, "No se pudo crear la textura de " + path + "!");
				log.cerrarLog();
				return false;
			}
			SDL_FreeSurface( imagenCargada );
		}

		return true;
	}

	virtual void render() {
		SDL_RenderCopy( dRenderer, dTextura, NULL, NULL );
	}

	void dibujar()
	{
		render();
	};

private:
	std::string path;
	int width, height;
};



#endif /* FONDO_H_ */
