//
// Created by msumi on 20/05/2024.
//

#include "Interfaz.h"

#include <utility>

Interfaz::Interfaz(int numBlocks, int blockSize, int numFrames): buffManager(blockSize, numFrames), diskMan(numBlocks, blockSize) {
	buffManager.setDiskManRef(&diskMan);
}

void Interfaz::leerBloque(int numBlock) {
	string* bloque = buffManager.getPage(numBlock);
	if(bloque != nullptr) {
		cout<<*bloque<<endl;
		buffManager.printPageTable();
		buffManager.printLRUqueue();
	}
}

void Interfaz::escribirBloque(int numBloque, string contenido) {
	string* bloque = buffManager.getPage(numBloque);
	if(bloque != nullptr) {
		*bloque = std::move(contenido);
		buffManager.setDirtyFlag(numBloque);
		buffManager.printPageTable();
		buffManager.printLRUqueue();
	}
}

void Interfaz::liberarBloque(int numBloque) {
	buffManager.unpinPage(numBloque);
	buffManager.printPageTable();
	buffManager.printLRUqueue();
}

void Interfaz::mostrarContadores() {
	cout << "Total Misscount: " << buffManager.getMissCount();
	cout << ", Total Hitcount: " << buffManager.getHitcount() << endl;
}
