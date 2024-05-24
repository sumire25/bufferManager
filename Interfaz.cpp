//
// Created by msumi on 20/05/2024.
//

#include "Interfaz.h"

Interfaz::Interfaz(int numBlocks, int blockSize, int numFrames): buffManager(numBlocks, blockSize, numFrames) {
	this->blockSize = blockSize;
}

void Interfaz::leerBloque(int numBloque) {
	cout<<*buffManager.getPage(numBloque)<<endl;
	buffManager.unpinPage(numBloque);
}

void Interfaz::escribirBloque(int numBloque, string contenido) {
	string* bloque = buffManager.getPage(numBloque);
	*bloque = contenido;
	buffManager.setDirtyFlag(numBloque);
	buffManager.unpinPage(numBloque);
}

int Interfaz::getMissCount() {
	return buffManager.getMissCount();
}

int Interfaz::getHitcount() {
	return buffManager.getHitcount();
}
