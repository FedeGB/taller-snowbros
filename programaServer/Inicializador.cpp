/*
 * Inicializador.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: rodrizapico
 */

#include "Inicializador.h"

#include <unistd.h>

int isNumber(const char* string);
bool file_exist( string f);
bool ipValid(string ip);
bool isValidIPNumber(string token);
bool isValidPort(int puerto);

// Clase encargada de inicializar varios modulos del juego.
Inicializador::Inicializador(){

}

Inicializador::~Inicializador(){

}

// Valida los parametros iniciales. Si son validos, los carga como
// informacion publica.
bool Inicializador::validarParametros(int argc, char** argv){

    // Process command line arguments
	int opt, cflag, pflag, iflag, port;
	opt = cflag = pflag = iflag = 0;
	port = 0;
	std::string path (" "); // path al config
	std::string ip (""); // IP en el que escucha.

	if ( argc < 5 || argc > 7 ) {
		printf("Uso: %s -c <JSON Mapa> -p <Puerto> -i [<IP Opcional>]\n", argv[0]);
		return false;
	}

    while( (opt = getopt(argc, argv, "c:p:i:")) != -1 ) {
       	switch(opt) {
       	case 'c':

       		cflag = 1;
       		path = std::string(optarg);
       		break;
       	case 'p':

       		if(!isNumber(optarg)) {
       			printf("El puerto %s especificado debe ser un numero\n", optarg);
       			exit(-1);
       		}
       		pflag = 1;
       		port = atoi(optarg); // Puerto en el que escucha a las conexiones.
       		break;
       	case 'i':

       		iflag = 1;
       		ip = std::string(optarg);
       		break;
       	case '?':
       		if(optopt == 'c') {
       			printf("Al parametro -c le falta el path\n");
       		}
       		else if(optopt == 'p') {
       			printf("Al parametro -p le falta especificar el puerto\n");
       		}
       		else if(optopt == 'i') {
       			printf("Al parametro -i le faltaria especificar una ip, si no quiere especificar una, no utilice el argumento -i\n");
       		}
       		else {
       			printf("Parametro -%c no reconocido\n", optopt);
       		}
       		return false;
       	default:
       		printf("Error no esperado en el procesamiento de comandos\n");
       		return false;
       	}
    }

    if (!cflag) {
     	printf("No se especifico archivo de configuracion\n");
       	// Seteando archivo default
       	path = "defaultConfig.json";
    }
    if (!file_exist(path)){
        //printf("no existe el archivo: ",path," de configuracion, el programa terminara\n");
    	return false;
    }

    if (!pflag) {
       printf("No se especifico puerto con el comando -p\n");
       return -1;
    } else {
    	if(!isValidPort(port)) {
    		printf("El puerto %d no es valido, ingrese un puerto entre 1024 y 49151\n", port);
    		return false;
    	}
    }

    if (iflag) {
    	if(!ipValid(ip)){
    		printf("la ip ingresada es invalida\n");
    		return false;
    	}
    }

	LocalizadorDeServicios::obtenerInformacionPublica()->puerto = port;
	LocalizadorDeServicios::obtenerInformacionPublica()->archivoConfiguracion = path;
	LocalizadorDeServicios::obtenerInformacionPublica()->IP = ip;

    return true;
}










//////////////////////////////////////////////////////////////////////
//                                                                  //
//        FUNCIONES PARA VERIFICAR PARAMETROS INICIALES.            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

int isNumber(const char* string) {
	std::string var;
	if(!string) {
		return 0;
	} else {
		var  = string;
	}
	for(unsigned int i = 0; i < var.length(); i++) {
		if(!isdigit(var[i])) {
			return 0;
		}
	}
	return 1;
}

bool file_exist(const string  f){
    ifstream file;
    file.open(f.c_str());
    if(file.fail())
        return false;
    file.close();
    return true;
}

bool ipValid(string ip){
	if(ip == "localhost") return true;
	if(ip.length()<8 || ip.length()>16)
		return false;
	string token ,temp=ip;
	while (token != temp){
		token = temp.substr(0,temp.find_first_of("."));
		temp = temp.substr(temp.find_first_of(".") + 1);
		if(!isValidIPNumber(token)) {
			return false;
		}
	}
	return true;
}

