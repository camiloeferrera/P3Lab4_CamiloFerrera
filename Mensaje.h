#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>

using std::string;

class Mensaje
{
	public:
		Mensaje(string,int,string);
		~Mensaje();
		
		string getMensaje();
		int getLlave();
		string getAutor();
	protected:
		string mensaje,autor;
		int llave;
};

#endif
