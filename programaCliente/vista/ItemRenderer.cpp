/*
 * ItemRenderer.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: rodrizapico
 */

#include "ItemRenderer.h"

TextureMap ItemRenderer::textureMap;
float ItemRenderer::escalaPorDefecto = 20;
b2Vec2 ItemRenderer::tamanioMundo;
b2Vec2 ItemRenderer::posicionCamara;

SonidosMap ItemRenderer::sonidosMap;

ItemRenderer::ItemRenderer() {
	posicionCamara.x = 0;
	posicionCamara.y = 0;
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

	TexAndVertexes * TaV;
	// Obtiene la textura y su correspondiente rect para renderear.
	if(item->hielo==false)
			  TaV = textureMap[CUADRILATERO1];
		else
			  TaV = textureMap[CUADRILATERO2];

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
	TaV->tex->eliminar();

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

	if (activeSprite == TIRANDOIZQUIERDA1){
			vertexes->x[0] = vertexes->x[3] = 8 / 432.0f;
			vertexes->y[0] = vertexes->y[1] = 51 / 320.0f;
			vertexes->x[1] = vertexes->x[2] = 30 / 432.0f;
			vertexes->y[2] = vertexes->y[3] = 80 / 320.0f;
		}

	if (activeSprite == TIRANDOIZQUIERDA2){
				vertexes->x[0] = vertexes->x[3] = 37 / 432.0f;
				vertexes->y[0] = vertexes->y[1] = 46 / 320.0f;
				vertexes->x[1] = vertexes->x[2] = 60 / 432.0f;
				vertexes->y[2] = vertexes->y[3] = 76 / 320.0f;
			}

	if (activeSprite == TIRANDOIZQUIERDA3){
				vertexes->x[0] = vertexes->x[3] = 72 / 432.0f;
				vertexes->y[0] = vertexes->y[1] = 49 / 320.0f;
				vertexes->x[1] = vertexes->x[2] = 101 / 432.0f;
				vertexes->y[2] = vertexes->y[3] = 76 / 320.0f;
			}
	return vertexes;
}
Vertexes * obtenerVerticesPoder(sprite_t activeSprite){
	Vertexes * vertexes = new Vertexes(4);

		if (activeSprite == PODER1){
			vertexes->x[0] = vertexes->x[3] = 288 / 432.0f;
			vertexes->y[0] = vertexes->y[1] = 212 / 320.0f;
			vertexes->x[1] = vertexes->x[2] = 302 / 432.0f;
			vertexes->y[2] = vertexes->y[3] = 230 / 320.0f;
		}
		if (activeSprite == PODER2){
			vertexes->x[0] = vertexes->x[3] = 311.5 / 432.0f;
			vertexes->y[0] = vertexes->y[1] = 213 / 320.0f;
			vertexes->x[1] = vertexes->x[2] = 324 / 432.0f;
			vertexes->y[2] = vertexes->y[3] = 227 / 320.0f;
		}
		return vertexes;
}

Vertexes * obtenerVerticesSorpresa(sprite_t activeSprite){
	Vertexes * vertexes = new Vertexes(4);

		if (activeSprite == SORPRESAvida){
			vertexes->x[0] = vertexes->x[3] = 175 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 275 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 182 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 287 / 365.0f;
		}
		if (activeSprite == SORPRESAcorrer){
			vertexes->x[0] = vertexes->x[3] = 175 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 289 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 182 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 299 / 365.0f;
		}
		if (activeSprite == SORPRESAnieveLejos){
			vertexes->x[0] = vertexes->x[3] = 164 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 285 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 172 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 295 / 365.0f;
		}
		if (activeSprite == SORPRESAnieveMasPotente){
			vertexes->x[0] = vertexes->x[3] = 153 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 300 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 161 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 311 / 365.0f;
		}
		return vertexes;
}

