//
// Created by msumi on 20/05/2024.
//

#include "bufferPool.h"

bufferPool::bufferPool(int blockSize, int numFrames) {
	this->numFrames = numFrames;
	this->bufferSize = numFrames * blockSize;
	listFrame.resize(numFrames);
	for(int i=0; i<numFrames; i++)
	{
		listFrame[i] = "";
	}
}

string * bufferPool::getFrameDirection(int frameId) {
	return &listFrame[frameId];
}
