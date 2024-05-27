//
// Created by msumi on 20/05/2024.
//

#include "bufferManager.h"

bufferManager::bufferManager(int blockSize, int numFrames): buffPool(blockSize, numFrames) {
	this->numFrames = numFrames;
	this->bufferSize = blockSize*numFrames;
	// incializar hit y miss count
	hitCount = 0;
	missCount = 0;
	//inicializar lista freeFrames
	int i;
	for(i=0; i<numFrames; i++) freeFrames.push(i);
}

void bufferManager::setDiskManRef(DiskManager *diskManRef) {
	this->diskManRef = diskManRef;
}

string * bufferManager::getPage(int pageId) {
	// pinear pagina
	pinPage(pageId);
	// retornar direccion del frame que sostiene a la pagina
	int frameId = get<0>(pageTable[pageId]);
	return buffPool.getFrameDirection(frameId);
}

void bufferManager::flushPage(int pageId) { // recibira una pagina que esta en un frame
	if(get<2>(pageTable[pageId]) != 0) {
		cerr << "No se puede liberar la pagina " << pageId << " porque esta siendo usada" << endl;
		return;
	}
	if(get<1>(pageTable[pageId])) { // la escribira en disco si dirtyflag es true
		string* contenidoActual = buffPool.getFrameDirection(get<0>(pageTable[pageId]));
		diskManRef->writeBlock(pageId, *contenidoActual);
	}
	//liberar frame
	freeFrames.push(get<0>(pageTable[pageId]));// agregar frameId a la lista de frames libres
	pageTable.erase(pageId);// eliminar seguimiento de la pagina del pagetable
	LRUqueue.pop_front();// eliminar pagina de la cola LRU
	cerr<<"Flushing page: "<<pageId<<endl; // mensaje de depuracion
}

void bufferManager::pinPage(int pageId) {
	if(pageTable.find(pageId) == pageTable.end()) // Si la pagina no esta en el bufferPool
	{
		cout<<"misscount ++"<<endl;
		missCount++;
		if(freeFrames.size() == 0) { //Si no hay frames disponibles
			int page = LRUqueue.front();
			flushPage(page);// liberamos el frame de la cabecera de la LRUqueue
		}
		//reservar frame
		int freeFrame = freeFrames.front();
		freeFrames.pop();
		//escribir contenido del bloque en el frame
		*buffPool.getFrameDirection(freeFrame) = diskManRef->readBlock(pageId);
		//registrar en el pagetable
		pageTable[pageId] = make_tuple(freeFrame, false, 0);
	} else {
		if(get<2>(pageTable[pageId]) == 0) { // Si esta unpinned
			for (auto it = LRUqueue.begin(); it != LRUqueue.end(); ++it) {
				if (*it == pageId) {
					LRUqueue.erase(it); //lo retiramos del LRUqueue
					break;
				}
			}
		}
		cout<<"hitcount ++"<<endl;
		hitCount++;
	}
	get<2>(pageTable[pageId])++; //incrementar pincount
}

void bufferManager::unpinPage(int pageId) {
	if((--get<2>(pageTable[pageId])) == 0)// decrementar pincount y verificar si esta unpinned
		LRUqueue.push_back(pageId); //intrducir la pagina en LRU queue
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

void bufferManager::printPageTable() {
	cout << "\t----------------------------------------------" << endl;
	cout << "\t| Page ID | Frame ID | dirty bit | pin count |" << endl;
	for (const auto& entry : pageTable) {
		int key = entry.first;
		const tuple<int, bool, int>& value = entry.second;

		int firstElement = get<0>(value);
		int secondElement = get<1>(value);
		int thirdElement = get<2>(value);

		cout << "\t----------------------------------------------" << endl;
		cout << "\t|    " << key << "    |    " << firstElement << "     |     " << secondElement << "     |     " << thirdElement << "     |" << endl;
	}
	cout << "\t----------------------------------------------\n" << endl;
}

void bufferManager::printLRUqueue() {
	for (const int& item : LRUqueue) {
		cout << "| " << item << " | <- ";
	}
	cout << "end\n" << endl;
}