Vertexes * obtenerVerticesBola(sprite_t activeSprite){
	Vertexes * vertexes = new Vertexes(4);

		if (activeSprite == STUN0){
			vertexes->x[0] = vertexes->x[3] = 0 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 0 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 0 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 0 / 365.0f;
		}
		if (activeSprite == STUN1){
			vertexes->x[0] = vertexes->x[3] = 197 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 306 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 214 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 324 / 365.0f;
		}

		if (activeSprite == STUN2){
			vertexes->x[0] = vertexes->x[3] = 175 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 306 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 194 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 324 / 365.0f;
		}

		if (activeSprite == STUN3){
			vertexes->x[0] = vertexes->x[3] = 222 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 306 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 241 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 325 / 365.0f;
		}
		if (activeSprite == CONGELADO){
			vertexes->x[0] = vertexes->x[3] = 204 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 263 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 223 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 282 / 365.0f;
		}
		return vertexes;
}

Vertexes * obtenerVerticesNieve(sprite_t activeSprite){
	Vertexes * vertexes = new Vertexes(20);
	for (int i = 0; i < 20; i++) {
		float thita = (2 * i * PI / 20);
		vertexes->x[i] = ( 214.5 + 9.5 * cos(thita) ) / 428.0f;
		vertexes->y[i] = ( 272.5 - 9.5 * sin(thita) ) / 365.0f;
	}
	return vertexes;
}

Vertexes * obtenerVerticesFuego(sprite_t activeSprite){
	return obtenerVerticesNieve(activeSprite);
}

Vertexes * obtenerVerticesEnemigo1(sprite_t activeSprite){

	Vertexes * vertexes = new Vertexes(4);

	if (activeSprite == PARADOIZQUIERDA){
		vertexes->x[0] = vertexes->x[3] = 40 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 0;
		vertexes->x[1] = vertexes->x[2] = 60 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA1){
		vertexes->x[0] = vertexes->x[3] = 20 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 0/ 365.0f;
		vertexes->x[1] = vertexes->x[2] = 40 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA2){
		vertexes->x[0] = vertexes->x[3] = 0;
				vertexes->y[0] = vertexes->y[1] = 0;
				vertexes->x[1] = vertexes->x[2] = 20 / 428.0f;
				vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA3){
		vertexes->x[0] = vertexes->x[3] = 20 / 428.0f;
				vertexes->y[0] = vertexes->y[1] = 0/ 365.0f;
				vertexes->x[1] = vertexes->x[2] = 40 / 428.0f;
				vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}

	if (activeSprite == MOVIENDOIZQUIERDA4){
		vertexes->x[0] = vertexes->x[3] = 0;
				vertexes->y[0] = vertexes->y[1] = 0;
				vertexes->x[1] = vertexes->x[2] = 20 / 428.0f;
				vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA1){
		vertexes->x[0] = vertexes->x[3] = 44 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 15.5 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 60 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 34 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA2){
		vertexes->x[0] = vertexes->x[3] = 44 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 15.5 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 60 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 34 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA3){
		vertexes->x[0] = vertexes->x[3] = 44 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 15.5 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 60 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 34 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA4){
		vertexes->x[0] = vertexes->x[3] = 44 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 15.5 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 60 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 34 / 320.0f;
	}

	if (activeSprite == SALTANDOIZQUIERDA5){
		vertexes->x[0] = vertexes->x[3] = 44 / 432.0f;
		vertexes->y[0] = vertexes->y[1] = 34.5 / 320.0f;
		vertexes->x[1] = vertexes->x[2] = 61 / 432.0f;
		vertexes->y[2] = vertexes->y[3] = 52 / 320.0f;
	}

	if (activeSprite == ATRAPADO1){
			vertexes->x[0] = vertexes->x[3] = 0 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 17.5 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 20.5 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 33 / 365.0f;
		}

	if (activeSprite == ATRAPADO2){
			vertexes->x[0] = vertexes->x[3] = 17.5 / 428.0f;
			vertexes->y[0] = vertexes->y[1] = 51.5 / 365.0f;
			vertexes->x[1] = vertexes->x[2] = 39.5 / 428.0f;
			vertexes->y[2] = vertexes->y[3] = 66.5 / 365.0f;
		}
	if (activeSprite == CONGELADO){
				vertexes->x[0] = vertexes->x[3] = 204 / 428.0f;
				vertexes->y[0] = vertexes->y[1] = 263 / 365.0f;
				vertexes->x[1] = vertexes->x[2] = 223 / 428.0f;
				vertexes->y[2] = vertexes->y[3] = 282 / 365.0f;
			}

	return vertexes;
}

