#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

#include "Persona.h"

using namespace std;

vector <Persona*> personas;
int u; //variable que nos ayudara a manejar al usuario que inicio sesion.


bool Registrado (string);
bool LogIn (string,string);
string CesarAdelante(string,int);
string CesarAtras(string,int);
int MenuUsuario();
string Cifrado(string,int);
string Descifrado(string,int);


int main (){
	int opcion;
	
	string nombre,apellido,password;
	while (true){
		cout << "1. Registrarse" << endl;
		cout << "2. Ingresar" << endl;
		cout << "3. Salir" << endl;
		cout << "Ingrese opcion: "; cin >> opcion; cout << endl;
		
		switch (opcion){
			case 1: {
				cout << "Ingrese su nombre: "; cin  >> nombre;
				cout << "Ingrese su apellido: "; cin >> apellido;
				cout << "Ingrese su contrasena: "; cin >> password; cout << endl;
				
				bool registrado = Registrado (nombre);
				if (registrado == true){
					cout << "Esta persona ya esta registrada..." << endl;
				} else {
					personas.push_back(new Persona (nombre,apellido,password));
					cout << "Se ha registrado exitosamente!" << endl;
				}
				break;
			}
			case 2:{
				cout << "LOGIN" << endl << endl;
				cout << "Ingrese su nombre: "; cin  >> nombre;
				cout << "Ingrese su contrasena: "; cin >> password; cout << endl;
				
				bool login = LogIn(nombre,password);
				if (login == true){

					while (login){
						opcion = MenuUsuario();
						while (opcion > 4 || opcion < 1){
							cout << "Opcion Incorrecta..." << endl;
							cout << "Ingrese opcion: "; cin >> opcion; cout << endl;
						}
						
						switch (opcion) {
							case 1: {
								for (int i = 0; i < personas.size(); i++){
									cout << (i+1) << ". " << personas[i]->getNombre() << endl;
								}
								cout << "Selecciona a quien enviar el mensaje: "; cin >> opcion;
								opcion -= 1;
								
								while (opcion < 0 || opcion >= personas.size()){
									cout << endl << "Opcion Incorrecta" << endl;
									cout << "Selecciona a quien enviar el mensaje: "; cin >> opcion;
									opcion -=1;
									
								}
								cout << endl;
								
								string mensaje;
								cout << "Escribe el mensaje: "; cin >> mensaje;
								
								personas[opcion]->getMensajes().push_back(new Mensaje(Cifrado(mensaje,personas[u]->getLlave()), personas[u]->getLlave(),personas[u]->getNombre()));
								
								
								cout << endl << "Mensaje enviado con exito!" << endl;
								
								break;
							}
							case 2: {
								if (personas[u]->getMensajes().size() == 0){
									cout << "No tienes mensajes recibidos..." << endl;
								} else {

									for (int i = 0; i < personas[u]->getMensajes().size(); i++){
										cout << (i+1) << ". " << personas[u]->getMensajes()[i]->getMensaje() << endl; 
									}
									cout << "Ingrese mensaje a descifrar: "; cin >> opcion; opcion--;
									
									while (opcion < 0 || opcion >= personas[u]->getMensajes().size()){
										cout << endl << "Fuera del rango, intente de nuevo." << endl
										<< "Ingrese mensaje a descifrar: "; cin >> opcion; opcion--;
									}
									
									
									cout << endl << "Enviado por: " << personas[u]->getMensajes()[opcion]->getAutor() << endl
									<<  "El mensaje dice: " << Descifrado(personas[u]->getMensajes()[opcion]->getMensaje(), personas[u]->getMensajes()[opcion]->getLlave()) << endl;
								
								}
								
								break;
							}
							case 3: {
								cout << "Tu llave es: " << personas[u]->getLlave() << endl;
								break;
							}
							case 4: {
								login = false;
								break;
							}
						}
						
						cout << endl;
					}
						
					
				} else {
					cout << "Datos Incorrectos..." << endl;
				}
				
				break;
			}
			case 3:{
				return 0;
				break;
			}
			default:{
				cout << "Opcion Incorrecta" << endl;
				break;
			}
		}
		
		cout <<  endl;
	}
	
	for (int i = 0; i < personas.size(); i++){
		delete personas[i];
	}
	
}

bool Registrado (string nombre){
	bool registrado = false;
	for (int i = 0; i < personas.size(); i++){
		if (nombre == personas[i]->getNombre()){
			registrado = true;
			break;
		}
	}
	
	return registrado;
}

