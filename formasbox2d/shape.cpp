#include "shape.h"
#include "../modelo/formas/CirculoDibujable.h"
#include "../modelo/formas/PoligonoDibujable.h"
#include "../modelo/formas/RectanguloDibujable.h"
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
		myFixtureDef.density =get_node("masa", "objetos", data, num,1.0f); //le doy masa

		circle.m_radius =get_node("escala", "objetos", data, num,1.0f);	//y el tamaño
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma

		// Determina el tipo de figura para poder dibujarla.
		figura = new CirculoDibujable();
		figura->setRadio(circle.m_radius);

		break;
	}
	case 4: // 4 lados caja
	{
		float halfHeight = get_node("alto", "objetos", data, num,1.0f) / 2;
		float halfWidth = get_node("ancho", "objetos", data, num,1.0f) / 2;
		poligon.SetAsBox(halfHeight, halfWidth); //le doy dimensiones
		myFixtureDef.shape = &poligon; //defino que es un poligono
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma

		// Determina el tipo de figura para poder dibujarla.
		figura = new PoligonoDibujable();

		float modulo = sqrt( pow(halfWidth, 2) + pow(halfHeight, 2) );
		float thita = b2dObjDef.angle * 0.017469944f + atan( halfHeight / halfWidth );
		float xaux = modulo * cos(thita);
		float yaux = modulo * sin(thita);
		float thita2 = - b2dObjDef.angle * 0.017469944f + atan( halfHeight / halfWidth );
		float xaux2 = modulo * cos(thita2);
		float yaux2 = modulo * sin(thita2);

		Sint16* vx = new Sint16[2];
		vx[0] = b2dObjDef.position.x - xaux;
		vx[1] = b2dObjDef.position.x + xaux2;
		vx[2] = b2dObjDef.position.x + xaux;
		vx[3] = b2dObjDef.position.x - xaux2;

		Sint16* vy = new Sint16[2];
		vy[0] = b2dObjDef.position.y - yaux;
		vy[1] = b2dObjDef.position.y - yaux2;
		vy[2] = b2dObjDef.position.y + yaux;
		vy[3] = b2dObjDef.position.y + yaux2;

		figura->setVertices(vx, vy, 4);

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
		myFixtureDef.density =get_node("masa", "objetos", data, num,1.0f); //le asigno la masa
		_shape->CreateFixture(&myFixtureDef); //le asigno la forma

		// Determina el tipo de figura para poder dibujarla.
		figura = new PoligonoDibujable();

		Sint16* vx = new Sint16[lados];
		Sint16* vy = new Sint16[lados];
		for (int i = 0; i < lados; i++)	{
			vx[i] = _shape->GetWorldPoint(_point[i]).x;
			vy[i] = _shape->GetWorldPoint(_point[i]).y;
		}

		figura->setVertices(vx, vy, lados);

		break;

	}

	// Determina el color de la figura.
	std::string hexT;
	hexT.assign(get_node("color", "objetos", data, num, "FF0000"));
	std::stringstream s(hexT.substr(0, 2));
	int R; s >> std::hex >> R;
	int G; s.clear(); s.str(hexT.substr(2, 2)); s >> std::hex >> G;
	int B; s.clear(); s.str(hexT.substr(4, 2)); s >> std::hex >> B;
	SDL_Color color = { R , G , B , 255 };
	figura->color(color);

	// Determina los demas parametros de la figura.
	figura->posicion(b2dObjDef.position.x,b2dObjDef.position.y);
	figura->angulo(b2dObjDef.angle);
	figura->esEstatico(true);

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
	figura->render();
}

void shape::setRenderer(SDL_Renderer* r){
	figura->setRenderer(r);
}
