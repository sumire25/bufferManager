//
// Created by msumi on 20/05/2024.
//

#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "bufferManager.h"
#include "DiskManager.h"

/**
 * Clase que se encarga de la interacción con el usuario
 */
class Interfaz {
private:
	DiskManager diskMan;//instancia del diskManager
	bufferManager buffManager;//instancia del bufferManager
public:
	/**
	 * Constructor: crea un bufferManager con los parámetros dados
	 * @param numBlocks: cantidad de bloques, blocksize: tamaño de los bloques, numFrames: cantidad de frames
	 * @author Todos
	 */
	Interfaz(int numBlocks, int blockSize, int numFrames);
	/**
	 * Imprime el contenido del bloque dado su identificador
	 * @param numBlock: identificador del bloque
	 * @author Todos
	 */
	void leerBloque(int numBlock);// Deberia de retornar el contenido de un bloque, consultando al buffermanager
	/**
	* Escribe en el bloque cuyo identificador es dado
	* @param numBlock: identificador del bloque
	* @author Todos
	*/
	void escribirBloque(int numBloque, string contenido);
	/**
	 * Imprime los cantidad de misses y hits
	 * @author Todos
	 */
	void mostrarContadores();
};



#endif //INTERFAZ_H
