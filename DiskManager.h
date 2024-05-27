//
// Created by msumi on 26/05/2024.
//

#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <vector>
#include "Bloque.h"

/**
 * Clase que se encarga de la escritura y lectura del disco
 */
class DiskManager {
	vector<Bloque*> diskBlocks;
public:
	DiskManager(int numBlocks, int blockSize);
	/**
	* @param blockId: identificador del bloque a leer
	* @return contenido del bloque
	*/
	string readBlock(int blockId);

	/**
	 *
	 * @param blockId: identificador del bloque a escribir
	 * @param content: contenido a escribir
	 */
	void writeBlock(int blockId, string& content);
};



#endif //DISKMANAGER_H
