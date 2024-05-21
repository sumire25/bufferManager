//
// Created by msumi on 20/05/2024.
//

#include "bufferManager.h"

bufferManager::bufferManager(int numBlocks, int blockSize, int numFrames): bufferPool(blockSize, numFrames) {
	this->numFrames = numFrames;
	this->bufferSize = blockSize*numFrames;
	string myString = "";
	directorio.resize(numBlocks);
	for(int i=0; i<numBlocks; i++)
	{
		myString = "Bloque: "+std::to_string(i);
		directorio[i] = new Bloque(blockSize);
		directorio[i]->escribirBloque(myString);
	}
}

void bufferManager::leerBloque(int numBloque) {
	cout<<*directorio[numBloque]->leerBloque()<<endl;
}
