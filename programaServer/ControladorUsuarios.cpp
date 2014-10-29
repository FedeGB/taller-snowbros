/*
 * ControladorUsuarios.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: rodrizapico
 */

#include "ControladorUsuarios.h"

ControladorUsuarios::ControladorUsuarios() {
	tamanioMaximo = 4;
}

ControladorUsuarios::~ControladorUsuarios() {
	// TODO Auto-generated destructor stub
}

// Agrega un nuevo usuario a los usuarios registrados en el servidor.
// username: el nombre de usuario a registrar.
// retorno: true si tuvo exito el registro, false si hubo algun error.
bool ControladorUsuarios::registrarUsuario(std::string username){

	// Si no hay mas espacio, o el usuario ya existe, no se lo puede agregar.
	if (escenarioLleno() || usuarioExiste(username)) return false;

	// En caso contrario, se lo agrega.
	(*this)[username] = new Usuario();
	(*this)[username]->username = username;
	return true;
}

// Verifica si el usuario requerido ya se encuentra registrado.
// username: el nombre de usuario a verificar.
// retorno: true si el usuario ya se encuentra registrado, false en caso contrario.
bool ControladorUsuarios::usuarioExiste(std::string username){
	return this->count(username) != 0? true : false;
}

// Obtiene el usuario correspondiente al username dado.
// username: el usuario que se quiere recuperar.
// return: puntero al usuario, o NULL en caso de que no exista.
Usuario * ControladorUsuarios::obtenerUsuario(std::string username){
	if (!usuarioExiste(username)) return NULL;
	return (*this)[username];
}

// Determina si queda lugar en el escenario para que ingresen nuevos usuarios.
// return: true si no pueden ingresar mas usuarios, false si aun hay lugar.
bool ControladorUsuarios::escenarioLleno(){
	return this->size() < tamanioMaximo ? false :true;
}
