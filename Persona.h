#ifndef PERSONA_H
#define PERSONA_H

#include "Mensaje.h"

#include <string>
#include <vector>

using namespace std;
class Persona {
	private:
		string nombre;
		string apellido;
		string password;
		int llave;
		vector <Mensaje*> mensajes;
	public:
		Persona (string,string,string);
		~Persona();
		vector<Mensaje*>& getMensajes();
		string getNombre();
		string getApellido();
		string getPassword();
		int getLlave();
};

#endif
