//
// Created by msumi on 20/05/2024.
//

#include "bufferManager.h"

bufferManager::bufferManager(int numBlocks, int blockSize, int numFrames): bufferPool(blockSize, numFrames) {
	this->numFrames = numFrames;
	this->bufferSize = blockSize*numFrames;
	hitCount = 0;
	missCount = 0;
	string myString = "";
	//inicializar freeFrames
	int i;
	for(i=0; i<numFrames; i++)
	{
		freeFrames.push(i);
	}
	//inicializar directorio de bloques
	directorio.resize(numBlocks);
	for(i=0; i<numBlocks; i++)
	{
		myString = "Bloque: "+std::to_string(i);
		directorio[i] = new Bloque(blockSize);
		directorio[i]->escribirBloque(myString);
	}
}

string * bufferManager::getPage(int pageId) {
	pinPage(pageId);
	int frameId = get<0>(pageTable[pageId]);

	return bufferPool.getFrameDirection(frameId);
}

// recibira una pagina que esta en un frame
void bufferManager::flushPage(int pageId) {
	//la escribira en disco si dirtyflag es true
	if(get<1>(pageTable[pageId])) {
		string * contenidoActual = bufferPool.getFrameDirection(get<0>(pageTable[pageId]));
		directorio[pageId]->escribirBloque(*contenidoActual);
	}
	//liberar frame
	freeFrames.push(get<0>(pageTable[pageId]));
	pageTable.erase(pageId);
	cerr<<"Flushing page: "<<pageId<<endl;
}

void bufferManager::pinPage(int pageId) {
	if(pageTable.find(pageId) == pageTable.end())
	{
		cout<<"misscount ++"<<endl;
		missCount++;
		//Buscar frames que mo sostengan bloques
		//Si no hay frames disponibles
		if(freeFrames.size() == 0) {
			int page;
			int pincountPage;
			for(auto it=LRUqueue.begin(); it != LRUqueue.end(); ++it) {
				if(get<2>(pageTable[*it]) == 0) {
					page = *it;
					LRUqueue.erase(it);
					break;
				}
			}
			flushPage(page);
		}

		//reservar frame
		int freeFrame = freeFrames.front();
		freeFrames.pop();
		//escribir contenido del bloque en el frame
		*bufferPool.getFrameDirection(freeFrame) = *directorio[pageId]->leerBloque();
		//registrar en el pagetable y el LRU
		pageTable[pageId] = make_tuple(freeFrame, false, 0);
		//push pagina en LRUqueue
		LRUqueue.push_back(pageId);

	} else {
		cout<<"hitcount ++"<<endl;
		hitCount++;
	}
	//incrementar pincount
	get<2>(pageTable[pageId])++;
}

void bufferManager::unpinPage(int pageId) {
	get<2>(pageTable[pageId])--;
	//actualizar posicion de la pagina en LRU queue
	for (auto it = LRUqueue.begin(); it != LRUqueue.end(); ++it) {
		if (*it == pageId) {
			LRUqueue.erase(it);
			LRUqueue.push_back(pageId);
			break;
		}
	}
}

void bufferManager::setDirtyFlag(int pageId) {
	get<1>(pageTable[pageId]) = true;
}

int bufferManager::getMissCount() {
	return missCount;
}

int bufferManager::getHitcount() {
	return hitCount;
}
