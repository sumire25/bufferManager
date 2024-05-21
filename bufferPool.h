//
// Created by msumi on 20/05/2024.
//

#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <string>
#include <vector>
using namespace std;

class bufferPool {
private:
	int numFrames;
	int bufferSize;
	vector<string> listFrame;
public:
	bufferPool(int blockSize, int numFrames);
	string* getFrameDirection(int frameId);// devuelve referencia del bloque en el buffer
};



#endif //BUFFERPOOL_H