Vertexes * obtenerVerticesEnemigo2(sprite_t activeSprite){

	Vertexes * vertexes = new Vertexes(4);

	if (activeSprite == PARADOIZQUIERDA){
		vertexes->x[0] = vertexes->x[3] = 190.5 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 0;
		vertexes->x[1] = vertexes->x[2] = 206 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}
	if (activeSprite == MOVIENDOIZQUIERDA1){
		vertexes->x[0] = vertexes->x[3] = 151/428.0f;
		vertexes->y[0] = vertexes->y[1] = 0;
		vertexes->x[1] = vertexes->x[2] = 172 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 16.5 / 365.0f;
	}
	if (activeSprite == MOVIENDOIZQUIERDA2){
		vertexes->x[0] = vertexes->x[3] = 173.5 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 0/ 365.0f;
		vertexes->x[1] = vertexes->x[2] = 190 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}
	if (activeSprite == MOVIENDOIZQUIERDA3){
		vertexes->x[0] = vertexes->x[3] = 151/428.0f;
		vertexes->y[0] = vertexes->y[1] = 0;
		vertexes->x[1] = vertexes->x[2] = 172 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 16.5 / 365.0f;
	}
	if (activeSprite == MOVIENDOIZQUIERDA4){
		vertexes->x[0] = vertexes->x[3] = 173.5 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 0/ 365.0f;
		vertexes->x[1] = vertexes->x[2] = 190 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 18 / 365.0f;
	}
	if (activeSprite == SALTANDOIZQUIERDA1){
		vertexes->x[0] = vertexes->x[3] = 151/428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 169 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 58 / 365.0f;
	}
	if (activeSprite == SALTANDOIZQUIERDA2){
		vertexes->x[0] = vertexes->x[3] = 151/428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 169 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 58 / 365.0f;
	}
	if (activeSprite == SALTANDOIZQUIERDA3){
		vertexes->x[0] = vertexes->x[3] = 151/428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 169 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 58 / 365.0f;
	}
	if (activeSprite == SALTANDOIZQUIERDA4){
		vertexes->x[0] = vertexes->x[3] = 151/428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 169 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 58 / 365.0f;
	}
	if (activeSprite == SALTANDOIZQUIERDA5){
		vertexes->x[0] = vertexes->x[3] = 151/428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 169 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 58 / 365.0f;
	}
	if (activeSprite == ATRAPADO1){
		vertexes->x[0] = vertexes->x[3] = 173 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 18 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 195 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 34.5 / 365.0f;
	}
	if (activeSprite == ATRAPADO2){
		vertexes->x[0] = vertexes->x[3] = 195 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 18 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 217 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 34.5 / 365.0f;
	}
	if (activeSprite == CONGELADO){
		vertexes->x[0] = vertexes->x[3] = 177 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 323.5 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 197 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 343.5 / 365.0f;
	}
	if (activeSprite == TIRANDOIZQUIERDA1){
		vertexes->x[0] = vertexes->x[3] = 168 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 191 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 56 / 365.0f;
	}

	if (activeSprite == TIRANDOIZQUIERDA2){
		vertexes->x[0] = vertexes->x[3] = 191 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 216 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 54 / 365.0f;
	}

	if (activeSprite == TIRANDOIZQUIERDA3){
		vertexes->x[0] = vertexes->x[3] = 168 / 428.0f;
		vertexes->y[0] = vertexes->y[1] = 35 / 365.0f;
		vertexes->x[1] = vertexes->x[2] = 191 / 428.0f;
		vertexes->y[2] = vertexes->y[3] = 56 / 365.0f;
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
	if(!item->online||item->inmunity){
		TaV->tex->dibujarOscuro(vx, vy, vert->x, vert->y, 4);// cambio el color
	}
	else{
	// Renderea.
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);
	}

	delete vert;
}

