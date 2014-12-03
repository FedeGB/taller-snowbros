/*
 * Textura.cpp
 *
 *  Created on: 5/10/2014
 *      Author: manuel
 */


#include "Textura.h"

//#include "../vista/Camera.h"

Textura::Textura() :id_tex(0) {}

Textura::~Textura() {
	eliminar();
}

void Textura::eliminar(){
	glDeleteTextures(1, &id_tex);
}

// Genera una textura en base a un archivo de imagen, para ser utilizada
// al renderear objetos en el mundo.
// path: la ruta al archivo de imagen del que se debe cargar la textura.
// return: true si se cargo con exito, false en caso contrario.
bool Textura::generar(std::string path) {

	Logger& log = * Logger::Instancia();

	bool exito = true;
	SDL_Surface *surface = NULL; // this surface will tell us the details of the image
	surface = IMG_Load(path.c_str());

	if (surface == NULL) log.log(TEXTURALOG, WARNING, "No se pudo crear la textura '"
			+ path + "' : " + SDL_GetError() + ". Se rellena la figura con color.");

	GLenum texture_format;
	GLint nofcolors = surface->format->BytesPerPixel;
	std::cout << "el numero de bytes por pixel es: " << nofcolors << std::endl;
	// seteo los parametros para la funcion glTexImage2D
	if (nofcolors == 4) {
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (nofcolors == 3) //no alpha channel
			{
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else log.log(TEXTURALOG, WARNING, "La imagen '"+ path+"' no es RGB. "
				"No se puede generar la textura. Se rellena la figura con color.");

	// Have OpenGL generate a texture object handle for us
	glGenTextures(1, &id_tex);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, id_tex);

	glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->w);

	// Set the texture's stretching properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexImage2D(GL_TEXTURE_2D, 0, nofcolors, surface->w, surface->h, 0,
			texture_format, GL_UNSIGNED_BYTE, surface->pixels);

	glBindTexture( GL_TEXTURE_2D, 0);

	// Free the SDL_Surface only if it was successfully created
	if (surface) {
		SDL_FreeSurface(surface);
	}

	return exito;
}


bool Textura::generarTexto(std::string path, int tamanio, std::string txt, SDL_Color color) {

	TTF_Font* fuente = TTF_OpenFont(path.c_str(), tamanio);

	bool exito = true;
	SDL_Surface *surface = NULL; // this surface will tell us the details of the image
	surface = TTF_RenderText_Blended(fuente, txt.c_str(), color);

	if (surface == NULL){
		Logger& log = * Logger::Instancia();
		if(log.abrirLog(TEXTURALOG)) {
			std::string err(SDL_GetError());
			log.escribirLog(WARNING, "No se pudo crear la textura '"+ path+"' : "+err+". Se rellena la figura con color.");
			log.cerrarLog();
		}else
			std::cout << "NO SE PUDO ABRIR EL LOG " << TEXTURALOG << "." << std::endl;
		return !exito;
	}

	GLenum texture_format;
	GLint nofcolors = surface->format->BytesPerPixel;
	// seteo los parametros para la funcion glTexImage2D
	if (nofcolors == 4) {
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (nofcolors == 3) { //no alpha channel
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		Logger& log = * Logger::Instancia();
		if(log.abrirLog(TEXTURALOG)) {
			std::string err(SDL_GetError());
			log.escribirLog(WARNING, "La imagen '"+ path+"' no es RGB. No se puede generar la textura. Se rellena la figura con color.");
			log.cerrarLog();
		}else
			std::cout << "NO SE PUDO ABRIR EL LOG " << TEXTURALOG << "." << std::endl;
		return !exito;
	}

	// Have OpenGL generate a texture object handle for us
	glGenTextures(1, &id_tex);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, id_tex);

	glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->w);

	// Set the texture's stretching properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexImage2D(GL_TEXTURE_2D, 0, nofcolors, surface->w, surface->h, 0,
			texture_format, GL_UNSIGNED_BYTE, surface->pixels);

	glBindTexture( GL_TEXTURE_2D, 0);

	// Free the SDL_Surface only if it was successfully created
	if (surface) {
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	if (fuente) {
		TTF_CloseFont(fuente);
		fuente = NULL;
	}

	return exito;
}


void Textura::dibujar(GLfloat* vx, GLfloat* vy, float* s, float* t, int n) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

	// Bind the texture to which subsequent calls refer to
	glBindTexture( GL_TEXTURE_2D, id_tex);
	glFinish();

	glBegin( GL_POLYGON);

	for( int i = 0; i < n; i++ ){
		glTexCoord2f(s[i], t[i]);
		glVertex3f(vx[i], vy[i], 0);
	}

	glEnd();
	glFlush();

	glDisable( GL_BLEND );
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Textura::dibujarOscuro(GLfloat* vx, GLfloat* vy, float* s, float* t, int n) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	glEnable( GL_BLEND );

	// Bind the texture to which subsequent calls refer to
	glBindTexture( GL_TEXTURE_2D, id_tex);

	glBegin( GL_POLYGON);

	for( int i = 0; i < n; i++ ){
		glTexCoord2f(s[i], t[i]);
		glVertex3f(vx[i], vy[i], 0);
	}

	glEnd();
	glFlush();

	glDisable( GL_BLEND );
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
