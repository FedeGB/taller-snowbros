/*
 * ControladorUsuarios.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: rodrizapico
 */

#include "ControladorUsuarios.h"

ControladorUsuarios::ControladorUsuarios() {
	tamanioMaximo = 4;
	finDePartida = false;
	resultadoPartida = GANARON;
	for (int i = 0; i < 4; i++)	usuariosRegistrados[i] = NO_REGISTRADO;
	puntajeKills = 0;
}

void ControladorUsuarios::setConnectionLimit(int max) {
	tamanioMaximo = max;
}

ControladorUsuarios::~ControladorUsuarios() {
	// TODO Auto-generated destructor stub
}

// Asigna un numero de usuario.
int ControladorUsuarios::asignarNumeroUsuario(){
	for (int i = 0; i < 4; i++){
		if (usuariosRegistrados[i] == NO_REGISTRADO){
			usuariosRegistrados[i] = REGISTRADO;
			return i;
		}
	}

	return -1;
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

	(*this)[username]->numeroUsuario = asignarNumeroUsuario();
	return true;
}

// Elimina el usuario solicitado.
// username: el usuario al cual se quiere eliminar.
void ControladorUsuarios::eliminarUsuario(std::string username){
	//if (!usuarioExiste(username)) return;
	usuariosRegistrados[ (*this)[username]->numeroUsuario ] = NO_REGISTRADO;
	this->erase(username);
}

// Devuelve el numero de conexion correspondiente al usuario solicitado,
// asignado por orden de su primera conexion.
int ControladorUsuarios::numeroUsuario(std::string username){
	if (!usuarioExiste(username)) return -1;
	return (*this)[username]->numeroUsuario;
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

	uint numUsuarios = 0;
	for(int i = 0; i < 4; i++){
		if (usuariosRegistrados[i] == NO_NOTIFICADO) return false;
		if (usuariosRegistrados[i] == ESPERANDO_ESTADO) return false;
		if (usuariosRegistrados[i] == REGISTRADO) numUsuarios += 1;
	}

	finDePartida = false;

	return numUsuarios < tamanioMaximo ? false:true;
}

// Confirma que el usuario en cuestion va a jugar la siguiente partida.
void ControladorUsuarios::confirmarUsuario(std::string username, estado_user_t estado){
	usuariosRegistrados[ (*this)[username]->numeroUsuario ] = estado;
}

// Notifica a todos los jugadores conectados que el juego finalizo, informando el resultado
// de la partida. Ademas, inicia el protocolo para mantenerlos conectados a una nueva partida,
// o desconectarlos en caso que no quieran jugar nuevamente.
void ControladorUsuarios::notificarFinDePartida(resultado_t resultado){

	finDePartida = true;
	resultadoPartida = resultado;

	for (ControladorUsuarios::iterator it=(*this).begin(); it!=(*this).end(); ++it){
		if (!(*it).second->online) eliminarUsuario((*it).second->username);
		else usuariosRegistrados[(*it).second->numeroUsuario] = NO_NOTIFICADO;
	}


	for(int i = 0; i < 4; i++) if (usuariosRegistrados[i] == REGISTRADO) usuariosRegistrados[i] = NO_NOTIFICADO;
}

// Obtiene una version serializada de lo que se ve en pantalla del usuario
// pedido, para ser enviada al cliente para renderear.
// username:el nombre de usuario para el que se quiere obtener la pantalla
// serializada.
// return: la pantalla serializada para username.
std::string ControladorUsuarios::obtenerPantallaSerializada(std::string username){

	std::string buffer = (*this)[username]->obtenerPantallaSerializada();

	Metadata * metadata = new Metadata();
	metadata->tipo = METADATAHUD;

	metadata->puntaje = this->puntajeKills;
	int j=0;
	for (ControladorUsuarios::iterator it=(*this).begin(); it!=(*this).end(); ++it){
		if (!(*it).second || !(*it).second->inicializado) continue;
		if (!(*it).second->online) {
			metadata->mensaje += (*it).second->username;
			metadata->mensaje += "-ha-perdido-conexion-al-juego.&";
			metadata->users[j] = "offline";
			metadata->vidas[j] = 0;
		}
		else{
			metadata->users[j] = (*it).second->username;
			metadata->vidas[j] = (*it).second->getLives();
		}
		metadata->puntaje += ((*it).second)->getPuntaje();
		j++;
	}

	buffer += "%";
	buffer += metadata->serializar();

	delete metadata;

	return buffer;
}

void ControladorUsuarios::sumarPuntaje(int points) {
	puntajeKills += points;
}
