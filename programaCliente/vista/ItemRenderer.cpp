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
void ItemRenderer::renderPoligono(PoligonoRegular * item, float escala){
	// Calculo la posicion de los vertices.
	float vx[item->nLados]; float vy[item->nLados];
	float vxTex[item->nLados]; float vyTex[item->nLados];
	for (int i = 0; i < item->nLados; i++) {
		float thita1 = (2 * i * PI / item->nLados) - (item->angulo);
		float thita2 = (2 * i * PI / item->nLados);
		vx[i] = ( item->posicion.x + item->radio * cos(thita1) ) * escala;
		vy[i] = ( item->posicion.y - item->radio * sin(thita1) ) * escala;
		vxTex[i] = ( item->radio +  item->radio * cos(thita2) ) * escalaPorDefecto / 128.0f;
		vyTex[i] = ( item->radio - item->radio * sin(thita2) ) * escalaPorDefecto / 128.0f;
	}

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[CUADRILATERO1];

	// Renderea.
	TaV->tex->dibujar(vx, vy, vxTex, vyTex, item->nLados);

}

// Obtiene la posicion de los vertices para el sprite pedido.
Vertexes * obtenerVerticesPJ(sprite_t activeSprite){

	Vertexes * vertexes = new Vertexes(4);

	if (activeSprite == PARADOIZQUIERDA){
		vertexes->x[0] = vertexes->x[3] = 7 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 9 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 30 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA1){
		vertexes->x[0] = vertexes->x[3] = 37 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 9 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 60 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA2){
		vertexes->x[0] = vertexes->x[3] = 62 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 9 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 85 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA3){
		vertexes->x[0] = vertexes->x[3] = 92 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 9 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 115 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA4){
		vertexes->x[0] = vertexes->x[3] = 62 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 9 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 85 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA1){
		vertexes->x[0] = vertexes->x[3] = 152 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 6 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 175 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA2){
		vertexes->x[0] = vertexes->x[3] = 184 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 6 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 207 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA3){
		vertexes->x[0] = vertexes->x[3] = 215 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 6 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 238 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA4){
		vertexes->x[0] = vertexes->x[3] = 249 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 6 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 272 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA5){
		vertexes->x[0] = vertexes->x[3] = 118 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 6 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 141 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 35 / 320.0f;
	}

	return vertexes;
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

	// Obtiene los vertices del sprite.
	Vertexes * vert = obtenerVerticesPJ(item->activeSprite);

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[PJ1];

	// Si esta no esta conectado, se cambia el color a gris.
	if(!item->online)
		TaV->tex->dibujarOscuro(vx, vy, vert->x, vert->y, 4);// cambio el color
	else
	// Renderea.
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);

	delete vert;
}

// Dibuja la metadata del juego: las vidas, puntaje, y el fondo.
void ItemRenderer::renderMetadata(Metadata * item){

	GLfloat vx[4]; GLfloat vy[4];

	// Calcula la posicion del fondo
	// TODO: HARDCODEO!!!
	vx[0] = vx[3] = 0;
	vy[0] = vy[1] = 0;
	vx[1] = vx[2] = 720;
	vy[2] = vy[3] = 640;

	float vxTex[4]; float vyTex[4];

	// Calculo los vertices de la textura.
	vxTex[0] = vxTex[3] = item->posXCamara;
	vyTex[0] = vyTex[1] = item->posYCamara;
	vxTex[1] = vxTex[2] = item->posXCamara + item->anchoCamara;
	vyTex[2] = vyTex[3] = item->posYCamara + item->altoCamara;

	TexAndVertexes * TaV = textureMap[FONDO1];

	// Renderea fondo.
	TaV->tex->dibujar(vx, vy, vxTex, vyTex, 4);

	// Obtiene la textura y su correspondiente rect para renderear las vidas.
	TaV = textureMap[VIDAS1];

	for (int i = 0; i < item->vidas; i++){

		// Calcula la posicion de los corazones de vida.
		vx[0] = vx[3] = 20 + i * 54;
		vy[0] = vy[1] = 20;
		vx[1] = vx[2] = 68 + i * 54;
		vy[2] = vy[3] = 68;

		// Renderea vidas.
		TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
	}

	// Calcula la posicion del puntaje
	vx[0] = vx[3] = 600;
	vy[0] = vy[1] = 25;
	vx[1] = vx[2] = 700;
	vy[2] = vy[3] = 50;

	TaV = textureMap[PUNTAJE1];
	TaV->tex->eliminar();
	SDL_Color c = {255, 160, 100, 255};
	std::string puntaje = SSTR("Puntaje: " << item->puntaje);
	TaV->tex->generarTexto("fuentes/Ubuntu-B.ttf", 30, puntaje, c);

	// Renderea puntaje.
	TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);

}

// Dibuja un item del mundo.
void ItemRenderer::render(WorldItem * item, float escala){

	if (!textureMap.yaInicializado()) textureMap.init();

	switch(item->tipo){
	case CIRCULO:
		renderCirculo((Circulo*)item, escala);
		break;
	case CUADRILATERO:
		renderCuadrilatero((Cuadrilatero*)item, escala);
		break;
	case POLIGONOREGULAR:
		renderPoligono((PoligonoRegular*)item, escala);
		break;
	case PJ:
		renderPJ((Personaje*)item, escala);
		break;
	case METADATA:
		renderMetadata((Metadata*)item);
		break;
	}
}

