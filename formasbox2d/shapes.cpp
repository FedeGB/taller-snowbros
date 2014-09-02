/*
 * shapes.cpp
 *
 *  Created on: 30/08/2014
 *      Author: coco
 */

#include "shapes.h"

shapes::shapes() {
	_shape=NULL;
	// TODO Auto-generated constructor stub

}
shapes::shapes(std::string data,b2World *mundo,int num) {
	if(!b2d_objet(data,mundo,num))
		_shape=NULL;


}

shapes::~shapes() {
	// TODO Auto-generated destructor stub
}

bool shapes::b2d_objet(std::string data, b2World *mundo, int num){
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	b2PolygonShape poligon;
	if( get_node("estatico","objetos",data,num).compare("false"))
		b2dObjDef.type=b2_staticBody;
	else
		b2dObjDef.type=b2_dynamicBody;
	b2dObjDef.position.x=atof(get_node("x","objetos",data,num).c_str());
	b2dObjDef.position.y=atof(get_node("y","objetos",data,num).c_str());
	_shape=mundo->CreateBody(&b2dObjDef);
	int lados=num_lados(get_node("tipo","objetos",data,num));
	if	(lados==3){
		lados=atoi(get_node("lados","objetos",data,num).c_str());
	}
	switch(lados){
	case 0:
		return false;
	case 1: //1 solo lado  = circulo

		myFixtureDef.shape= &circle;
		circle.m_radius=atof(get_node("escala","objetos",data,num).c_str());
		_shape->CreateFixture(&myFixtureDef);
		break;
	case 4: // 4 lados caja
		poligon.SetAsBox(atof(get_node("alto","objetos",data,num).c_str())/2,atof(get_node("ancho","objeto",data).c_str())/2);
		myFixtureDef.shape = &poligon;
		_shape->CreateFixture(&myFixtureDef);
		break;
	default: // mas lados poligonos regulares
		b2Vec2 * point = new b2Vec2[lados];
		for(int i=0;i<lados;i++){
				point[i].Set(cos(2*i*PI/lados),sin(2*i*PI/lados));
				cout<<point[i].x<<" "<<point[i].y<<endl;
			}
	    poligon.Set(point, 3);
		myFixtureDef.shape = &poligon;
		_shape->CreateFixture(&myFixtureDef);
		break;

	}
	return true;
}

b2Body& shapes::getShape(){
	return *_shape;
}

//TODO no se si estas funciones van aca o ponerlas en una clase parser


int shapes::num_lados(std::string data){
	if(!data.compare("circulo"))
		return 1;
	if(!data.compare("rect"))
	    return 4;
	if(!data.compare("poli"))
		return 3;
	else
		return 0;


}
