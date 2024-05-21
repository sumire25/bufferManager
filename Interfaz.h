//
// Created by msumi on 20/05/2024.
//

#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "bufferManager.h"

class Interfaz {
private:
	bufferManager buffManager;
	int blockSize;
public:
	Interfaz(int numBlocks, int blockSize, int numFrames);
	void leerBloque(int numBloque);// Deberia de retornar el contenido de un bloque, consultando al buffermanager
};



#endif //INTERFAZ_H
