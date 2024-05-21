//
// Created by msumi on 20/05/2024.
//

#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "bufferPool.h";
#include "Bloque.h";
#include <iostream>

class bufferManager {
private:
	//Page table: Dictionario
	vector<Bloque*> directorio;
	bufferPool bufferPool;
	int numFrames;
	int bufferSize;
public:
	bufferManager(int numBlocks, int blockSize, int numFrames);
	//IMPORTANTE
	string* getPage(int pageId);// devuelve referencia del bloque en el buffer
	void flushPage(int pageId);// libera el frame que contiene al bloque, escribe en disco si hay cambios

	//temporal
	void leerBloque(int numBloque);
};



#endif //BUFFERMANAGER_H