bool LogIn (string nombre, string password){
	bool login = false;
	for (int i = 0; i < personas.size(); i++){
		if (nombre == personas[i]->getNombre() && password == personas[i]->getPassword()){
			login = true;
			u = i;
			break;
		}
	}
	
	return login;
}


string CesarAdelante (string palabra, int numero){
	string nueva_palabra = "";
	for (int i = 0; i < palabra.size(); i++){
		char ascii = palabra[i];
		ascii += numero;
		nueva_palabra += ascii;
	}
	
	return nueva_palabra;
}
string CesarAtras (string palabra, int numero){
	string nueva_palabra = "";
	for (int i = 0; i < palabra.size(); i++){
		char ascii = palabra[i];
		ascii -= numero;
		nueva_palabra += ascii;
	}
	
	return nueva_palabra;
}

int MenuUsuario(){
	int opcion;
	cout << "Hola " << personas[u]->getNombre()<< "!" << endl << endl;
	cout << "1. Enviar mensaje" << endl;
	cout << "2. Ver mensajes" << endl;
	cout << "3. Ver mi llave" << endl;
	cout << "4. Salir" << endl;
	cout << "Ingrese opcion: "; cin >> opcion; cout << endl;
	
	return opcion;
}

string Cifrado(string mensaje, int llave){
	if (llave == 0){
		return mensaje;
	} else {
		
		string cifrado = "";
		int cont = 0;
		
		if (mensaje.size() % llave == 0){
			string arreglo[mensaje.size()/llave];
			
			for (int i = 0; i < mensaje.size()/llave; i++){
				arreglo[i] = mensaje.substr(cont,llave);
				
				cont += llave;
			}
			
			for (int i = 0; i < mensaje.size()/llave; i++){
				if (i % 2 == 0){
					arreglo[i] = CesarAdelante(arreglo[i],llave);
				} else {
					arreglo[i] = CesarAtras(arreglo[i],llave);
				}
			}
						
			for (int i = 0; i < mensaje.size()/llave; i++){
				cifrado += arreglo[i];
			}
			
			return Cifrado(cifrado,llave-1);
						
		} else {
			
			string arreglo[(mensaje.size()/llave)+1];
			
			for (int i = 0; i < (mensaje.size()/llave)+1; i++){
				arreglo[i] = mensaje.substr(cont,llave);
				
				cont += llave;
			}
			
			for (int i = 0; i < (mensaje.size()/llave)+1; i++){
				if (i % 2 == 0){
					arreglo[i] = CesarAdelante(arreglo[i],llave);
				} else {
					arreglo[i] = CesarAtras(arreglo[i],llave);
				}
			}
						
			for (int i = 0; i < (mensaje.size()/llave)+1; i++){
				cifrado += arreglo[i];
			}
			
			return Cifrado(cifrado,llave-1);			
		}		
	}
}

string Descifrado(string mensaje, int llave){
	if (llave == 0){
		return mensaje;
	} else {
		
		string cifrado = "";
		int cont = 0;
		
		if (mensaje.size() % llave == 0){
			string arreglo[mensaje.size()/llave];
			
			for (int i = 0; i < mensaje.size()/llave; i++){
				arreglo[i] = mensaje.substr(cont,llave);
				
				cont += llave;
			}
			
			for (int i = 0; i < mensaje.size()/llave; i++){
				if (i % 2 == 0){
					arreglo[i] = CesarAtras(arreglo[i],llave);
				} else {
					arreglo[i] = CesarAdelante(arreglo[i],llave);
				}
			}
			
			
			for (int i = 0; i < mensaje.size()/llave; i++){
				cifrado += arreglo[i];
			}
			
			return Descifrado(cifrado,llave-1);
				
		} else {
			
			string arreglo[(mensaje.size()/llave)+1];
			
			for (int i = 0; i < (mensaje.size()/llave)+1; i++){
				arreglo[i] = mensaje.substr(cont,llave);
				
				cont += llave;
			}
			
			for (int i = 0; i < (mensaje.size()/llave)+1; i++){
				if (i % 2 == 0){
					arreglo[i] = CesarAtras(arreglo[i],llave);
				} else {
					arreglo[i] = CesarAdelante(arreglo[i],llave);
				}
			}
			
			
			for (int i = 0; i < (mensaje.size()/llave)+1; i++){
				cifrado += arreglo[i];
			}
			
			return Descifrado(cifrado,llave-1);
			
		}		
	}		
}


