//
// Created by msumi on 20/05/2024.
//

#ifndef BLOQUE_H
#define BLOQUE_H

#include<string>
using namespace std;

class Bloque {
private:
	string contenido;
public:
	Bloque(int size);
	string* leerBloque();
	void escribirBloque(string contenido);
};



#endif //BLOQUE_H
