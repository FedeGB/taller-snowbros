#include "parser.h"
//#include "json.h"
#include <sstream>
using namespace std;

string get_node(string data, string param, string file, char* defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isString()){
		if (!log.abrirLog("Parser.log")) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return defaultData;
				}
				log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera string");
				log.cerrarLog();
				return defaultData;
	}
	return root[param].get(data, defaultData).asString();

}

string get_node(char* datas, string param, string file, char* defaultData) {
	string data(datas);
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isString()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera string");
					log.cerrarLog();
					return defaultData;
		}
	return root[param].get(data, defaultData).asString();

}

string get_node(string data, string param, string file, int field,
		char* defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio, del objeto" + s);
		log.cerrarLog();
	}
	if (!root[param][data].isString()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +"del objeto"+ s+ ". Se espera string");
					log.cerrarLog();
					return defaultData;
		}
	return root[param][field].get(data, defaultData).asString();
}

int get_node(string data, string param, string file, int defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isInt()){
		if (!log.abrirLog("Parser.log")) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return defaultData;
				}
				log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera int");
				log.cerrarLog();
				return defaultData;
	}
	return root[param].get(data, defaultData).asInt();

}

int get_node(char* datas, string param, string file, int defaultData) {
	string data(datas);
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isInt()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera int");
					log.cerrarLog();
					return defaultData;
		}
	return root[param].get(data, defaultData).asInt();

}

int get_node(string data, string param, string file, int field,
		int defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio, del objeto" + s);
		log.cerrarLog();
	}
	if (!root[param][data].isInt()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +"del objeto"+ s+ ". Se espera int");
					log.cerrarLog();
			return defaultData;
		}
	return root[param][field].get(data, defaultData).asInt();
}

float get_node(string data, string param, string file, float defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isNumeric()){
		if (!log.abrirLog("Parser.log")) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return defaultData;
				}
				log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera float");
				log.cerrarLog();
				return defaultData;
	}
	return root[param].get(data, defaultData).asFloat();

}

float get_node(char* datas, string param, string file, float defaultData) {
	string data(datas);
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isNumeric()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera int");
					log.cerrarLog();
					return defaultData;
		}
	return root[param].get(data, defaultData).asFloat();

}

float get_node(string data, string param, string file, int field,
		float defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio, del objeto" + s);
		log.cerrarLog();
	}
	if (!root[param][data].isNumeric()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +"del objeto"+ s+ ". Se espera int");
					log.cerrarLog();
					return defaultData;
		}
	return root[param][field].get(data, defaultData).asFloat();
}

bool get_node(string data, string param, string file, bool defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isBool()){
		if (!log.abrirLog("Parser.log")) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return defaultData;
				}
				log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera Bool");
				log.cerrarLog();
				return defaultData;
	}
	return root[param].get(data, defaultData).asBool();

}

bool get_node(char* datas, string param, string file, bool defaultData) {
	string data(datas);
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio");
		log.cerrarLog();
	}
	if (!root[param][data].isBool()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +". Se espera Bool");
					log.cerrarLog();
					return defaultData;
		}
	return root[param].get(data, defaultData).asBool();

}

bool get_node(string data, string param, string file, int field,
		bool defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return defaultData;
		}
		log.escribirLog("ERROR", "campo "+ data +" de "+param+" vacio, del objeto" + s);
		log.cerrarLog();
	}
	if (!root[param][data].isBool()){
			if (!log.abrirLog("Parser.log")) {
						std::cout << "Error al abrir archivo de log" << std::endl;
						return defaultData;
					}
					log.escribirLog("ERROR", " tipo incorrecto del campo "+ data +" de "+param +"del objeto"+ s+ ". Se espera int");
					log.cerrarLog();
					return defaultData;
		}
	return root[param][field].get(data, defaultData).asBool();
}
