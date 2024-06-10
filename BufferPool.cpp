//
// Created by msumi on 20/05/2024.
//

#include "BufferPool.h"

BufferPool::BufferPool() {
	framelist = new string[NUM_FRAMES];
}

BufferPool::~BufferPool() {
	delete[] framelist;
}

string * BufferPool::getFrameDirection(int frameId) {
	return &framelist[frameId];
}
