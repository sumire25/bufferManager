//
// Created by msumi on 26/05/2024.
//

#include "DiskManager.h"

DiskManager::DiskManager(int numBlocks, int blockSize) {
	//inicializar directorio de bloques
	diskBlocks.resize(numBlocks);
	int i;
	string myString;
	for(i=0; i<numBlocks; i++)
	{
		myString = "Bloque: "+std::to_string(i);
		diskBlocks[i] = new Bloque(blockSize);
		diskBlocks[i]->escribirBloque(myString);
	}
}

string DiskManager::readBlock(int blockId) {
	return diskBlocks[blockId]->leerBloque();
}

void DiskManager::writeBlock(int blockId, string& content) {
	diskBlocks[blockId]->escribirBloque(content);
}
