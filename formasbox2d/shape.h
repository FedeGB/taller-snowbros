#ifndef SHAPES_H_
#define SHAPES_H_

#define PI 3.14159265
#include <Box2D/Box2D.h>
#include <string>
#include <cmath>
#include "../parser/parser.h"
#include "../utiles/Logger.h"
#include "../modelo/ObjetoDibujable.h"

//diccionario
enum tipo{CIRCULO=1,RECTANGULO=4,POLIGONO=3,IRREGULAR=5};
const string formas[6]={"","circulo","","poligono","rectangulo","irregular"};

class shape: public IDibujable {
public:
	shape();
	shape(std::string data,b2World* mundo, int num);
	virtual ~shape();
	b2Body& getShape();
	b2Vec2& getPoints();
	int getLados();
	virtual void render();
	virtual void setRenderer(SDL_Renderer* r);



private:
	bool b2d_objet(std::string data,b2World *mundo,int num);
	int num_lados(std::string data);
	b2Body *_shape;
	b2Vec2 *_point;
	int nLados;
	b2World *world;
	bool update_Position();//cambia la posicion de la imagen
	ObjetoDibujable *figura;
};

#endif /* SHAPES_H_ */

