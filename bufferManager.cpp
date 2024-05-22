//
// Created by msumi on 20/05/2024.
//

#include "bufferManager.h"

void push(Node** head, int value) {
	Node* newNode = new Node();
	newNode->value = value;
	if (*head == NULL) {
		newNode->next = newNode->prev = newNode;
		*head = newNode;
	} else {
		Node* tail = (*head)->prev;
		newNode->next = *head;
		newNode->prev = tail;
		tail->next = newNode;
		(*head)->prev = newNode;
	}
}

Node* search(Node** head, int value) {
	if (*head == NULL) {
		return NULL;
	}
	Node* current = *head;
	do {
		if (current->value == value) {
			return current;
		}
		current = current->next;
	} while (current != *head);
	return NULL;
}

void remove(Node** head, Node* node) {
	if (node == NULL || *head == NULL) return;
	if (node->next == node) { // Only one node in the list
		*head = NULL;
	} else {
		Node* nextNode = node->next;
		Node* prevNode = node->prev;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		if (node == *head) {
			*head = nextNode;
		}
	}
	delete node;
}

void move(Node** head, int value) {
	Node* node = search(head, value);
	if (node) {
		remove(head, node);
		push(head, value);
	}
}

int pop(Node** head) {
	if (*head == NULL) {
		std::cerr << "List is empty." << std::endl;
		return -1; // or throw an exception
	}
	Node* oldHead = *head;
	int data = oldHead->value;
	if (oldHead->next == oldHead) { // Only one node in the list
		*head = NULL;
	} else {
		Node* newHead = oldHead->next;
		Node* tail = oldHead->prev;
		tail->next = newHead;
		newHead->prev = tail;
		*head = newHead;
	}
	delete oldHead;
	return data;
}

void printList(Node* head) {
	if (head == NULL) return;
	Node* current = head;
	do {
		std::cout << current->value << " ";
		current = current->next;
	} while (current != head);
	std::cout << std::endl;
}

bufferManager::bufferManager(int numBlocks, int blockSize, int numFrames): bufferPool(blockSize, numFrames) {
	this->numFrames = numFrames;
	this->bufferSize = blockSize*numFrames;
	string myString = "";
	int i;
	//inicializar LRUhead
	LRUHead = NULL;
	//inicializar freeFrames
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
	//la escribira en disco
	if(get<1>(pageTable[pageId])) {
		string * contenidoActual = bufferPool.getFrameDirection(get<0>(pageTable[pageId]));
		directorio[pageId]->escribirBloque(*contenidoActual);
	}
	//liberar frame
	pageTable.erase(pageId);
	freeFrames.push(get<0>(pageTable[pageId]));
	cerr<<"Flushing page: "<<pageId<<endl;
}

void bufferManager::pinPage(int pageId) {
	if(pageTable.find(pageId) == pageTable.end())
	{
		cerr<<"Page not found in buffer"<<endl;
		missCount++;
		//Buscar frames que mo sostengan bloques
		//Si no hay frames disponibles
		if(freeFrames.size() == 0) {
			int page;
			int pincountPage;
			do {
				page = pop(&LRUHead);// sacar pagina de LRU queue
				pincountPage = get<2>(pageTable[page]);
			}while(pincountPage);
			flushPage(page);
		}

		//reservar frame
		int freeFrame = freeFrames.front();
		freeFrames.pop();
		//escribir contenido del bloque en el frame
		*bufferPool.getFrameDirection(freeFrame) = *directorio[pageId]->leerBloque();
		//registrar en el pagetable y el LRU
		pageTable[pageId] = make_tuple(freeFrame, false, 0);
		//push pagina en LRU queue
		push(&LRUHead, pageId);
	} else {
		hitCount++;
	}
	//incrementar pincount
	get<2>(pageTable[pageId])++;
	//actualizar posicion de la pagina en LRU queue
	move(&LRUHead, pageId);
}

void bufferManager::unpinPage(int pageId) {
	get<2>(pageTable[pageId])--;
}

void bufferManager::setDirtyFlag(int pageId) {
	get<1>(pageTable[pageId]) = true;
}
