//
// Created by msumi on 10/06/2024.
//

#ifndef REPLACER_H
#define REPLACER_H

#include <unordered_map>
#include <list>
using namespace std;

//Clase abstracta para las politicas de reemplazo
class Replacer {
protected:
	tuple<bool, int>* frameInfo;
	int numFrames;
public:
	Replacer(tuple<bool, int>* fi, int nf) : frameInfo(fi), numFrames(nf) {}
	virtual ~Replacer() = default;
	virtual int victim() = 0;
	virtual void handlePinning(int frameId) = 0;
	virtual void handleUnpinning(int frameId) = 0;
	virtual void print() = 0;
};

//Clase que implementa la politica de reempalzo LRU
class LruReplacer : public Replacer {
private:
	list<int> LRUqueue;
public:
	LruReplacer(tuple<bool, int>* fi, int nf) : Replacer(fi, nf) {

	}
};

#endif //REPLACER_H
