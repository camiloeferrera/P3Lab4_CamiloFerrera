#include "Mensaje.h"

Mensaje::Mensaje(string mensaje,int llave){
	this->mensaje = mensaje;
	this->llave = llave;
}

Mensaje::~Mensaje(){
}

string Mensaje::getMensaje(){
	return this->mensaje;
}
int Mensaje::getLlave(){
	return this->llave;
}
