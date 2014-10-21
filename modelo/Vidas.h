/*
 * Vidas.h
 *
 *  Created on: 20/10/2014
 *      Author: manuel
 */

#ifndef VIDAS_H_
#define VIDAS_H_

#include "formas/RectanguloDibujable.h"

class Vidas : public ITexturizable{
public:
	Vidas() : cant_vidas(5){

		_tex = new Textura();
		_tex->generar("imagenes/vida2.png");

		recuadro = new RectanguloDibujable[cant_vidas];

		for(int i=0; i<cant_vidas; i++ ){
			recuadro[i].setFijo(true);
			recuadro[i].setEscalaCamara(10);
			recuadro[i].setPosicion(3+i*5, 3.0f);
			recuadro[i].setDimensiones(5.0f, 5.0f);
			recuadro[i].setColor("FF00AA");
			recuadro[i].setTex(_tex, 1.0, 1.0);
		}

	}
	virtual ~Vidas(){}

	void render() {
		for(int i=0; i<cant_vidas; i++)
			recuadro[i].render();
	}
private:
	std::string path;
	int cant_vidas;

	RectanguloDibujable* recuadro;

};


#endif /* VIDAS_H_ */
