/*
 * IDibujable.h
 *
 *  Created on: 2/9/2014
 *      Author: manuel
 */

#ifndef IDIBUJABLE_H_
#define IDIBUJABLE_H_

#include <SDL2/SDL.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "../../utiles/Logger.h"

class IDibujable {
public:
	IDibujable() : dTextura(NULL), dRenderer(NULL){};
	virtual ~IDibujable()
	{
		free();
	};

	virtual void dibujar()
	{
		render();
	}

	virtual bool cargarImagen(std::string path)
	{
		bool exito = true;
		Logger& log = * Logger::Instancia();
		free();
		// textura final
		SDL_Texture* texturaNueva = NULL;
		//cargamos imagen
		SDL_Surface* surfaceCargada = IMG_Load( path.c_str() );
		if( surfaceCargada  == NULL )
		{
			log.abrirLog("Dibujable.log");
			log.escribirLog("ERROR", "Imposible cargar la imagen "+path+"\n");
			log.cerrarLog();
			return !exito;
		}
		else
		{ 	//Setear color transparente
			//SDL_SetColorKey( surfaceCargada , SDL_TRUE, SDL_MapRGB( surfaceCargada ->format, 0, 0xFF, 0xFF ) );
			//crea nueva textura de la surface
			texturaNueva = SDL_CreateTextureFromSurface( dRenderer, surfaceCargada  );
			if( texturaNueva == NULL )
			{
				log.abrirLog("Dibujable.log");
				log.escribirLog("ERROR", "Imposible crear textura desde "+path+"\n");
				log.cerrarLog();
				return !exito;
			}
			//eliminamos la vieja surface
			SDL_FreeSurface( surfaceCargada );
		}
		//devolvemos el valor de exito
		dTextura = texturaNueva;
		return dTextura != NULL;
	}

	virtual void free()
	{
		 //Free texture if it exists
		if( dTextura != NULL )
		{
			SDL_DestroyTexture( dTextura );
			dTextura = NULL;
		}
	}

	// cada elemnto tiene que redefinir este metodo para devolver el recuadro a donde se va a dibujar la imagen
	virtual SDL_Rect getRecuadroDeDibujo() {};

	virtual void render()
	{
		SDL_Rect r = getRecuadroDeDibujo();
		SDL_RenderCopy( dRenderer, dTextura, NULL, &r );
	}

	void setRenderer(SDL_Renderer* r){
		dRenderer = r;
	}

protected:
	SDL_Texture* dTextura;
	SDL_Renderer* dRenderer;
};



#endif /* IDIBUJABLE_H_ */
