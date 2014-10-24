/*
 * Logger.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: matias
 */

#include "Logger.h"
#include <stddef.h> //Define NULL
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

//Puntero global estatico para asegurar que solo se use una instancia del Logger
Logger* Logger::InstanciaActual = NULL;

/** Se llama esta funcion para crear una instacia del logger. El constructor es privado
 * y solo se llama desde adentro de esta funcion. Si ya existe uno, lo devuelve.
*/

Logger::~Logger(){
	if(this->logActual.is_open()) this->logActual.close();
}

Logger* Logger::Instancia()
{
   if (!InstanciaActual){   // Only allow one instance of class to be generated.
	   InstanciaActual = new Logger;
	   InstanciaActual->mode = ALL;
   }

   return InstanciaActual;
}

bool Logger::setMode(string mode){
	if (mode != ALL && mode != ERRORS_ONLY && mode != NO_ERRORS){
		return false;
	}
	this->mode = mode;
	return true;
}

bool Logger::abrirLog(std::string _logFile)
{
	if( this->logActual.is_open() ) this->logActual.close();
	this->logActual.open ( _logFile.c_str(), ios::out | ios::app);
	if (this->logActual.is_open()) return true;
	else return false;
}

void Logger::cerrarLog()
{
	if(! this->logActual.is_open() ) return;
	this->logActual.close();
	return;
}

bool Logger::escribirLog(string tipo, string detalle){
	if(! this->logActual.is_open())return false;

	//Verifico el modo del logger
	if (this->mode == ERRORS_ONLY && tipo != ERROR) return true;
	if (this->mode == NO_ERRORS && tipo == ERROR) return true;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	string str(buffer);
	this->logActual << str + " -> " + tipo + " -> " + detalle + "\n";

	return true;
}

bool Logger::estaAbierto()
{
	return this->logActual.is_open();
}

bool Logger::crearLogs()
{
	mkdir(LOGDIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	std::ofstream logfile (WINDOWLOG);
	logfile.close();

	logfile.open(DIBUJABLELOG);
	logfile.close();

	logfile.open(HANDLERLOG);
	logfile.close();

	logfile.open(SIMULACIONLOG);
	logfile.close();

	logfile.open(PARSERLOG);
	logfile.close();

	logfile.open(MAINLOG);
	logfile.close();

	logfile.open(SHAPESLOG);
	logfile.close();

	return true;
}

void Logger::log(std::string logFile, std::string tipo, std::string detalle){

	if (!abrirLog(logFile)) {
		std::cout << "Error al abrir archivo de log " << logFile << ", creando... " << std::endl;
		crearLogs();
		if (!abrirLog(MAINLOG))	{
			std::cout << "No se pudo crear el archivo de log." << std::endl;
			return;
		}
	}
	escribirLog(tipo, detalle);
	cerrarLog();
}