bool isValidIPNumber(string token) {
	if(isNumber(token.c_str())) {
		int number = atoi(token.c_str());
		if (number < 0 || number > 255) {
			return false;
		}
	} else {
		return false;
	}
	return true;
}

bool isValidPort(int puerto) {
	if(puerto < 1024 || puerto > 49151) {
		return false;
	}
	return true;
}

bool Inicializador::loadInitialValues(std::string configFile, std::string& sConfig) {
	Logger& log = *Logger::Instancia();
	//abre el json y lo carga a un string
	fstream fConfig;
	fConfig.open(configFile.c_str(), ios_base::in);
	if (!fConfig.is_open()) {
		if (!log.abrirLog(MAINLOG)) {
			log.crearLogs();
			std::cout << "Error al abrir archivo de log " << MAINLOG
					<< ", creando..." << std::endl;
			if (!log.abrirLog(MAINLOG)) {
				std::cout << "No se pudo crear el archivo de log.";
				return false;
			}
		}

		log.escribirLog(WARNING,
				"No se pudo encontrar o abrir el archivo de configuracion. Cargando mapa por defecto.");
		log.cerrarLog();

		fConfig.open("defaultConfig.json", ios_base::in);
		if (!fConfig.is_open()) {
			if (!log.abrirLog(MAINLOG)) {
				log.crearLogs();
				std::cout << "Error al abrir archivo de log " << MAINLOG
						<< ", creando..." << std::endl;
				if (!log.abrirLog(MAINLOG)) {
					std::cout << "No se pudo crear el archivo de log.";
					return false;
				}
			}

			log.escribirLog(ERROR,
					"No se pudo encontrar o abrir el archivo de configuracion por defecto.");
			log.cerrarLog();
			return false;
		}

	}
	std::string newStr((std::istreambuf_iterator<char>(fConfig)),
			std::istreambuf_iterator<char>());
	sConfig = newStr;
	fConfig.close();

	if (!parsingOk(sConfig)) {
		fConfig.open("defaultConfig.json", ios_base::in);
		if (!fConfig.is_open()) {
			if (!log.abrirLog(MAINLOG)) {
				log.crearLogs();
				std::cout << "Error al abrir archivo de log " << MAINLOG
						<< ", creando..." << std::endl;
				if (!log.abrirLog(MAINLOG)) {
					std::cout << "No se pudo crear el archivo de log.";
					return false;
				}
			}

			log.escribirLog("ERROR",
					"No se pudo encontrar o abrir el archivo default.json");
			log.cerrarLog();
			return false;
		}
		std::string newStr((std::istreambuf_iterator<char>(fConfig)),
				std::istreambuf_iterator<char>());
		sConfig = newStr;
		fConfig.close();
	}

	return true;
}

void worldInit(b2World ** worldB2D, ContactListener * contactListener) {

	b2Vec2 gravedad(0, 35);
	*worldB2D = new b2World(gravedad);

	(*worldB2D)->SetContactListener(contactListener);

	return;
}







int num_lados(std::string data) {
	if (!data.compare("circ"))
		return 1;
	if (!data.compare("rect"))
		return 4;
	if (!data.compare("laguna"))
		return 4;
	if (!data.compare("agujero"))
		return 4;
	if (!data.compare("poli"))
		return 3;
	if (!data.compare("irreg"))
		return 5;
	else
		return 0;
}

