
#include "shapes.h"

shapes::shapes() {
	_shape = NULL;
	_point = NULL;
	log = * Logger::Instancia();
	// TODO Auto-generated constructor stub
}

shapes::shapes(std::string data, b2World *mundo, int num) {
	log = * Logger::Instancia();
	if (!b2d_objet(data, mundo, num))
		_shape = NULL;
}

shapes::~shapes() {
	delete _shape;
	_shape = NULL;
	delete _point;
	_point = NULL;
	// TODO Auto-generated destructor stub
}

bool shapes::b2d_objet(std::string data, b2World *mundo, int num) {

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	b2PolygonShape poligon;

	if (get_node("estatico", "objetos", data, num,"false").compare("false"))
		b2dObjDef.type = b2_staticBody;
	else
		b2dObjDef.type = b2_dynamicBody;

	//posicion inicial
	b2dObjDef.position.x = atof(get_node("x", "objetos", data, num,"1").c_str());
	b2dObjDef.position.y = atof(get_node("y", "objetos", data, num,"1").c_str());
	b2dObjDef.angle = atoi(get_node("rot", "objetos", data, num,"0").c_str());

	//lo vinculo al mundo
	_shape = mundo->CreateBody(&b2dObjDef);

	//le doy forma
	int lados = num_lados(get_node("tipo", "objetos", data, num,"rect"));
	if (lados == 3)
		lados = atoi(get_node("lados", "objetos", data, num,"3").c_str());

	switch (lados) {//dependiendo del numero de lados
	case 0: //0 es error
		if (!log.abrirLog("shapes.log")) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return false;
				}
				log.escribirLog("ERROR", "No se definio ninguna forma");
				log.cerrarLog();
		return false;

	case 1: //1 solo lado  = circulo

		myFixtureDef.shape = &circle; //defino que es un circulo
		myFixtureDef.density = atof(
				get_node("masa", "objetos", data, num,"1").c_str());//le doy masa

		circle.m_radius = atof(
				get_node("escala", "objetos", data, num,"1").c_str());
		//y el tamaño
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma
		break;

	case 4: // 4 lados caja
		poligon.SetAsBox(
				atof(get_node("alto", "objetos", data, num,"1").c_str()) / 2,
				atof(get_node("ancho", "objeto", data,"1").c_str()) / 2); //le doy dimenciones
		myFixtureDef.shape = &poligon; //defino que es un poligono
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma
		break;

	default: // 3, 5 o mas lados poligonos regulares

		_point = new b2Vec2[lados]; //creo un vector con los vertices
		for (int i = 0; i < lados; i++) {
			point[i].Set(cos(2 * i * PI / lados), sin(2 * i * PI / lados));
		} //les asigno la posicion

		poligon.Set(point, lados);
		myFixtureDef.shape = &poligon;
		myFixtureDef.density = atof(
				get_node("masa", "objetos", data, num,"1").c_str()); //le asigno la masa
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma
		break;

	}
	return true;
}

b2Body& shapes::getShape() {
	return *_shape;
}// retorna una referencia al objeto de box2d

b2Body& shapes::getPoints() {
	return *_point;
}// retorna una referencia al objeto de box2d

//TODO no se si estas funciones van aca o ponerlas en una clase parser

int shapes::num_lados(std::string data) {
	if (!data.compare("circ"))
		return 1;
	if (!data.compare("rect"))
		return 4;
	if (!data.compare("poli"))
		return 3;
	else
		return 0;

}

