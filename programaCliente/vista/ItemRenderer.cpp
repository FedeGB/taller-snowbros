/*
 * ItemRenderer.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: rodrizapico
 */

#include "ItemRenderer.h"

TextureMap ItemRenderer::textureMap;

ItemRenderer::ItemRenderer() {
	// TODO Auto-generated constructor stub

}

ItemRenderer::~ItemRenderer() {
	// TODO Auto-generated destructor stub
}

// Dibuja la marca de un circulo, para poder ver su rotacion.
int renderMarca(SDL_Renderer* renderer, Circulo * item, float escala) {

	Sint16 radioArco  = (Sint16)(item->radio*0.4 * escala);
	// TODO: HARDCODEADO!!!
	Uint8 newRed = 255 - 255;
	Uint8 newGreen = 255 - 0;
	Uint8 newBlue = 255 - 0;
	int32 anguloInit = RADTODEG * item->angulo;
	if(anguloInit > 360) {
		anguloInit -= 360;
	}
	int32 anguloEnd = anguloInit + 70;

	Sint16 posX = item->posicion.x * escala;
	Sint16 posY = item->posicion.y * escala;

	return arcRGBA(renderer, posX, posY, radioArco, anguloInit, anguloEnd, newRed, newGreen, newBlue, 255);
}

// Dibuja un circulo.
void ItemRenderer::renderCirculo(SDL_Renderer* renderer, Circulo * item, float escala){

	// Calculo posicion y radio.
	Sint16 posX = item->posicion.x * escala;
	Sint16 posY = item->posicion.y * escala;
	Sint16 rad = item->radio * escala;

	// Rendereo el circulo.
	// TODO: (255,0,0,255) color HARDCODEADO!!
	int status = filledCircleRGBA(renderer, posX, posY, rad, 255, 0, 0, 255);
	if(status != 0) {
		Logger& log = * Logger::Instancia();
		std::string err(SDL_GetError());
		log.log(DIBUJABLELOG, WARNING, "No se renderizo el circulo "+err);
	}

	status = renderMarca(renderer, item, escala);
	if(status != 0) {
		Logger& log = * Logger::Instancia();
		std::string err(SDL_GetError());
		log.log(DIBUJABLELOG, WARNING, "No se renderizo la marca del circulo "+err);
	}
}

// Dibuja un cuadrilatero.
void ItemRenderer::renderCuadrilatero(SDL_Renderer* renderer, Cuadrilatero * item, float escala){

	Sint16 vx[4]; Sint16 vy[4];

	// Calculo la posicion del centro.
	float32 centroX = ( ( 2 * item->baseMenor * item->desplazamiento +
			item->baseMayor * item->desplazamiento + item->baseMayor * item->baseMenor +
			pow(item->baseMayor,2) + pow(item->baseMenor,2) ) /
			(3 * (item->baseMayor + item->baseMenor) ) );
	float32 centroY = ( ( item->altura * (item->baseMayor + 2 * item->baseMenor) ) /
			(3 * (item->baseMayor + item->baseMenor) ) );

	// Calculo los modulos.
	float32 modulo0 = sqrt( pow(- centroX, 2) + pow(centroY, 2) );
	float32 modulo1 = sqrt( pow(- centroX + item->baseMayor, 2) + pow(centroY, 2) );
	float32 modulo2 = sqrt( pow(- centroX + item->desplazamiento + item->baseMenor, 2) +
			pow(centroY - item->altura, 2) );
	float32 modulo3 = sqrt( pow(- centroX + item->desplazamiento, 2) +
			pow(centroY - item->altura, 2) );

	// Calculo los angulos.
	float32 thita0 = PI + atan( centroY / (centroX) ) - item->angulo;
	float32 thita1 =  2 * PI - atan( centroY / (-centroX + item->baseMayor) ) - item->angulo;
	float32 thita2 =  atan( (-centroY + item->altura) /
			(-centroX + item->desplazamiento + item->baseMenor) ) - item->angulo;
	float32 thita3 =  PI - atan( (-centroY + item->altura) /
			(centroX - item->desplazamiento) ) - item->angulo;

	// Calculo la posicion de los vertices.
	vx[0] = (item->posicion.x + modulo0 * cos(thita0) ) * escala;
	vy[0] = (item->posicion.y - modulo0 * sin(thita0)) * escala;
	vx[1] = (item->posicion.x + modulo1 * cos(thita1)) * escala;
	vy[1] = (item->posicion.y - modulo1 * sin(thita1)) * escala;
	vx[2] = (item->posicion.x + modulo2 * cos(thita2)) * escala;
	vy[2] = (item->posicion.y - modulo2 * sin(thita2)) * escala;
	vx[3] = (item->posicion.x + modulo3 * cos(thita3)) * escala;
	vy[3] = (item->posicion.y - modulo3 * sin(thita3)) * escala;

	// Rendereo.
	// TODO: (255,0,0,255) color HARDCODEADO!!
	int status = filledPolygonRGBA(renderer, vx, vy, 4, 255, 0, 0, 255);
	if(status != 0) {
		Logger& log = * Logger::Instancia();
		std::string err(SDL_GetError());
		log.log(DIBUJABLELOG, WARNING, "No se renderizo el cuadrilatero "+err);
	}
}

