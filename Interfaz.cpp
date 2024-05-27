//
// Created by msumi on 20/05/2024.
//

#include "Interfaz.h"

Interfaz::Interfaz(int numBlocks, int blockSize, int numFrames): buffManager(blockSize, numFrames), diskMan(numBlocks, blockSize) {
	buffManager.setDiskManRef(&diskMan);
}

void Interfaz::leerBloque(int numBlock) {
	cout<<*buffManager.getPage(numBlock)<<endl;
	buffManager.unpinPage(numBlock);
	buffManager.printPageTable();
	buffManager.printLRUqueue();
}

void Interfaz::escribirBloque(int numBloque, string contenido) {
	string* bloque = buffManager.getPage(numBloque);
	*bloque = contenido;
	buffManager.setDirtyFlag(numBloque);
	buffManager.unpinPage(numBloque);
	buffManager.printPageTable();
	buffManager.printLRUqueue();
}

void Interfaz::mostrarContadores() {
	cout << "Total Misscount: " << buffManager.getMissCount();
	cout << ", Total Hitcount: " << buffManager.getHitcount() << endl;
}
