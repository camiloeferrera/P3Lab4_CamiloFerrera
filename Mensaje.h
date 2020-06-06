#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>

using std::string;

class Mensaje
{
	public:
		Mensaje(string,int);
		~Mensaje();
		
		string getMensaje();
		int getLlave();
	protected:
		string mensaje;
		int llave;
};

#endif