// Dibuja un poligono regular.
void ItemRenderer::renderPoligono(SDL_Renderer* renderer, PoligonoRegular * item, float escala){
	// Calculo la posicion de los vertices.
	Sint16 vx[item->nLados]; Sint16 vy[item->nLados];
	for (int i = 0; i < item->nLados; i++) {
		float thita = (2 * i * PI / item->nLados) - (item->angulo);
		vx[i] = ( item->posicion.x + escala * cos(thita) ) * escala;
		vy[i] = ( item->posicion.y - escala * sin(thita) ) * escala;
	}

	// Rendereo.
	// TODO: (255,0,0,255) color HARDCODEADO!!
	int status = filledPolygonRGBA(renderer, vx, vy, item->nLados, 255, 0, 0, 255);
	if(status != 0) {
		Logger& log = * Logger::Instancia();
		std::string err(SDL_GetError());
		log.log(DIBUJABLELOG, WARNING, "No se renderizo el poligono "+err);
	}

}

// Dibuja un PJ.
void ItemRenderer::renderPJ(SDL_Renderer* renderer, Personaje * item, float escala){
	// Convierte los parametros de B2D en los necesarios para renderear el sprite.
	// Obtiene la seccion de la pantalla a renderear.
	int X = (item->posicion.x - item->baseMayor / 2) * escala;
	int Y = (item->posicion.y - item->altura / 2) * escala;
	int width = item->baseMayor * escala;
	int height = item->altura * escala;
	SDL_Rect pos = {X, Y, width, height};

	// Verifica si tiene que espejar la imagen (si esta mirando hacia la derecha, se espeja).
	SDL_RendererFlip flip;
	if (item->orientation == Personaje::RIGHT) flip = SDL_FLIP_HORIZONTAL;
	else flip = SDL_FLIP_NONE;

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndRect TaR = textureMap[item->activeSprite];
	SDL_SetTextureAlphaMod(TaR.tex,10);// cambio el color
	// Renderea.
	if(!item->online)
		SDL_RenderCopyEx( renderer, TaR.tex, TaR.rect, &pos, 0, NULL, flip);

}

// Dibuja un item del mundo.
void ItemRenderer::render(SDL_Renderer* wRenderer, WorldItem * item, float escala){

	if (!textureMap.yaInicializado()) {
		std::cout << "inicializando mapa de texturas" << std::endl;
		textureMap.init(wRenderer);
	}

	switch(item->tipo){
	case CIRCULO:
		renderCirculo(wRenderer, (Circulo*)item, escala);
		break;
	case CUADRILATERO:
		renderCuadrilatero(wRenderer, (Cuadrilatero*)item, escala);
		break;
	case POLIGONOREGULAR:
		renderPoligono(wRenderer, (PoligonoRegular*)item, escala);
		break;
	case PJ:
			renderPJ(wRenderer, (Personaje*)item, escala);
			break;
	}
}

