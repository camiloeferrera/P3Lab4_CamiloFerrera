#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Persona {
	private:
		string nombre;
		string apellido;
		string password;
		int llave;
		vector <string> mensajes;
	public:
		Persona (string,string,string);
		vector<string>& getMensajes();
		string getNombre();
		string getApellido();
		string getPassword();
		int getLlave();
};

Persona::Persona(string _nombre, string _apellido, string _password){
	nombre = _nombre;
	apellido = _apellido;
	password = _password;
	srand ((int) time (0));
	llave = rand() % 15;
}

vector <Persona> personas;
int u; //variable que nos ayudara a manejar al usuario que inicio sesion.

vector <string>& Persona::getMensajes(){
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


bool Registrado (string nombre, string apellido){
	bool registrado = false;
	for (int i = 0; i < personas.size(); i++){
		if (nombre == personas[i].getNombre() && apellido == personas[i].getApellido()){
			registrado = true;
			break;
		}
	}
	
	return registrado;
}

bool LogIn (string nombre, string password){
	bool login = false;
	for (int i = 0; i < personas.size(); i++){
		if (nombre == personas[i].getNombre() && password == personas[i].getPassword()){
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
	cout << "Hola " << personas[u].getNombre()<< "!" << endl << endl;
	cout << "1. Enviar mensaje" << endl;
	cout << "2. Ver mensajes" << endl;
	cout << "3. Ver mi llave" << endl;
	cout << "4. Salir" << endl;
	cout << "Ingrese opcion: "; cin >> opcion; cout << endl;
	
	return opcion;
}

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
				
				bool registrado = Registrado (nombre,apellido);
				if (registrado == true){
					cout << "Esta persona ya esta registrada..." << endl;
				} else {
					personas.push_back(Persona (nombre,apellido,password));
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
									cout << (i+1) << ". " << personas[i].getNombre() << endl;
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
								
								
								if (mensaje.size()/personas[u].getLlave() == 0){
									string newmensaje;
										for (int x = personas[u].getLlave(); x > 0 ; x--){
											string *arreglo = NULL;
											arreglo = new string [mensaje.size()/x];
											
											int contador = 0;											
		
											for (int i = 0; i < mensaje.size()/x; i++){
												for (int j = 0; j < x; j++){
													arreglo[i] += mensaje[contador];
													contador ++; 
												}
											}
											
											for (int i = 0; i < mensaje.size()/x; i++){
												if (i % 2 == 0){
													arreglo[i] = CesarAdelante(arreglo[i],x);
												} else {
													arreglo[i] = CesarAtras(arreglo[i],x);
												}
											}
											
											
											
											newmensaje = "";
											for (int i = 0;i < mensaje.size()/x; i++){
												for (int j = 0; j < x; j++){
													newmensaje += arreglo[i][j];
												}
											}
											mensaje = newmensaje;
											delete [] arreglo;
										}
									
									personas[opcion].getMensajes().push_back((char)u + mensaje);
								} else {
										string newmensaje;
										for (int x = personas[u].getLlave(); x > 0 ; x--){
											string *arreglo = NULL;
											arreglo = new string [mensaje.size()/x+1];
											
											int contador = 0;												
											
											for (int i = 0; i < mensaje.size()/x+1; i++){
												for (int j = 0; j < x; j++){
													arreglo[i] += mensaje[contador];
													contador ++; 
												}
											}
											
											for (int i = 0; i < mensaje.size()/x+1; i++){
												if (i % 2 == 0){
													arreglo[i] = CesarAdelante(arreglo[i],x);
												} else {
													arreglo[i] = CesarAtras(arreglo[i],x);
												}
											}
											
											
											
											newmensaje = "";
											for (int i = 0;i < mensaje.size()/x+1; i++){
												for (int j = 0; j < x; j++){
													newmensaje += arreglo[i][j];
												}
											}
											mensaje = newmensaje;
											delete [] arreglo;
										}
									
									personas[opcion].getMensajes().push_back((char)u + mensaje);
									cout << endl << "Mensaje enviado exitosamente !" << endl;
									
								}
								
								break;
							}
							case 2: {
								if (personas[u].getMensajes().size() == 0){
									cout << "Tu lista de mensajes esta vacia." << endl;
								} else {
									cout << "Mensajes recibidos:" << endl << endl;
									for (int i = 0; i < personas[u].getMensajes().size(); i++){
										int apoyo = (char)personas[u].getMensajes()[i][0];
										string newmensaje = "";
										for (int j = 1; j < personas[u].getMensajes()[i].size(); j++ ){
											newmensaje += personas[u].getMensajes()[i][j];
										}
										
										
										personas[u].getMensajes()[i] = newmensaje;
										cout << (i+1) << ". " << "Enviado por: " << personas[apoyo].getNombre() << " " <<  personas[u].getMensajes()[i] << endl; 
										
									}
									cout << "Escoga el mensaje: "; cin >> opcion; cout << endl;
									opcion -= 1;
									
									while (opcion < 0 || opcion >= personas[u].getMensajes().size()){
										cout << endl << "Opcion Incorrecta" << endl;
										cout << "Escoga un mensaje valido: "; cin >> opcion;
										opcion -=1;
									
									}
									
									string mensaje = personas[u].getMensajes()[opcion];
									if (mensaje.size()/personas[u].getLlave() == 0){
									string newmensaje;
										for (int x = personas[u].getLlave(); x > 0 ; x--){
											string *arreglo = NULL;
											arreglo = new string [mensaje.size()/x];
											
											int contador = 0;											
		
											for (int i = 0; i < mensaje.size()/x; i++){
												for (int j = 0; j < x; j++){
													arreglo[i] += mensaje[contador];
													contador ++; 
												}
											}
											
											for (int i = 0; i < mensaje.size()/x; i++){
												if (i % 2 == 0){
													arreglo[i] = CesarAtras(arreglo[i],x);
												} else {
													arreglo[i] = CesarAdelante(arreglo[i],x);
												}
											}
											
											
											
											newmensaje = "";
											for (int i = 0;i < mensaje.size()/x; i++){
												for (int j = 0; j < x; j++){
													newmensaje += arreglo[i][j];
												}
											}
											mensaje = newmensaje;
											delete [] arreglo;
										}
									
									personas[opcion].getMensajes().push_back(mensaje);
								} else {
										string newmensaje;
										for (int x = personas[u].getLlave(); x > 0 ; x--){
											string *arreglo = NULL;
											arreglo = new string [mensaje.size()/x+1];
											
											int contador = 0;											
		
											for (int i = 0; i < mensaje.size()/x+1; i++){
												for (int j = 0; j < x; j++){
													arreglo[i] += mensaje[contador];
													contador ++; 
												}
											}
											
											for (int i = 0; i < mensaje.size()/x+1; i++){
												if (i % 2 == 0){
													arreglo[i] = CesarAtras(arreglo[i],x);
												} else {
													arreglo[i] = CesarAdelante(arreglo[i],x);
												}
											}
											
											
											
											newmensaje = "";
											for (int i = 0;i < mensaje.size()/x+1; i++){
												for (int j = 0; j < x; j++){
													newmensaje += arreglo[i][j];
												}
											}
											mensaje = newmensaje;
											delete [] arreglo;
											
										}
									
									cout << "El mensaje es: " << mensaje << endl;
								}
								}
								break;
							}
							case 3: {
								cout << "Tu llave es: " << personas[u].getLlave() << endl;
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
}
