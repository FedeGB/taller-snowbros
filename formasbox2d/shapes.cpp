#include "shapes.h"

shapes::shapes() {
	_shape = NULL;
	_point = NULL;
	nLados=0;
	world=NULL;
	// TODO Auto-generated constructor stub
}

shapes::shapes(std::string data, b2World *mundo, int num) {
	this->world=world;
	if (!b2d_objet(data, mundo, num))
		_shape = NULL;
}

shapes::~shapes() {
	world->DestroyBody(_shape);
	// TODO Auto-generated destructor stub
}

bool shapes::b2d_objet(std::string data, b2World *mundo, int num) {

	Logger& log= *Logger::Instancia();
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	b2PolygonShape poligon;

	if (get_node("estatico", "objetos", data, num,false))
		b2dObjDef.type = b2_staticBody;
	else
		b2dObjDef.type = b2_dynamicBody;

	//posicion inicial
	b2dObjDef.position.x = get_node("x", "objetos", data, num,1.0f);
	b2dObjDef.position.y = get_node("y", "objetos", data, num,1.0f);
	b2dObjDef.angle = get_node("rot", "objetos", data, num,0.0f);

	//lo vinculo al mundo
	_shape = mundo->CreateBody(&b2dObjDef);

	//le doy forma
	int lados = num_lados(get_node("tipo", "objetos", data, num,"rect"));
	if (lados == 3)
		lados = get_node("lados", "objetos", data, num,3);

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

		myFixtureDef.shape = &circle; //defino que es un circulo
		myFixtureDef.density =get_node("masa", "objetos", data, num,1.0f);//le doy masa

		circle.m_radius =get_node("escala", "objetos", data, num,1.0f);
		//y el tamaño
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma
		break;

	case 4: // 4 lados caja
		poligon.SetAsBox(get_node("alto", "objetos", data, num,1.0f)/ 2,get_node("ancho", "objetos", data, num,1.0f)/ 2); //le doy dimenciones
		myFixtureDef.shape = &poligon; //defino que es un poligono
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma
		break;

	case 5:{
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
		break;}

	default: // 3, 5 o mas lados poligonos regulares

		_point = new b2Vec2[lados]; //creo un vector con los vertices
		for (int i = 0; i < lados; i++) {
			_point[i].Set(cos(2 * i * PI / lados), sin(2 * i * PI / lados));
		} //les asigno la posicion

		poligon.Set(_point, lados);
		myFixtureDef.shape = &poligon;
		myFixtureDef.density =get_node("masa", "objetos", data, num,1.0f); //le asigno la masa
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma
		break;

	}
	return true;
}

b2Body& shapes::getShape() {
	return *_shape;
}// retorna una referencia al objeto de box2d

b2Vec2& shapes::getPoints() {
	return *_point;
}// retorna una referencia a los vertices originales de los objetos

//TODO no se si estas funciones van aca o ponerlas en una clase parser

int shapes::num_lados(std::string data) {
	if (!data.compare("circ"))
		return 1;
	if (!data.compare("rect"))
		return 4;
	if (!data.compare("poli"))
		return 3;
	if (!data.compare("irreg"))//trapecio o paralelogramo
			return 5;
	else
		return 0;

}

int shapes::getLados(){
	return nLados;
}
