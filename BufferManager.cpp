//
// Created by msumi on 20/05/2024.
//

#include "BufferManager.h"

BufferManager::BufferManager(int replacerType) {
	this->numFrames = NUM_FRAMES;
	this->bufferSize = PAGE_SIZE * NUM_FRAMES;
	// incializar hit y miss count
	hitCount = 0;
	missCount = 0;
	//inicializar frameInfo
	for(int i=0; i<numFrames; i++) frameInfo[i] = make_tuple(false, 0);
	//inicializar replacer
	if(replacerType == 2) replacer = new ClockReplacer(frameInfo, numFrames);
	else replacer = new LruReplacer(frameInfo, numFrames);
}

BufferManager::~BufferManager() {
	for (const auto& entry : pageTable) {
		int key = entry.first;
		int frameId = entry.second;
		if(get<0>(frameInfo[frameId])) {
			string* page = buffPool.getFrameDirection(frameId);
			diskManRef->writeBlock(key, *page);
		}
	}
}

void BufferManager::setDiskManRef(DiskManager *diskManRef) {
	this->diskManRef = diskManRef;
}

string * BufferManager::getPage(int pageId) {
	// pinear pagina
	if(pinPage(pageId)) {
		// retornar direccion del frame que sostiene a la pagina
		return buffPool.getFrameDirection(pageTable[pageId]);
	}
	return nullptr;
}

void BufferManager::flushPage(int pageId) {
	int frameId = pageTable[pageId];
	if(get<1>(frameInfo[frameId]) != 0) {// si la pagina esta pinned
		cerr << "No se puede liberar la pagina " << pageId << " porque esta siendo usada" << endl;
		return;
	}
	if(get<0>(frameInfo[frameId])) {// la escribira en disco si dirtyflag es true
		string* page = buffPool.getFrameDirection(frameId);
		diskManRef->writeBlock(pageId, *page);
	}
	pageTable.erase(pageId);// eliminar seguimiento de la pagina del pagetable
	cerr<<"Flushing page: "<<pageId<<endl;
}

bool BufferManager::pinPage(int pageId) {
	int frameId;
	if(pageTable.find(pageId) == pageTable.end()) {// Si la pagina no esta en el BufferPool
		frameId = replacer->getVictim();//obtener el victimFrame
		if(frameId == -1) {// Si no hay frames disponibles
			cerr << "No hay frames disponibles" << endl;
			return false;
		}
		int victimPage = getPageidfromFrame(frameId);
		if(victimPage != -1) {// Si el victimFrame tiene una pagina
			flushPage(victimPage);
		}
		//cargar la pagina en el frame y actualizar el pageTable
		pageTable[pageId] = frameId;
		frameInfo[frameId] = make_tuple(false, 0);
		*(buffPool.getFrameDirection(frameId)) = diskManRef->readBlock(pageId);
		cerr<<"misscount ++"<<endl;
		missCount++;
	}
	else {// Si la pagina esta en el BufferPool
		frameId = pageTable[pageId];
		cout<<"hitcount ++"<<endl;
		hitCount++;
	}
	//pinnear la pagina
	get<1>(frameInfo[pageTable[pageId]])++;
	replacer->handlePinning(frameId);
	return true;
}

int BufferManager::getPageidfromFrame(int frameId) {
	int victimPage = -1;
	for (const auto& entry : pageTable) {
		if(entry.second == frameId) {
			victimPage = entry.first;
			break;
		}
	}
	return victimPage;
}

void BufferManager::unpinPage(int pageId) {
	if((--get<1>(frameInfo[pageTable[pageId]])) == 0)//si la pagina esta unpinned
		replacer->handleUnpinning(pageTable[pageId]);//actualizar el estado del frame en el reemplazador
}

void BufferManager::setDirtyFlag(int pageId) {
	get<0>(frameInfo[pageTable[pageId]]) = true;
}

int BufferManager::getMissCount() {
	return missCount;
}

int BufferManager::getHitcount() {
	return hitCount;
}

void BufferManager::printPageTable() {
	cout << "\t----------------------------------------------" << endl;
	cout << "\t| Page ID | Frame ID | dirty bit | pin count |" << endl;
	for (const auto& entry : pageTable) {
		int key = entry.first;
		int frameId = entry.second;

		bool dirtyBit = get<0>(frameInfo[frameId]);
		int pinCount = get<1>(frameInfo[frameId]);

		cout << "\t----------------------------------------------" << endl;
		cout << "\t|    " << key << "    |    " << frameId << "     |     " << dirtyBit << "     |     " << pinCount << "     |" << endl;
	}
	cout << "\t----------------------------------------------\n" << endl;
}

void BufferManager::printReplacer() {
	replacer->print();
}
