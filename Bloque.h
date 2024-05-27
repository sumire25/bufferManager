//
// Created by msumi on 20/05/2024.
//

#ifndef BLOQUE_H
#define BLOQUE_H

#include<string>
using namespace std;

/**
 * Clase que simula un bloque en disco
 */
class Bloque {
private:
	string contenido;
public:
	/**
	* Constructor: crea un bloque con el tamaño dado
	* @param size: tamaño del bloque
	* @author Todos
	*/
	Bloque(int size);
	/**
	* Simula la lectura de un bloque del disco
	* @return Un puntero al contenido del bloque
	* @author Todos
	*/
	string leerBloque();
	/**
	* Simula la escritura de un bloque al disco
	* @param conternido: contenido a escribir en el bloque
	* @author Todos
	*/
	void escribirBloque(string contenido);
};



#endif //BLOQUE_H