void ItemRenderer::renderENES(EnemigoEstandar * item, float escala) {
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
	Vertexes * vert = obtenerVerticesEnemigo1(item->activeSprite);

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[ENES];

	// Renderea.
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);
	delete vert;
	vert = obtenerVerticesBola(item->spriteStun);
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);
	delete vert;
}

void ItemRenderer::renderENTIFUE(EnemigoTiraFuego * item, float escala) {
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
	Vertexes * vert = obtenerVerticesEnemigo2(item->activeSprite);

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[ENES];

	// Renderea.
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);
	delete vert;
	vert = obtenerVerticesBola(item->spriteStun);
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);
	delete vert;
}

void ItemRenderer::renderPoderNieve(poder * item,float escala){

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
		Vertexes * vert = obtenerVerticesPoder(item->activeSprite);

		// Obtiene la textura y su correspondiente rect para renderear.
		TexAndVertexes * TaV = textureMap[PODER1];

		// Renderea.
		TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);

		delete vert;
}

void ItemRenderer::renderPoderFuego(Fireball *item,float escala) {
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
	Vertexes * vert = obtenerVerticesPoder(item->activeSprite);

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[PODER2];

	// Renderea.
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);

	delete vert;
}

void ItemRenderer::renderSorpresa(Sorpresa * item,float escala){

		GLfloat vx[4];
		GLfloat vy[4];

		// Flippea la imagen si es necesario.
//		if (item->orientation == Personaje::LEFT){
//			vx[0] = vx[3] = (item->posicion.x - item->baseMayor / 2) * escala;
//			vy[0] = vy[1] = (item->posicion.y - item->altura / 2) * escala;
//			vx[1] = vx[2] = vx[0] + item->baseMayor * escala;
//			vy[2] = vy[3] = vy[0] + item->altura * escala;
//		} else {
			vx[1] = vx[2] = (item->posicion.x - item->baseMayor / 2) * escala;
			vy[0] = vy[1] = (item->posicion.y - item->altura / 2) * escala;
			vx[0] = vx[3] = vx[1] + item->baseMayor * escala;
			vy[2] = vy[3] = vy[0] + item->altura * escala;
//		}

		// Obtiene los vertices del sprite.
		Vertexes * vert = obtenerVerticesSorpresa(item->activeSprite);
		//Vertexes * vert = obtenerVerticesPoder(PODER1);

		// Obtiene la textura y su correspondiente rect para renderear.
		TexAndVertexes * TaV = textureMap[SORPRESAvida];

		// Si esta no esta conectado, se cambia el color a gris.
		// Renderea.
		TaV->tex->dibujar(vx, vy, vert->x, vert->y, 4);

		delete vert;
}

// Dibuja la metadata del juego: fondo.
void ItemRenderer::renderMetadataFondo(Metadata * item){

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

}

