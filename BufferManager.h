//
// Created by msumi on 20/05/2024.
//

#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "BufferPool.h"
#include "DiskManager.h"
#include "Replacer.h"
#include <iostream>
#include <unordered_map>
#include <queue>

enum class RequestType {
	READ,
	WRITE
};
/**
 * Gestiona el buffer, el cual es un conjunto de frames en memoria principal
 */
class BufferManager {
private:
	DiskManager* diskManRef; //Referencia al disk manager
	//key: pageId, value: frameId
	unordered_map<int,int> pageTable;
	//key: frameId, value: dirtyBit, pinCount y pinned
	tuple<bool, int, bool> frameInfo[NUM_FRAMES];
	//request queue for any page
	queue<RequestType> requestQueue[NUM_FRAMES];
	Replacer* replacer;//reemplazador
	BufferPool buffPool; // instancia del buffer pool
	int numFrames; // numero de frames
	int bufferSize; // tamaño del buffer
	int missCount; // contador de misses
	int hitCount; // contador de hits

	/**
	* Escribe el contenido de la pagina en disco
	* @param pageId: id de la pagina
	* @author Marko
	*/
	void writePage(int pageId);
	/**
 * Libera el frame que contiene a la pagina, escribe en disco si hay cambios
 * @param pageId: id de la pagina
 * @author Todos
 */
	bool flushPage(int pageId);
	/**
 * Obtiene el id de la pagina que esta en el frame
 * @param frameId: id del frame
 * @return id de la pagina que esta en el frame, -1 si no hay ninguna
 * @author Marko
 */
	int getPageidfromFrame(int frameId);
public:
	/**
	* Constructor: crea un BufferManager con la estrategia de reemplazo deseada
	* @param replacerType: LRU(1), Clock(2)
	* @author Marko
	*/
	BufferManager(int replacerType);
	~BufferManager();
	/**
	 * Establece la conexion con el disk manager
	 * @param diskManRef: referencia al disk manager
	 * @author Todos
	 */
	void setDiskManRef(DiskManager* diskManRef);//setea la referencia al disk manager
	/**
	 * Obtiene el contenido de una pagina en el buffer
	 * @param pageId: id de la pagina
	 * @return referencia a la pagina en el buffer
	 * @author Todos
	 */
	string* getPage(int pageId);
	/**
	* Verifica si la pagina esta en el buffer, incrementa el pincount
	* @param pageId: id de la pagina
	* @param requestType: tipo de request(READ, WRITE)
	* @return true si se pudo pinear la pagina, false en caso contrario
	* @author Todos
	*/
	bool pinPage(int pageId, RequestType requestType);
	/**
	 * Decrementa el pincount
	 * @param pageId: id de la pagina
	 * @author Todos
	 */
	void unpinPage(int pageId);
	/**
	 * Marca el dirty flag de la pagina
	 * @param pageId: id de la pagina
	 * @author Todos
	 */
	void setDirtyFlag(int pageId);
	/**
	 * Obtiene el contador de misses
	 * @return contador de misses
	 * @author Todos
	 */
	int getMissCount();
	/**
	 * Obtiene el contador de hits
	 * @return contador de hits
	 * @author Todos
	 */
	int getHitcount();
	/**
	 * Imprime la pageTable
	 * @author Todos
	 */
	void printPageTable();
	/**
	* Imprime el estado de las estructuras de reemplazo
	* @author Marko
	*/
	void printReplacer();
	void printRequestQueue();
	void pinningPage(int pageId);
	void unpinningPage(int pageId);
};



#endif //BUFFERMANAGER_H
