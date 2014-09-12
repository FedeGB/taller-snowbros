/*
 * Logger.h
 *
 *  Created on: Aug 31, 2014
 *      Author: matias
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>
#include <iostream>

#define WINDOWLOG "log/Window.log"
#define DIBUJABLELOG "log/Dibujable.log"
#define HANDLERLOG "log/Handler.log"
#define SIMULACIONLOG "log/Simulacion.log"
#define PARSERLOG "log/Parser.log"

#define WARNING "WAR"
#define ERROR "ERR"
#define OK "OK"

class Logger{
public:
	~Logger(); //Destructor creado para garantizar que se cierre el log.
	static Logger* Instancia();
	bool abrirLog(std::string logFile);
	bool escribirLog(std::string tipo, std::string detalle);
	bool estaAbierto();
	void cerrarLog();

private:
	Logger(){};  // Constructor privado para que no lo invoquen
	Logger(Logger const&){};             // Copia privado
	Logger& operator=(Logger const&);  // Asignacion es privado
	static Logger* InstanciaActual;
	std::ofstream logActual;

};

#endif /* LOGGER_H_ */
