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
	vector<Bloque*> directorio;
	bufferPool bufferPool;
	int numFrames;
	int bufferSize;
public:
	bufferManager(int numBlocks, int blockSize, int numFrames);
	//temporal
	void leerBloque(int numBloque);
};



#endif //BUFFERMANAGER_H
