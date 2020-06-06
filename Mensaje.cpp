#include "Mensaje.h"

Mensaje::Mensaje(string mensaje,int llave,string autor){
	this->mensaje = mensaje;
	this->llave = llave;
	this->autor = autor;
}

Mensaje::~Mensaje(){
}

string Mensaje::getMensaje(){
	return this->mensaje;
}
int Mensaje::getLlave(){
	return this->llave;
}
string Mensaje::getAutor(){
	return this->autor;
}