// Dibuja la metadata del juego: las vidas, puntaje, mensajes del servidor.
void ItemRenderer::renderMetadataHUD(Metadata * item){

	GLfloat vx[4]; GLfloat vy[4];

	// Obtiene la textura y su correspondiente rect para renderear las vidas.
	TexAndVertexes * TaV = textureMap[VIDAS1];

	for (int i = 0; i < 4; i++){

		// Calcula la posicion de los corazones de vida.
		vx[0] = vx[3] = 20 + 3*i * 54;
		vy[0] = vy[1] = 20;
		vx[1] = vx[2] = 68 + 3*i * 54;
		vy[2] = vy[3] = 68;

		// Renderea vidas.
		TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
	}

	std::string puntaje = SSTR("Puntaje: " << item->puntaje);

	// Calcula la posicion del puntaje
	vx[0] = vx[3] = 600;
	vy[0] = vy[1] = 600;
	vx[1] = vx[2] = 600 + 8 * puntaje.size();
	vy[2] = vy[3] = 628;

	TaV = textureMap[PUNTAJE1];
	SDL_Color c = {0, 0, 0, 255};
	TaV->tex->generarTexto("fuentes/Ubuntu-B.ttf", 30, puntaje, c);

	// Renderea puntaje.
	TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
	TaV->tex->eliminar();
	for (int i = 0; i < 4; i++){
		//posicion xvidas
		vx[0] = vx[3] = 20 + 1 * 54 + 3*i*54;
		vy[0] = vy[1] = 20;
		vx[1] = vx[2] = 68 + 1 * 54 + 3*i*54;
		vy[2] = vy[3] = 68;

		std::string xvidas = SSTR("X" << item->vidas[i]);
		TaV->tex->generarTexto("fuentes/Ubuntu-B.ttf", 30, xvidas, c);
		// Renderea vidas numero
	TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
	TaV->tex->eliminar();
	}
	for (int i = 0; i < 4; i++){
	//posicion nombre 1
		vx[0] = vx[3] = 20 + 3*i * 54;
		vy[0] = vy[1] = 70;
		vx[1] = vx[2] = 68	+ 3*i * 54 ;
		vy[2] = vy[3] = 98;

		std::string user = SSTR( item->users[i]);
		TaV->tex->generarTexto("fuentes/Ubuntu-B.ttf", 30, user, c);

	// Renderea nombre
		TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
		TaV->tex->eliminar();
	}
	// Analiza el mensaje.
	if (item->mensaje == "NOMESSAGE") return;

	//
	item->mensaje.replace(0, 9, "");
	std::replace( item->mensaje.begin(), item->mensaje.end(), '-', ' ');

	std::vector<std::string> buff;
	split(buff, item->mensaje, "&", no_empties);

	for (unsigned int i = 0; i < buff.size(); i++){

		// Calcula posicion mensaje.
		vx[0] = vx[3] = 50;
		vy[0] = vy[1] = 510 + i * 30;
		vx[1] = vx[2] = 50 + 8 * buff[i].size();
		vy[2] = vy[3] = 540 + i * 30;

		TaV = textureMap[PUNTAJE1];
		TaV->tex->generarTexto("fuentes/Ubuntu-B.ttf", 30, buff[i], c);

		// Renderea mensaje.
		TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
		TaV->tex->eliminar();
	}

}

void ItemRenderer::renderBola(BolaEnemigo * item, float escala){

	// Convierte los parametros de B2D en los necesarios para renderear el sprite.
	// Obtiene la seccion de la pantalla a renderear.
	GLfloat vx[20];
	GLfloat vy[20];

	for (int i = 0; i < 20; i++) {
		float thita = (2 * i * PI / 20) - (item->angulo);
		vx[i] = ( item->posicion.x - item->radio * cos(thita) ) * escala;
		vy[i] = ( item->posicion.y + item->radio * sin(thita) ) * escala;
	}

	// Obtiene la textura y su correspondiente rect para renderear.
	Vertexes * vert = obtenerVerticesNieve(item->activeSprite);

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[ENES];

	// Si esta no esta conectado, se cambia el color a gris.
	// Renderea.
	TaV->tex->dibujar(vx, vy, vert->x, vert->y, 20);

	delete vert;

}

void ItemRenderer::renderLaguna(Laguna* item, float escala){

	GLfloat vx[4];
	GLfloat vy[4];

	vx[1] = vx[2] = (item->posicion.x - item->baseMayor / 2) * escala;
	vy[0] = vy[1] = (item->posicion.y - item->altura / 2) * escala;
	vx[0] = vx[3] = vx[1] + item->baseMayor * escala;
	vy[2] = vy[3] = vy[0] + item->altura * escala;

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[spriteLAGUNA];

	// Renderea.
	TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
}

