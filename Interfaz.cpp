//
// Created by msumi on 20/05/2024.
//

#include "Interfaz.h"

#include <utility>

Interfaz::Interfaz(int replacerType): buffManager(replacerType), diskMan(5, PAGE_SIZE) {
	buffManager.setDiskManRef(&diskMan);
}

void Interfaz::leerBloque(int numBlock) {
	string* bloque = buffManager.getPage(numBlock);
	if(bloque != nullptr) {
		cout<<*bloque<<endl;
		buffManager.printPageTable();
		buffManager.printReplacer();
	}
}

void Interfaz::escribirBloque(int numBloque, string contenido) {
	string* bloque = buffManager.getPage(numBloque);
	if(bloque != nullptr) {
		*bloque = std::move(contenido);
		buffManager.setDirtyFlag(numBloque);
		buffManager.printPageTable();
		buffManager.printReplacer();
	}
}

void Interfaz::liberarBloque(int numBloque) {
	buffManager.unpinPage(numBloque);
	buffManager.printPageTable();
	buffManager.printReplacer();
}

void Interfaz::mostrarContadores() {
	cout << "Total Misscount: " << buffManager.getMissCount();
	cout << ", Total Hitcount: " << buffManager.getHitcount() << endl;
}
