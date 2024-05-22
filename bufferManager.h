//
// Created by msumi on 20/05/2024.
//

#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "bufferPool.h";
#include "Bloque.h";
#include <iostream>
#include <unordered_map>
#include <queue>

struct Node {
	int value;
	Node* next;
	Node* prev;
};

class bufferManager {
private:
	//key: pageId, value: <frameId, dirtyBit, pinCount>
	unordered_map<int,tuple<int, bool, int>> pageTable;
	Node* LRUHead;
	queue<int> freeFrames;
	vector<Bloque*> directorio;
	bufferPool bufferPool;
	int numFrames;
	int bufferSize;
	int missCount;
	int hitCount;
public:
	bufferManager(int numBlocks, int blockSize, int numFrames);
	//IMPORTANTE
	string* getPage(int pageId);// devuelve referencia del bloque en el buffer
	void flushPage(int pageId);// libera el frame que contiene al bloque, escribe en disco si hay cambios
	void pinPage(int pageId);//verifica si esta en el buuffer, incrementa el pincount
	void unpinPage(int pageId);//decrementa el pincount
	void setDirtyFlag(int pageId);//marca el dirty flag
};



#endif //BUFFERMANAGER_H