void ItemRenderer::renderAgujero(Agujero* item, float escala){

	GLfloat vx[4];
	GLfloat vy[4];

	vx[1] = vx[2] = (item->posicion.x - item->baseMayor / 2) * escala;
	vy[0] = vy[1] = (item->posicion.y - item->altura / 2) * escala;
	vx[0] = vx[3] = vx[1] + item->baseMayor * escala;
	vy[2] = vy[3] = vy[0] + item->altura * escala;

	// Obtiene la textura y su correspondiente rect para renderear.
	TexAndVertexes * TaV = textureMap[spriteLAGUNA];

	// Renderea.
	TaV->tex->dibujar(vx, vy, TaV->vertexes->x, TaV->vertexes->y, 4);
}

void ItemRenderer::renderGameOver(){

		GLfloat vx[4]; GLfloat vy[4];

		// Calcula la posicion del fondo
		// TODO: HARDCODEO!!!
		vx[0] = vx[3] = 0;
		vy[0] = vy[1] = 0;
		vx[1] = vx[2] = 720;
		vy[2] = vy[3] = 640;

		float vxTex[4]; float vyTex[4];

		// Calculo los vertices de la textura.
		vxTex[0] = vxTex[3] = 0;
		vyTex[0] = vyTex[1] = 0;
		vxTex[1] = vxTex[2] = 1;
		vyTex[2] = vyTex[3] = 1;

		TexAndVertexes * TaV = textureMap[GAMEOVER];

		// Renderea fondo.
		TaV->tex->dibujar(vx, vy, vxTex, vyTex, 4);

}

void ItemRenderer::renderSonido(Sonido * item){

	sonidosMap[item->sonido]->actualizarEstado();
	sonidosMap[item->sonido]->velocidad = item->velocidad;

	if( sonidosMap[item->sonido]->estaSonando() )
		sonidosMap[item->sonido]->apagar();

	if( sonidosMap[item->sonido]->velocidad != item->velocidad ){
		sonidosMap[item->sonido]->pausar();
		sonidosMap[item->sonido]->velocidad = item->velocidad;
	}

	sonidosMap[item->sonido]->reproducir();
}

// Dibuja un item del mundo.
void ItemRenderer::render(WorldItem * item, float escala){

	if (!textureMap.yaInicializado()) textureMap.init();

	if(!sonidosMap.yaInicializado()) sonidosMap.init();

	sonidosMap.actualizarEstados();

	item->aCoordenadasLocales(posicionCamara);

//	std::cout << "el tipo es: " << item->tipo << std::endl;

	switch(item->tipo){
	case NIEVE:
		renderPoderNieve((poder*)item,escala);
		break;
	case FUEGO:
		renderPoderFuego((Fireball*)item, escala);
		break;
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
	case ENEMIGOESTANDAR:
		renderENES((EnemigoEstandar*)item, escala);
		break;
	case ENEMIGOTIRAFUEGO:
		renderENTIFUE((EnemigoTiraFuego*)item, escala);
		break;
	case METADATAFONDO:
		tamanioMundo.x = ((Metadata*)item)->tamanioXMundo;
		tamanioMundo.y = ((Metadata*)item)->tamanioYMundo;
		posicionCamara.x = ((Metadata*)item)->posXCamara * tamanioMundo.x;
		posicionCamara.y = ((Metadata*)item)->posYCamara * tamanioMundo.y;
		renderMetadataFondo((Metadata*)item);
		break;
	case METADATAHUD:
		renderMetadataHUD((Metadata*)item);
		break;
	case SONIDO:
		renderSonido((Sonido*) item);
		break;
	case SORPRESA:
		renderSorpresa((Sorpresa*) item, escala);
		break;
	case BOLASNOW:
		renderBola((BolaEnemigo*) item, escala);
		break;
	case LAGUNA:
		renderLaguna((Laguna*) item, escala);
		break;
	case AGUJERO:
		renderAgujero((Agujero*) item, escala);
		break;
	}
}


