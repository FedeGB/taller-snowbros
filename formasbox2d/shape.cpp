#include "shape.h"
#include "../modelo/formas/CirculoDibujable.h"
#include "../modelo/formas/PoligonoDibujable.h"
#include "../modelo/formas/RectanguloDibujable.h"
#include "../utiles/tipos.h"

#include <sstream>


shape::shape() {
	_shape = NULL;
	_point = NULL;
	nLados=0;
	world=NULL;
	figura = NULL;
	// TODO Auto-generated constructor stub
}

shape::shape(std::string data, b2World *mundo, int num) {
	this->world=world;
	if (!b2d_objet(data, mundo, num))
		_shape = NULL;
}

shape::~shape() {
	//world->DestroyBody(_shape);
	// TODO Auto-generated destructor stub
}

bool shape::b2d_objet(std::string data, b2World *mundo, int num) {

	Logger& log= *Logger::Instancia();
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	b2PolygonShape poligon;

	if (get_node("estatico", "objetos", data, num,false))
		b2dObjDef.type = b2_staticBody;
	else b2dObjDef.type = b2_dynamicBody;

	//posicion inicial
	b2dObjDef.position.x = get_node("x", "objetos", data, num,1.0f);
	b2dObjDef.position.y = get_node("y", "objetos", data, num,1.0f);
	b2dObjDef.angle = get_node("rot", "objetos", data, num,0.0f) * DEGTORAD;
	if (b2dObjDef.type == b2_dynamicBody) {
		//b2dObjDef.angularVelocity = 10;
		b2dObjDef.linearDamping = 0.1;
		//b2dObjDef.angularDamping = 1;
	} else {

	}

	//lo vinculo al mundo
	_shape = mundo->CreateBody(&b2dObjDef);

	//le doy forma
	int lados = num_lados(get_node("tipo", "objetos", data, num,"rect"));

	nLados=lados;
	switch (lados) {//dependiendo del numero de lados
	case 0: //0 es error
		if (!log.abrirLog(SHAPESLOG)) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return false;
				}
				log.escribirLog("ERROR", "No se definio ninguna forma");
				log.cerrarLog();
		return false;

	case 1: //1 solo lado  = circulo
	{
		myFixtureDef.shape = &circle; //defino que es un circulo
		circle.m_radius =get_node("escala", "objetos", data, num,1.0f);	//y el tamaño

		// Determina el tipo de figura para poder dibujarla.
		CirculoDibujable * circ = new CirculoDibujable();
		circ->setRadio(circle.m_radius);
		figura = circ;

		break;
	}
	case 4: // 4 lados caja
	{
		float32 halfHeight = get_node("alto", "objetos", data, num,1.0f) / 2;
		float32 halfWidth = get_node("ancho", "objetos", data, num,1.0f) / 2;
		poligon.SetAsBox(halfWidth, halfHeight); //le doy dimensiones
		myFixtureDef.shape = &poligon; //defino que es un poligono
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma

		// Determina el tipo de figura para poder dibujarla.
		RectanguloDibujable * rect = new RectanguloDibujable();
		rect->setDimensiones(halfHeight * 2, halfWidth * 2);
		figura = rect;

		break;
	}
	case 5:{ // poligonos irregulares

		_point = new b2Vec2[lados];
		float base=get_node("base","objetos",data,num,1.0f);
		float tapa=get_node("tapa","objetos",data,num,1.0f);
		float alto=get_node("alto","objetos",data,num,1.0f);
		float desp=get_node("desp","objetos",data,num,1.0f);//desplazamiento
		_point[0].Set(-1.0*base/2,0.0);
		_point[1].Set(base/2,0.0);
		_point[2].Set((tapa/2)+(desp/2),alto);
		_point[3].Set((-1.0*tapa/2)+(desp/2),alto);
		poligon.Set(_point, lados);
		myFixtureDef.shape = &poligon;
		myFixtureDef.density =get_node("masa", "objetos", data, num,1.0f);
		_shape->CreateFixture(&myFixtureDef);
		break;
	}

	default: // 3, 5 o mas lados poligonos regulares

		lados = get_node("lados", "objetos", data, num,3);

		float escala = get_node("escala", "objetos", data, num,1.0f);
		_point = new b2Vec2[lados]; //creo un vector con los vertices
		for (int i = 0; i < lados; i++) {
			float angulo = (2 * i * PI / lados) - (b2dObjDef.angle * 0.017469944f);
			_point[i].Set(escala * cos( angulo ), escala * sin( angulo ));
		} //les asigno la posicion

		poligon.Set(_point, lados);
		myFixtureDef.shape = &poligon;

		// Determina el tipo de figura para poder dibujarla.
		PoligonoDibujable * poli = new PoligonoDibujable();

		poli->setNumVertices(lados);
		poli->setEscala(escala);

		figura = poli;

		break;

	}

	myFixtureDef.density = get_node("masa", "objetos", data, num,1.0f); //le doy masa
	myFixtureDef.restitution = 0.35f;
	//myFixtureDef.friction = 0.1f;
	_shape->CreateFixture(&myFixtureDef); //le asigno la forma

	// Determina los parametros basicos de la figura.

	figura->setColor((get_node("color", "objetos", data, num, "FF0000")));
	figura->setPosicion(b2dObjDef.position.x,b2dObjDef.position.y);
	figura->setAngulo(b2dObjDef.angle);

	return true;
}

b2Body& shape::getShape() {
	return *_shape;
}// retorna una referencia al objeto de box2d

b2Vec2& shape::getPoints() {
	return *_point;
}// retorna una referencia a los vertices originales de los objetos

//TODO no se si estas funciones van aca o ponerlas en una clase parser

int shape::num_lados(std::string data) {
	if (!data.compare("circ")){
		this->_shape->SetUserData( new int(CIRCULO));
		return 1;
	}
	if (!data.compare("rect")){
				this->_shape->SetUserData(new int(RECTANGULO));
				return 4;
			}
	if (!data.compare("poli")){
				this->_shape->SetUserData(new int(POLIGONO));
				return 3;
			}
	if (!data.compare("irreg")){
		this->_shape->SetUserData(new int(IRREGULAR));
		return 5;
			}
	else
		return 0;

}

int shape::getLados(){
	return nLados;
}

void shape::render(){
	// SOLO FUNCIONA PARA RECTANGULOS Y CIRCULOS !! !! ! !! ! ! ! !1 1 1 1 1 1 1one one one one one
	figura->setAngulo(_shape->GetAngle());
	figura->setPosicion(_shape->GetPosition());
	figura->render();

	//std::cout << "el angulo es: " << _shape->GetAngle() << std::endl;
}

void shape::setRenderer(SDL_Renderer* r){
	figura->setRenderer(r);
}
