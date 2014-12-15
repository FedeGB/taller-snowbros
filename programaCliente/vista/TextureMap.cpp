/*
 * TextureMap.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: rodrizapico
 */

#include "TextureMap.h"

// Crea un mapa de texturas.
TextureMap::TextureMap() {
}

// Destruye el mapa de texturas.
TextureMap::~TextureMap() {

	for (TextureMap::iterator it = this->begin(); it != this->end(); it++){
		if ((*it).second) {
			delete (*it).second;
			(*it).second = NULL;
		}
	}

}

// Carga todas las texturas que se utilizaran en el juego, junto con sus
// areas de rendereo.
bool TextureMap::inicializar(){

/*	if (!loadMetadataTex()) return false;

	if (!loadENESTex()) return false;
	if (!loadENTIFUETex()) return false;
	if (!loadCircleTex()) return false;
	if (!loadCuadTex()) return false;
	if (!loadFireBallTex()) return false;
	if (!loadSnowBallTex()) return false;
	if (!loadSorpresasTex()) return false;
	if (!loadLagunaTex()) return false;
	if (!loadGameOverTex()) return false;
*/

	if (!cargarTexturasBotones()) return false;
	if (!cargarTexturasPJ()) return false;
	if (!cargarTexturasEnemigos()) return false;
	if (!cargarTexturasAuxiliares()) return false;
	return true;
}

// Devuelve la textura correspondiente a tipoTextura.
Textura * TextureMap::obtenerTextura(tipo_textura_t tipoTextura){
	return (*this)[tipoTextura];
}

// Devuelve una textura correspondiente al texto pedido.
// A diferencia de las texturas de elementos de la UI, las texturas de
// textos deben ser liberadas cuando se terminan de utilizar.
Textura * TextureMap::generarTexturaTexto(std::string texto, estilo_texto_t estilo){

	// TODO: sacar los parametros hardcodeados y cargarlos segun el estilo elegido.
	std::string fuente;
	if (estilo == PANTALLAINICIARSESION) fuente = "fuentes/UbuntuMono-B.ttf";
	if (estilo == ESTADOJUGADOR) fuente = "fuentes/UbuntuMono-R.ttf";
	int tamanio;
	if (estilo == PANTALLAINICIARSESION) tamanio = 14;
	if (estilo == ESTADOJUGADOR) tamanio = 9;
	SDL_Color color;
	color.r = 0; color.g = 0; color.b = 0; color.a = 255;

	Textura * tex = new Textura();
	if (!tex->generarTexto(fuente, tamanio, texto, color)) return NULL;

	return tex;
}

// Carga las texturas correspondientes a los botones del juego.
bool TextureMap::cargarTexturasBotones(){

	// Crea la textura y carga la imagen.
	Textura * tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_BOTON1)) return false;

	// Agrega la textura al mapa.
	(*this)[BOTON1] = tex;

	// Crea la textura y carga la imagen.
	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_BOTON2)) return false;

	// Agrega la textura al mapa.
	(*this)[BOTON2] = tex;

	// Crea la textura y carga la imagen.
	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_CAJADETEXTO)) return false;

	// Agrega la textura al mapa.
	(*this)[CAJADETEXTO] = tex;

	return true;
}

bool TextureMap::cargarTexturasPJ(){

	// Crea la textura y carga la imagen.
	Textura * tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_PJ)) return false;

	// Agrega la textura al mapa.
	(*this)[PJ] = tex;

	return true;
}

bool TextureMap::cargarTexturasEnemigos(){

	// Crea la textura y carga la imagen.
	Textura * tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_ENEMIGOESTANDAR)) return false;

	// Agrega la textura al mapa.
	(*this)[ENEMIGOESTANDAR] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_ENEMIGOFUEGO)) return false;

	// Agrega la textura al mapa.
	(*this)[ENEMIGOFUEGO] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_BOLAENEMIGOPARCIAL)) return false;

	// Agrega la textura al mapa.
	(*this)[BOLAENEMIGOPARCIAL] = tex;

	return true;
}

bool TextureMap::cargarTexturasAuxiliares(){

	// Crea la textura y carga la imagen.
	Textura * tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_BOLADEFUEGO)) return false;

	// Agrega la textura al mapa.
	(*this)[BOLADEFUEGO] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_BOLADENIEVE)) return false;

	// Agrega la textura al mapa.
	(*this)[BOLADENIEVE] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_PELOTADENIEVE)) return false;

	// Agrega la textura al mapa.
	(*this)[PELOTADENIEVE] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_LADRILLO)) return false;

	// Agrega la textura al mapa.
	(*this)[LADRILLO] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_LAGUNA)) return false;

	// Agrega la textura al mapa.
	(*this)[LAGUNA] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_AGUJERO)) return false;

	// Agrega la textura al mapa.
	(*this)[AGUJERO] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_INMUNIDAD)) return false;

	// Agrega la textura al mapa.
	(*this)[INMUNIDAD] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_SORPRESACORRER)) return false;

	// Agrega la textura al mapa.
	(*this)[SORPRESACORRER] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_SORPRESALEJOS)) return false;

	// Agrega la textura al mapa.
	(*this)[SORPRESALEJOS] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_SORPRESAPOTENTE)) return false;

	// Agrega la textura al mapa.
	(*this)[SORPRESAPOTENTE] = tex;

	tex = new Textura();
	if (!tex) return false;
	if (!tex->generar(PATH_TEXTURA_FONDO)) return false;

	// Agrega la textura al mapa.
	(*this)[FONDO] = tex;

	return true;
}

