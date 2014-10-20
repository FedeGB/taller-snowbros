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

#include <Box2D/Box2D.h>

#include <SDL2/SDL_opengl.h>

#include <string>
#include <sstream>

#include "../../utiles/Logger.h"
#include "../../utiles/tipos.h"

class IDibujable {
public:
	IDibujable() : dTextura(NULL), dRenderer(NULL), s(NULL), t(NULL){
		posicion.Set(0.0,0.0);
		angulo = 0;
		color = {255 , 0 , 0 , 255};
	};
	virtual ~IDibujable()
	{
		free();
	};

	void dibujar()
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
			log.abrirLog(DIBUJABLELOG);
			log.escribirLog(ERROR, "Imposible cargar la imagen " +path+ " " + IMG_GetError());
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
				log.abrirLog(DIBUJABLELOG);
				log.escribirLog(ERROR, "Imposible crear textura desde "+path);
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
		if( s != NULL )
			delete [] s;

		if( t != NULL )
			delete [] t;
	}

	// cada elemnto tiene que redefinir este metodo para devolver el recuadro a donde se va a dibujar la imagen
	//virtual SDL_Rect * getRecuadroDeDibujo() {}

	virtual void render() {	}

	virtual void setRenderer(SDL_Renderer* r){
		dRenderer = r;
	}

	// Determina el color de la figura en base al hex triplet pasado por parametro.
	bool setColor (std::string hexT){

		//TODO: parsear hexT para checkear errores.
		std::stringstream s(hexT.substr(0, 2));
		int R; s >> std::hex >> R;
		int G; s.clear(); s.str(hexT.substr(2, 2)); s >> std::hex >> G;
		int B; s.clear(); s.str(hexT.substr(4, 2)); s >> std::hex >> B;
		color = { R , G , B , 255 };
		return true;
	}

	b2Vec2 getPosicion(){ return posicion; }
	void setPosicion(b2Vec2 p){	posicion.Set(p.x , p.y); }
	void setPosicion(float32 x, float32 y){	posicion.Set(x , y); }

	// Almacena el angulo. Recibe y entrega angulos en radianes.
	float32 getAngulo(){ return angulo; }
	void setAngulo(float32 a){ angulo = a;	}

	virtual void calcularVertices(float* vx, float* vy, int nVertices, float escalaX, float escalaY, float angulo, float worldToWindowScale) {};
	virtual unsigned int getCantidadDeVertices(){ return 0; }

	virtual void setCoord_s(float* _s){ s = _s; }
	virtual void setCoord_t(float* _t){ t =_t; }

	virtual bool dibujarV(float* vx, float* vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a){

//		printf("holanda\n");
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_BLEND );

		glColor4ub(r, g, b, a);

		glBegin(GL_POLYGON);

		for( int i = 0; i < n; i++ ){
			glVertex3f(vx[i], vy[i], 0);
		}

		glEnd();
		glFlush();

		glDisable( GL_BLEND );

		glPopMatrix();
	}

	virtual bool dibujarLineas(float* vx, float* vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_BLEND );

		glColor4ub(r, g, b, a);

		glBegin(GL_LINES);

		for( int i = 0; i < n; i++ ){
			glVertex3f(vx[i], vy[i], 0);
		}

		glEnd();
		glFlush();

		glDisable( GL_BLEND );

		glPopMatrix();
	}

protected:
	SDL_Texture* dTextura;
	SDL_Renderer* dRenderer;
	SDL_Color color;
	b2Vec2 posicion;
	float32 angulo;

	float32* s;
	float32* t;
};



#endif /* IDIBUJABLE_H_ */
