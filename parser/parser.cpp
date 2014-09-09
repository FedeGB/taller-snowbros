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
			return NULL;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog("ERROR", "campo "+ data +" vacio");
		log.cerrarLog();
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
			return NULL;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog("ERROR", "campo "+ data +" vacio");
		log.cerrarLog();
	}
	return root[param].get(data, defaultData).asString();

}

string get_node(string data, string param, string file, int field,
		char* defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log= * Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "+ reader.getFormattedErrorMessages();
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		std::string s;
		std::stringstream out;
		out << field;
		s = out.str();
		log.escribirLog("ERROR", "campo "+ data +" vacio del objeto" + s);
		log.cerrarLog();
	}
	return root[param][field].get(data, defaultData).asString();
}
