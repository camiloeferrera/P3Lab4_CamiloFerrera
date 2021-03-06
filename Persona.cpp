#include "Persona.h"

Persona::Persona(string _nombre, string _apellido, string _password){
	nombre = _nombre;
	apellido = _apellido;
	password = _password;
	srand ((int) time (0));
	llave = rand() % 16;
}

Persona::~Persona(){
	for (int i = 0; i < this->mensajes.size(); i++){
		delete this->mensajes[i];
	}
}

vector <Mensaje*>& Persona::getMensajes(){
    return mensajes;
}
string Persona::getNombre(){
	return nombre;
}
string Persona::getApellido(){
	return apellido;
}
string Persona::getPassword(){
	return password;
}
int Persona::getLlave(){
	return llave;
}
