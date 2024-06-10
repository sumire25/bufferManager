//
// Created by msumi on 20/05/2024.
//

#include "BufferManager.h"

BufferManager::BufferManager() {
	this->numFrames = NUM_FRAMES;
	this->bufferSize = PAGE_SIZE * NUM_FRAMES;
	// incializar hit y miss count
	hitCount = 0;
	missCount = 0;
	//inicializar lista freeFrames
	int i;
	for(i=0; i<numFrames; i++) freeFrames.push(i);
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
	if(get<1>(frameInfo[frameId]) != 0) {
		cerr << "No se puede liberar la pagina " << pageId << " porque esta siendo usada" << endl;
		return;
	}
	if(get<0>(frameInfo[frameId])) {
		string* page = buffPool.getFrameDirection(frameId);
		diskManRef->writeBlock(pageId, *page);
	}
	freeFrames.push(frameId);
	pageTable.erase(pageId);
	LRUqueue.pop_front();
	cerr<<"Flushing page: "<<pageId<<endl;
}

bool BufferManager::pinPage(int pageId) {
	if(pageTable.find(pageId) == pageTable.end()) {
		if(freeFrames.size() == 0) {
			if(!LRUqueue.empty()) {
				int page = LRUqueue.front();
				flushPage(page);
			}
			else {
				cerr << "No hay frames disponibles" << endl;
				return 0;
			}
		}
		int freeFrame = freeFrames.front();
		freeFrames.pop();
		*(buffPool.getFrameDirection(freeFrame)) = diskManRef->readBlock(pageId);
		pageTable[pageId] = freeFrame;
		frameInfo[freeFrame] = make_tuple(false, 0);
		cerr<<"misscount ++"<<endl;
		missCount++;
	} else {
		int frameId = pageTable[pageId];
		if(get<1>(frameInfo[frameId]) == 0) {
			for (auto it = LRUqueue.begin(); it != LRUqueue.end(); ++it) {
				if (*it == pageId) {
					LRUqueue.erase(it);
					break;
				}
			}
		}
		cout<<"hitcount ++"<<endl;
		hitCount++;
	}
	get<1>(frameInfo[pageTable[pageId]])++;
	return 1;
}

void BufferManager::unpinPage(int pageId) {
	if((--get<1>(frameInfo[pageTable[pageId]])) == 0)
		LRUqueue.push_back(pageId);
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

void BufferManager::printLRUqueue() {
	for (const int& item : LRUqueue) {
		cout << "| " << item << " | <- ";
	}
	cout << "end\n" << endl;
}
