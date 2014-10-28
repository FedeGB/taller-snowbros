/*
 * ItemRenderer.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: rodrizapico
 */

#include "ItemRenderer.h"

TextureMap ItemRenderer::textureMap;
float ItemRenderer::escalaPorDefecto = 20;

ItemRenderer::ItemRenderer() {
}

ItemRenderer::~ItemRenderer() {
	// TODO Auto-generated destructor stub
}

// Dibuja un circulo.
void ItemRenderer::renderCirculo(Circulo * item, float escala){

	// Convierte los parametros de B2D en los necesarios para renderear el sprite.
	// Obtiene la seccion de la pantalla a renderear.
	GLfloat vx[20];
	GLfloat vy[20];

	for (int i = 0; i < 20; i++) {
		float thita = (2 * i * PI / 20) - (item->angulo);
		vx[i] = ( item->posicion.x + item->radio * cos(thita) ) * escala;
		vy[i] = ( item->posicion.y - item->radio * sin(thita) ) * escala;
	}

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[CIRCULO1];

	// Renderea.
	TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 20);

}

// Dibuja un cuadrilatero.
void ItemRenderer::renderCuadrilatero(Cuadrilatero * item, float escala){

	float vx[4]; float vy[4];
	float vxTex[4]; float vyTex[4];

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


	// Calculo los vertices de la textura.
	vxTex[0] = vxTex[3] = 0.0f;
	vyTex[0] = vyTex[1] = 0.0f;
	vxTex[1] = vxTex[2] = item->baseMayor * escalaPorDefecto / 128.0f;
	vyTex[2] = vyTex[3] = item->altura * escalaPorDefecto / 128.0f;

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[CUADRILATERO1];

	// Renderea.
	TaV->tex->dibujar(vx, vy, vxTex, vyTex, 4);
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
void ItemRenderer::renderPJ(Personaje * item, float escala){
	// Convierte los parametros de B2D en los necesarios para renderear el sprite.
	// Obtiene la seccion de la pantalla a renderear.
	GLfloat vx[4];
	GLfloat vy[4];

	// Flippea la imagen si es necesario.
	if (item->orientation == Personaje::LEFT){
		vx[0] = vx[3] = (item->posicion.x - item->baseMayor / 2) * escala;
		vy[0] = vy[1] = (item->posicion.y - item->altura / 2) * escala;
		vx[1] = vx[2] = vx[0] + item->baseMayor * escala;
		vy[2] = vy[3] = vy[0] + item->altura * escala;
	} else {
		vx[1] = vx[2] = (item->posicion.x - item->baseMayor / 2) * escala;
		vy[0] = vy[1] = (item->posicion.y - item->altura / 2) * escala;
		vx[0] = vx[3] = vx[1] + item->baseMayor * escala;
		vy[2] = vy[3] = vy[0] + item->altura * escala;
	}

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[item->activeSprite];

	// Si esta no esta conectado, se cambia el color a gris.
/*	if(!item->online)
		SDL_SetTextureAlphaMod(TaV.tex,150);// cambio el color
	else
		SDL_SetTextureAlphaMod(TaV.tex,255);
*/

	// Renderea.
	TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);

}

// Dibuja un item del mundo.
void ItemRenderer::render(SDL_Renderer* wRenderer, WorldItem * item, float escala){

	if (!textureMap.yaInicializado()) textureMap.init();

	switch(item->tipo){
	case CIRCULO:
		renderCirculo((Circulo*)item, escala);
		break;
	case CUADRILATERO:
		renderCuadrilatero((Cuadrilatero*)item, escala);
		break;
	case POLIGONOREGULAR:
		renderPoligono(wRenderer, (PoligonoRegular*)item, escala);
		break;
	case PJ:
		renderPJ((Personaje*)item, escala);
		break;
	}
}

