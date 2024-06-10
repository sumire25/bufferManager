//
// Created by msumi on 20/05/2024.
//

#include "BufferPool.h"

BufferPool::BufferPool(int blockSize, int numFrames) {
	this->numFrames = numFrames;
	this->bufferSize = numFrames * blockSize;
	listFrame.resize(numFrames);
	for(int i=0; i<numFrames; i++)
	{
		listFrame[i] = "";
	}
}

string * BufferPool::getFrameDirection(int frameId) {
	return &listFrame[frameId];
}
