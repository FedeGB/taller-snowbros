/*
 * Texto.h
 *
 *  Created on: 21/10/2014
 *      Author: manuel
 */

#ifndef TEXTO_H_
#define TEXTO_H_

#include "../utiles/tipos.h"

class Texto : public ITexturizable{
public:
	Texto() {
		recuadro = new RectanguloDibujable();
		_tex = new Textura();
	}

	Texto(std::string fnt_path, int tam, std::string txt, SDL_Color c) {

		fuente_path = fnt_path;
		texto = txt;
		tamanio = tam;
		color = c;

		recuadro = new RectanguloDibujable();
		setPosicion(20.0f, 20.0f);
		setAnchoyAlto(12,1);

		_tex = new Textura();
		_tex->generarTexto(fuente_path, tamanio, texto, color);

		recuadro->setTex(_tex, 2.0, 1.0);
	}

	virtual ~Texto(){}

	void regenerar(){
		_tex->eliminar();
		_tex->generarTexto(fuente_path, tamanio, texto, color);
		recuadro->setTex(_tex, 1.0, 1.0);
	}

	void setFuente(std::string fnt_path){
		fuente_path = fnt_path;
		regenerar();
	}

	void setTexto(std::string txt){
		texto = txt;
		regenerar();
	}

	void setTamanio(int tam){
		tamanio = tam;
		regenerar();
	}

	void setColor(SDL_Color c){
		color = c;
		regenerar();
	}

	void setPosicion(float32 x, float32 y){
		recuadro->setPosicion(x, y);
	}

	void setAnchoyAlto(float32 w, float32 h){
		recuadro->setDimensiones(h, w);
	}

	void dibujar(){
		recuadro->render();
	}

private:
	std::string fuente_path;
	std::string texto;
	int tamanio;
	SDL_Color color;
	RectanguloDibujable* recuadro;
};

#endif /* TEXTO_H_ */