b2Body * createObject(std::string data, b2World ** wB2D, int num) {

	Logger& log = *Logger::Instancia();
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	b2PolygonShape poligon;

	if (get_node("estatico", "objetos", data, num, false))
		b2dObjDef.type = b2_staticBody;
	else {
		b2dObjDef.type = b2_dynamicBody;
		b2dObjDef.bullet = true;
	}

	//posicion inicial
	b2dObjDef.position.x = get_node("x", "objetos", data, num, 1.0f);
	b2dObjDef.position.y = get_node("y", "objetos", data, num, 1.0f);
	b2dObjDef.angle = get_node("rot", "objetos", data, num, 0.0f) * DEGTORAD;

	//lo vinculo al mundo
	b2Body *_shape = (*wB2D)->CreateBody(&b2dObjDef);

	//le doy forma
	int lados = num_lados(get_node("tipo", "objetos", data, num, "rect"));
	//nLados=lados;
	switch (lados) { //dependiendo del numero de lados
	case 0: //0 es error
		if (!log.abrirLog(SHAPESLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog(ERROR, "El tipo de forma '" + get_node("tipo", "objetos", data, num,"rect") + "' no existe.");
		log.cerrarLog();
		(*wB2D)->DestroyBody(_shape);
		return NULL;

	case 1: //1 solo lado  = circulo
	{
		circle.m_radius = get_node("escala", "objetos", data, num, 1.0f); //defino el tamaño
		myFixtureDef.shape = &circle; //defino que es un circulo
		break;
	}
	case 4: // 4 lados caja
	{
		float32 halfHeight = get_node("alto", "objetos", data, num, 1.0f) / 2;
		float32 halfWidth = get_node("ancho", "objetos", data, num, 1.0f) / 2;
		poligon.SetAsBox(halfWidth, halfHeight); //le doy dimensiones
		myFixtureDef.shape = &poligon; //defino que es un poligono

		if( get_node("esLaguna", "objetos", data, num, false) ){
			_shape->SetBullet(false);
			myFixtureDef.isSensor = true;
			break;
		}
		if( get_node("esAgujero", "objetos", data, num, false) ){
			std::cout << "es un agujero" << std::endl;
			_shape->SetBullet(false);
			myFixtureDef.isSensor = true;
			break;
		}

		b2FixtureDef borderSensFix;
		b2PolygonShape polygon;

		break;
	}
	case 5: { // poligonos irregulares

		float base = get_node("base", "objetos", data, num, 1.0f);
		float tapa = get_node("tapa", "objetos", data, num, 1.0f);
		float alto = get_node("alto", "objetos", data, num, 1.0f);
		float desp = get_node("desp", "objetos", data, num, 1.0f); //desplazamiento

		b2Vec2 *_point = new b2Vec2[lados];
		float32 centroX = ((2 * tapa * desp + base * desp + base * tapa
				+ pow(base, 2) + pow(tapa, 2)) / (3 * (base + tapa)));
		float32 centroY = ((alto * (base + 2 * tapa)) / (3 * (base + tapa)));
		_point[0].Set(-centroX, centroY);
		_point[1].Set(-centroX + base, centroY);
		_point[2].Set(-centroX + desp, centroY - alto);
		_point[3].Set(-centroX + desp + tapa, centroY - alto);
		poligon.Set(_point, 4);
		myFixtureDef.shape = &poligon;

		break;
	}

	default: // 3, 5 o mas lados poligonos regulares

		lados = get_node("lados", "objetos", data, num, 3);
		float escala = get_node("escala", "objetos", data, num, 1.0f);

		b2Vec2 * _point = new b2Vec2[lados]; //creo un vector con los vertices
		for (int i = 0; i < lados; i++) {
			float angulo = (2 * i * PI / lados); //- (b2dObjDef.angle * 0.017469944f);
			_point[i].Set(escala * cos(angulo), escala * sin(angulo));
		} //les asigno la posicion

		poligon.Set(_point, lados);
		myFixtureDef.shape = &poligon;

		break;

	}

	if (b2dObjDef.type == b2_dynamicBody) {
		myFixtureDef.density = get_node("masa", "objetos", data, num, 1.0f); //le doy masa
		myFixtureDef.restitution = 0.15f;
		//myFixtureDef.friction = 0.1f;
	}

	myFixtureDef.friction = get_node("friccion", "objetos", data, num, 0.3f);

	/*if(b2dObjDef.type == b2_staticBody)
		if(myFixtureDef.friction == 0)
			figura->hielo=true;*/
	b2Fixture * shapeFixture = _shape->CreateFixture(&myFixtureDef); //le asigno la forma
	if (b2dObjDef.type == b2_dynamicBody) shapeFixture->SetUserData((void*) DINAMICO);
	else {
		shapeFixture->SetUserData((void*) ESTATICO);
	}

	//Me fijo si el objeto que creo es atravesable.
	if (get_node("atravesable", "objetos", data, num, false)) shapeFixture->SetUserData((void*) ATRAVESABLE);

	// me fijo si es laguna
	if (get_node("esLaguna", "objetos", data, num, false)) shapeFixture->SetUserData((void*) sensorLAGUNA);

	// me fijo si es agujero
	if (get_node("esAgujero", "objetos", data, num, false)) {
		std::cout << "setteando userdata" << std::endl;
		shapeFixture->SetUserData((void*) sensorAGUJERO);
	}

	return _shape;
}

b2Body * createEnemy(std::string data, b2World ** wB2D, int num) {
	Logger& log = *Logger::Instancia();
	std::string tipo = get_node("tipo", "objetos", data, num, "est");
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;
	b2dObjDef.type = b2_dynamicBody;
	float32 halfHeight = get_node("alto", "objetos", data, num, 2.8f) / 2;
	float32 halfWidth = get_node("ancho", "objetos", data, num, 2.4f) / 2;
	float32 en_x = get_node("x", "objetos", data, num, 5.0f);
	float32 en_y = get_node("y", "objetos", data, num, 10.0f);
	b2Body* enB2D = NULL;
	//worlditem_t type = ENEMIGOESTANDAR;
	float32 anchoMaximo = get_node("ancho-un", "escenario", data, 10.0f);
	float32 altoMaximo = get_node("alto-un", "escenario", data, 10.0f);
	if( (en_x > anchoMaximo) | (en_y > altoMaximo) ){
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog(WARNING, "No se puede inicializar al personaje fuera del escenario. Seteado por default al medio del escenario.");
		log.cerrarLog();
		en_x = ( anchoMaximo * 0.5 ); en_y = ( altoMaximo * 0.5 );
	}
	b2dObjDef.position.Set(en_x, en_y);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;
	b2dObjDef.bullet = true;
	//lo vinculo al mundo
	enB2D = (*wB2D)->CreateBody(&b2dObjDef);
	//le doy forma
	b2Vec2 v(0,(halfHeight*-0.1));

	polygon.SetAsBox(halfWidth*0.7, halfHeight*0.7,v,0); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.density =  get_node("masa", "objetos", data, num, 20.0f); //le doy masa
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=0.2;
	b2Fixture * bodyFixture = enB2D->CreateFixture(&myFixtureDef); //le asigno la forma
	bodyFixture->SetUserData( (void*)ENEMIGO );

	//costados sin friccion
	v.x=-halfWidth*0.7;
	polygon.SetAsBox(halfWidth*0.15, halfHeight*0.7,v,0); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.density=0;
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=0;
	b2Fixture* fixture = enB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData( (void*)ENEMIGO ); // CAMBIAR ESTA DATA POR NUMEROS UNICOS POR CADA ENEMIGO NUEVO (ATRIBUTO DE CLASE)

	//costados sin friccion
	v.x=halfWidth*0.7;
	polygon.SetAsBox(halfWidth*0.15, halfHeight*0.7,v,0); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=0;
	fixture = enB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData( (void*)ENEMIGO );

	//pies
	v.x=0;
	v.y=halfHeight*0.75;
	polygon.SetAsBox(halfWidth*0.4, halfHeight*0.1, v, 0);
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.density = 1.0f; //le doy masa
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=20.0f;
	fixture = enB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData( (void*)PIESEN  );

	// Agrego el sensor para saltos
	polygon.SetAsBox(halfWidth * 0.3, 0.15f, b2Vec2(0,halfHeight), 0);
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.isSensor = true;
	myFixtureDef.density = 1.0f; //le doy masa
	b2Fixture* footSensorFixture = enB2D->CreateFixture(&myFixtureDef);
	footSensorFixture->SetUserData( (void*)PIESEN );

    return enB2D;
}

b2Body * createPJ(std::string configFile, b2World ** worldB2D, int numeroObjeto){
	Logger& log = *Logger::Instancia();
	std::string data;
	bool statusOK = true;
	statusOK = Inicializador::loadInitialValues(configFile, data);
	if (!statusOK) return NULL;

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;

	// Parametros iniciales.
	b2dObjDef.type = b2_dynamicBody;
	//std::string campoPJ = SSTR("personaje" << numeroUsuario);

	float32 pj_x = get_node("x", "objetos", data, numeroObjeto, 5.0f);
	float32 pj_y = get_node("y", "objetos", data, numeroObjeto, 10.0f);

	float32 anchoMaximo = get_node("ancho-un", "escenario", data, 10.0f);
	float32 altoMaximo = get_node("alto-un", "escenario", data, 10.0f);

	// si la posicion del persona esta fuera del escenario, entonces lo posicionamos en el medio
	if( (pj_x > anchoMaximo) | (pj_y > altoMaximo) ){
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog(WARNING, "No se puede inicializar al personaje fuera del escenario. Seteado por default al medio del escenario.");
		log.cerrarLog();
		pj_x = ( anchoMaximo * 0.5 ); pj_y = ( altoMaximo * 0.5 );
	}

	b2dObjDef.position.Set(pj_x, pj_y);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;
	b2dObjDef.bullet = true;

	//lo vinculo al mundo
	b2Body * pjB2D = (*worldB2D)->CreateBody(&b2dObjDef);

	//le doy forma
	float32 halfHeight = get_node("alto", "objetos", data, numeroObjeto, 2.4f) / 2;
	float32 halfWidth = get_node("ancho", "objetos", data, numeroObjeto, 2.2f) / 2;
	b2Vec2 v(0,(halfHeight*-0.1));
	polygon.SetAsBox(halfWidth*0.7, halfHeight*0.7,v,0); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.density =  get_node("masa", "objetos", data, numeroObjeto, 20.0f); //le doy masa
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=0.2;
	b2Fixture * bodyFixture = pjB2D->CreateFixture(&myFixtureDef); //le asigno la forma
	bodyFixture->SetUserData( (void*)PERSONAJE );


	//costados sin friccion
	v.x=-halfWidth*0.7;
	polygon.SetAsBox(halfWidth*0.15, halfHeight*0.7,v,0); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono;
	myFixtureDef.density=0;
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=0;
	b2Fixture* fixture = pjB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData( (void*)PERSONAJE );

	//costados sin friccion
	v.x=halfWidth*0.7;
	polygon.SetAsBox(halfWidth*0.15, halfHeight*0.7,v,0); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=0;
	fixture = pjB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData( (void*)PERSONAJE );

	//pies
	v.x=0;
	v.y=halfHeight*0.75;
	polygon.SetAsBox(halfWidth*0.4, halfHeight*0.1, v, 0);
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.density = 1.0f; //le doy masa
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction=2.0f;
	fixture = pjB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData( (void*)PERSONAJE );

    // Agrego el sensor para saltos
    polygon.SetAsBox(halfWidth * 0.3, 0.15f, b2Vec2(0,halfHeight), 0);
	myFixtureDef.shape = &polygon; //defino que es un poligono
    myFixtureDef.isSensor = true;
	myFixtureDef.density = 1.0f; //le doy masa
    b2Fixture* footSensorFixture = pjB2D->CreateFixture(&myFixtureDef);
    footSensorFixture->SetUserData( (void*)PIESPJ );

    // Agrego el sensor para empujar
    polygon.SetAsBox(0.8f, 0.1f, b2Vec2(halfWidth*1.2,0), 0);
    myFixtureDef.shape = &polygon; //defino que es un poligono
    myFixtureDef.isSensor = true;
    myFixtureDef.density = 1.0f; //le doy masa
    b2Fixture* pushSensor1 = pjB2D->CreateFixture(&myFixtureDef);
    pushSensor1->SetUserData( (void*)EMPUJE );

    polygon.SetAsBox(0.8f, 0.1f, b2Vec2(-halfWidth*1.2,0), 0);
    myFixtureDef.shape = &polygon; //defino que es un poligono
    myFixtureDef.isSensor = true;
    myFixtureDef.density = 1.0f; //le doy masa
    b2Fixture* pushSensor2 = pjB2D->CreateFixture(&myFixtureDef);
    pushSensor2->SetUserData( (void*)EMPUJE );

    return pjB2D;
}


void checkBoundsAndOverlap(b2World ** worldB2D, float32 widthWorld, float32 heightWorld){

	Logger& log = *Logger::Instancia();

	bool overlap;
	b2Body *b = (*worldB2D)->GetBodyList();
	while (b){
		if(b->GetPosition().x > widthWorld || b->GetPosition().y > heightWorld
				|| b->GetPosition().x < 0.0 || b->GetPosition().y < 0.0){

			ostringstream message;   // stream used for the conversion
			message << "El objeto en la posicion " << b->GetPosition().x << "," <<
					b->GetPosition().y << " se encuentra fuera del mapa. Borrado.";

			log.log(WINDOWLOG,WARNING,message.str());

			(*worldB2D)->DestroyBody(b);
			b = (*worldB2D)->GetBodyList();
			continue;
		}

		bool skip = false;
		for (b2Body *b2 = b->GetNext(); b2; b2 = b2->GetNext()) {
			if (b->GetType() == b2_staticBody || b2->GetType() == b2_staticBody) continue;
			overlap = b2TestOverlap(b->GetFixtureList()->GetShape(), 0,
					b2->GetFixtureList()->GetShape(), 0,
					b->GetFixtureList()->GetBody()->GetTransform(),
					b2->GetFixtureList()->GetBody()->GetTransform());
			if (overlap) {

				ostringstream message;
				message << "Objeto en la posicion " << b->GetPosition().x << "," <<
						b->GetPosition().y << " borrado por solapamiento.";

				log.log(WINDOWLOG,WARNING,message.str());

				(*worldB2D)->DestroyBody(b);
				b = (*worldB2D)->GetBodyList();
				skip = true;
				break;
			}
		}
		if (!skip) b = b->GetNext();
	}
}







tipos_datos_t obtenerTipo(std::string tipo) {
	if (!tipo.compare("circ"))
		return TIPOPELOTADENIEVE;
	if (!tipo.compare("rect"))
		return TIPOLADRILLO;
	if (!tipo.compare("poli"))
		return TIPOLADRILLO;
	if (!tipo.compare("irreg"))
		return TIPOLADRILLO;
	if (!tipo.compare("personaje"))
		return TIPOPERSONAJE;
	if (!tipo.compare("enemigoEstandar"))
		return TIPOENEMIGOESTANDAR;
	if (!tipo.compare("enemigoFuego"))
		return TIPOENEMIGOFUEGO;
	if (!tipo.compare("laguna"))
		return TIPOLAGUNA;
	if (!tipo.compare("agujero"))
		return TIPOAGUJERO;
}

// Genera un objeto.
ObjetoModelo * generarObjeto(std::string sConfig, int numeroObjeto, b2World ** worldB2D, ControladorJuego * controlador){

	ObjetoModelo * objeto;

	static int i = 0;
	i++;

	tipos_datos_t tipo = obtenerTipo(get_node("tipo", "objetos", sConfig, numeroObjeto, "asd"));

	// Determino el tipo de objeto segun 'tipo'.
	switch(tipo){
	case TIPOPERSONAJE:{
		Jugador * jugador = controlador->estado.obtenerJugadorSinPersonaje();

		// Si no existe un jugador, es que los demas jugadores estan muertos
		// y no debo crear mas personajes.
		if (jugador == NULL) return NULL;

		// En caso contrario, crea al personaje.
		Personaje * personaje = new Personaje(sConfig, numeroObjeto);
		personaje->cuerpoB2D = createPJ(sConfig, worldB2D, numeroObjeto);
		personaje->cuerpoB2D->SetUserData(personaje);
		personaje->modificado = true;
		personaje->paraDestruir = false;
		personaje->posicionInicial.x = personaje->cuerpoB2D->GetPosition().x;
		personaje->posicionInicial.y = personaje->cuerpoB2D->GetPosition().y;
		personaje->orientacion = ObjetoModelo::IZQUIERDA;
		controlador->modelo.agregarPersonaje(personaje);
		personaje->nombre = jugador->nombre;
		personaje->salud = jugador->vidas;
		personaje->puntaje = jugador->puntaje;
		jugador->personaje = personaje;
		personaje->inicializar();
		objeto = personaje;
		break;
		}
	case TIPOENEMIGOESTANDAR:{
		EnemigoEstandar * enemigo = new EnemigoEstandar(sConfig, numeroObjeto);
		enemigo->cuerpoB2D = createEnemy(sConfig, worldB2D, numeroObjeto);
		enemigo->cuerpoB2D->SetUserData(enemigo);
		enemigo->modificado = true;
		enemigo->paraDestruir = false;
		enemigo->orientacion = ObjetoModelo::IZQUIERDA;
		controlador->modelo.agregarEnemigo(enemigo);
		enemigo->inicializar();
		objeto = enemigo;
		break;
		}
	case TIPOENEMIGOFUEGO:{
		EnemigoFuego * enemigo = new EnemigoFuego(sConfig, numeroObjeto);
		enemigo->cuerpoB2D = createEnemy(sConfig, worldB2D, numeroObjeto);
		enemigo->cuerpoB2D->SetUserData(enemigo);
		enemigo->modificado = true;
		enemigo->paraDestruir = false;
		enemigo->orientacion = ObjetoModelo::IZQUIERDA;
		controlador->modelo.agregarEnemigo(enemigo);
		enemigo->inicializar();
		objeto = enemigo;
		break;
		}
	case TIPOLADRILLO:{
		Ladrillo * obj = new Ladrillo(sConfig, numeroObjeto);
		obj->cuerpoB2D = createObject(sConfig, worldB2D, numeroObjeto);
		obj->cuerpoB2D->SetUserData(obj);
		obj->modificado = true;
		obj->paraDestruir = false;
		obj->orientacion = ObjetoModelo::IZQUIERDA;
		controlador->modelo.agregarObjeto(obj);
		obj->inicializar();
		objeto = obj;
		break;
		}
	case TIPOPELOTADENIEVE:{
		PelotaDeNieve * obj = new PelotaDeNieve(sConfig, numeroObjeto);
		obj->cuerpoB2D = createObject(sConfig, worldB2D, numeroObjeto);
		obj->cuerpoB2D->SetUserData(obj);
		obj->modificado = true;
		obj->paraDestruir = false;
		obj->orientacion = ObjetoModelo::IZQUIERDA;
		controlador->modelo.agregarObjeto(obj);
		obj->inicializar();
		objeto = obj;
		break;
		}
	case TIPOLAGUNA:{
		Laguna * obj = new Laguna(sConfig, numeroObjeto);
		obj->cuerpoB2D = createObject(sConfig, worldB2D, numeroObjeto);
		obj->cuerpoB2D->SetUserData(obj);
		obj->modificado = true;
		obj->paraDestruir = false;
		obj->orientacion = ObjetoModelo::IZQUIERDA;
		controlador->modelo.agregarObjeto(obj);
		obj->inicializar();
		objeto = obj;
		break;
	}
	case TIPOAGUJERO:{
		std::cout << "creando un agujero" << std::endl;
		Agujero * obj = new Agujero(sConfig, numeroObjeto);
		obj->cuerpoB2D = createObject(sConfig, worldB2D, numeroObjeto);
		obj->cuerpoB2D->SetUserData(obj);
		obj->modificado = true;
		obj->paraDestruir = false;
		obj->orientacion = ObjetoModelo::IZQUIERDA;
		controlador->modelo.agregarObjeto(obj);
		obj->inicializar();
		objeto = obj;
		break;
	}
	default:
		std::cout << "no se reconocio el tipo" << std::endl;
		break;
	}

	objeto->cayoPorAgujero = false;

	return objeto;
}

bool Inicializador::init(std::string configFile, b2World ** worldB2D, ControladorJuego * controlador,
	ContactListener * contactListener, std::string & nextLevel) {

	Logger& log = *Logger::Instancia();
	std::string sConfig;
	bool statusOK = true;
	statusOK = loadInitialValues(configFile, sConfig);
	if (!statusOK) return false;

	// Obtiene el path el siguiente nivel.
	nextLevel = get_node("prox-nivel", "escenario", sConfig, "defaultConfig.json");

	// Obtiene las dimensiones del mundo.
	float heightWorld = get_node("alto-un", "escenario", sConfig, 10.0f);
	float widthWorld = get_node("ancho-un", "escenario", sConfig, 10.0f);

	LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.x = widthWorld;
	LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa.y = heightWorld;

	// Inicializa el mundo de B2D.
	worldInit(worldB2D, contactListener);

	// Carga todos los objetos del mapa.
	int formas = get_size("objetos", sConfig);
	for (int i = 0; i < formas; i++) {
		generarObjeto(sConfig, i, worldB2D, controlador);
	}

	// Carga los enemigos
	//this->enemysInit(worldB2D, sConfig, army);

	// Remueve los objetos superpuestos.
	checkBoundsAndOverlap(worldB2D, widthWorld, heightWorld);

	log.log(MAINLOG,OK,"Se ha inicializado correctamente el mundo.");

	return true;
}