/*
bool TextureMap::loadMetadataTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(TEXTURA_VIDA);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	temp->tex = tex;
	(*this)[VIDAS1] = temp;

	tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}

	SDL_Color c = {255, 160, 100, 255};
	tex->generarTexto(FONT_TTF, 30, "Puntaje: 0", c);

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	temp->tex = tex;
	(*this)[PUNTAJE1] = temp;

	tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(IMAGEN_FONDO);

	temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	temp->tex = tex;
	(*this)[FONDO1] = temp;
	return true;
}



bool TextureMap::loadENESTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	// TODO: Otra textura para enemigo
	tex->generar(ENEMIES_SHEET);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 5 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 7 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 30 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[ENES] = temp;

	return true;
}

bool TextureMap::loadENTIFUETex() {
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(ENEMIES_SHEET);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 5 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 7 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 30 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 35 / 320.0f;
	temp->tex = tex;
	(*this)[ENTIFUE] = temp;

	return true;
}

bool TextureMap::loadSnowBallTex(){
		Textura * tex = new Textura();
		if (!tex) {
			std::cout << "no se cargo la imagen" << std::endl;
			return false;
		}
		tex->generar(SPRITE_SHEET);

		TexAndVertexes * temp = new TexAndVertexes;
		temp->vertexes = new Vertexes(4);
		temp->vertexes->x[0] = temp->vertexes->x[3] = 290 / 432.0f;
		temp->vertexes->y[0] = temp->vertexes->y[1] = 215 / 320.0f;
		temp->vertexes->x[1] = temp->vertexes->x[2] = 300 / 432.0f;
		temp->vertexes->y[2] = temp->vertexes->y[3] = 230 / 320.0f;
		temp->tex = tex;
		(*this)[PODER1] = temp;

		return true;
}

bool TextureMap::loadFireBallTex(){
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(SPRITE_SHEET);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 290 / 432.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 215 / 320.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 300 / 432.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 230 / 320.0f;
	temp->tex = tex;
	(*this)[PODER2] = temp;

	return true;
}

bool TextureMap::loadSorpresasTex(){
	// TODO: sacar hardcodeo del path de imagen.
		Textura * tex = new Textura();
		if (!tex) {
			std::cout << "no se cargo la imagen" << std::endl;
			return false;
		}
		tex->generar(ENEMIES_SHEET);

		TexAndVertexes * temp = new TexAndVertexes;
		temp->vertexes = new Vertexes(4);
		temp->vertexes->x[0] = temp->vertexes->x[3] = 175 / 428.0f;
		temp->vertexes->y[0] = temp->vertexes->y[1] = 275 / 365.0f;
		temp->vertexes->x[1] = temp->vertexes->x[2] = 183 / 428.0f;
		temp->vertexes->y[2] = temp->vertexes->y[3] = 287 / 365.0f;
		temp->tex = tex;
		(*this)[SORPRESAvida] = temp;

		return true;
}

bool TextureMap::loadLagunaTex(){
	// TODO: sacar hardcodeo del path de imagen.
		Textura * tex = new Textura();
		if (!tex) {
			std::cout << "no se cargo la imagen" << std::endl;
			return false;
		}
		tex->generar(TEXTURA_LAGUNA);

		TexAndVertexes * temp = new TexAndVertexes;
		temp->vertexes = new Vertexes(4);
		temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
		temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
		temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
		temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
		temp->tex = tex;
		(*this)[spriteLAGUNA] = temp;

		return true;
}

bool TextureMap::loadCircleTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(TEXTURA_PELOTA);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(20);

	for (int i = 0; i < 20; i++) {
		float thita = (2 * i * PI / 20);
		temp->vertexes->x[i] = ( 128 + 128 * cos(thita) ) / 256.0f;
		temp->vertexes->y[i] = ( 128 - 128 * sin(thita) ) / 256.0f;
	}
	temp->tex = tex;
	(*this)[CIRCULO1] = temp;

	return true;
}

bool TextureMap::loadGameOverTex(){

	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(IMAGEN_GAMEOVER);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	temp->tex = tex;
	(*this)[GAMEOVER] = temp;
	return true;
}

bool TextureMap::loadCuadTex(){

	// TODO: sacar hardcodeo del path de imagen.
	Textura * tex = new Textura();
	if (!tex) {
		std::cout << "no se cargo la imagen" << std::endl;
		return false;
	}
	tex->generar(TEXTURA_LADRILLO);

	TexAndVertexes * temp = new TexAndVertexes;
	temp->vertexes = new Vertexes(4);
	temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
	temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
	temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
	temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;

	temp->tex = tex;
	(*this)[CUADRILATERO1] = temp;

	tex= new Textura();
	 temp = new TexAndVertexes;
		temp->vertexes = new Vertexes(4);
		temp->vertexes->x[0] = temp->vertexes->x[3] = 0.0f;
		temp->vertexes->y[0] = temp->vertexes->y[1] = 0.0f;
		temp->vertexes->x[1] = temp->vertexes->x[2] = 1.0f;
		temp->vertexes->y[2] = temp->vertexes->y[3] = 1.0f;
	tex->generar(TEXTURA_HIELO);
	temp->tex =tex;
	(*this)[CUADRILATERO2] = temp;

	return true;
}
*/


