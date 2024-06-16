//
// Created by msumi on 20/05/2024.
//

#include "Interfaz.h"

#include <utility>

Interfaz::Interfaz(int replacerType): buffManager(replacerType), diskMan(5, PAGE_SIZE) {
	buffManager.setDiskManRef(&diskMan);
}

void Interfaz::leerBloque(int numBlock) {
	if(!buffManager.pinPage(numBlock, RequestType::READ)) return;
	string* bloque = buffManager.getPage(numBlock);
	cout<<*bloque<<endl;
}

void Interfaz::escribirBloque(int numBloque) {
	if(!buffManager.pinPage(numBloque, RequestType::WRITE)) return;
	string* bloque = buffManager.getPage(numBloque);
	cout<<*bloque<<endl;
}

void Interfaz::liberarBloque(int numBloque) {
	buffManager.unpinPage(numBloque);
}

void Interfaz::mostrarContadores() {
	cout << "Total Misscount: " << buffManager.getMissCount();
	cout << ", Total Hitcount: " << buffManager.getHitcount() << endl;
}

void Interfaz::pinPage(int numBloque) {
	buffManager.pinningPage(numBloque);
}

void Interfaz::unpinPage(int numBloque) {
	buffManager.unpinningPage(numBloque);
}

void Interfaz::print() {
	buffManager.printRequestQueue();
	buffManager.printPageTable();
	buffManager.printReplacer();
}
