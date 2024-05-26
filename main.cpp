#include <iostream>
#include <string>

#include "Interfaz.h"

int main()
{
    int opc = 1;
    int bloque;
    std::string contenido;

    std::cout << "----------- BUFFER MANAGER -----------" <<std::endl;
    std::cout << "1. Indicar numero de bloques " <<std::endl;
    int numBlocks;
    std::cin >> numBlocks;
    std::cout << "2. Indicar tamaño del bloque  " <<std::endl;
    int tamBlock;
    std::cin >> tamBlock;
    std::cout << "3. Indicar numero de frames " <<std::endl;
    int numFrames;
    std::cin >> numFrames;

    //Interfaz interfaz(5, 10, 3);
    Interfaz interfaz(numBlocks, tamBlock, numFrames);


    do {
        std::cout << "----------- Operaciones -----------" <<std::endl;
        std::cout << "1. Leer bloque " <<std::endl;
        std::cout << "2. Escribir bloque " <<std::endl;
        std::cin >> opc;
        std::cout << "\n Inidique el id del bloque: " <<std::endl;

        switch (opc)
        {
        case 1: {
            
            std::cin >> bloque;
            interfaz.leerBloque(bloque);
        }
            break;
        
        case 2:{ //Hacer que lea un archivo
             
            std::cin >> bloque;
            std::cin >> contenido;
            interfaz.escribirBloque(bloque,contenido);
        }
            break;
        
        default:
            break;
        }


    } while (opc);

    cout << "Total Misscount: " << interfaz.getMissCount();
    cout << ", Total Hitcount: " << interfaz.getHitcount() << endl;
    
    return 0;
}
