//
// Created by msumi on 20/05/2024.
//

#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <string>
#include <vector>
using namespace std;

// Clase que almacena los frames en la memoria principal
class BufferPool {
private:
	int numFrames; // numero de frames
	int bufferSize; // tamaño del buffer
	vector<string> listFrame; // lista de frames
public:
	BufferPool(int blockSize, int numFrames);
	/**
	 * Obtiene la direccion de un frame en el buffer
	 * @param frameId: id del frame
	 * @return direccion del frame en el buffer
	 * @author Todos
	 */
	string* getFrameDirection(int frameId);
};

#endif //BUFFERPOOL_H
