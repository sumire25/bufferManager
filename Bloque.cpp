//
// Created by msumi on 20/05/2024.
//

#include "Bloque.h"

Bloque::Bloque(int size) {
	contenido.resize(size);
}

string* Bloque::leerBloque() {
	return &contenido;
}

void Bloque::escribirBloque(string& contenido) {
	this->contenido = contenido;
}
