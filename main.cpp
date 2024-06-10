#include <iostream>
#include <string>

#include "Interfaz.h"

int main()
{
    int opc = 1;
    int bloque;
    std::string contenido;

    //Configuracion inicial
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
    Interfaz interfaz;


    do {
        std::cout << "----------- Operaciones -----------" <<std::endl;
        std::cout << "1. Leer bloque " <<std::endl;
        std::cout << "2. Escribir bloque " <<std::endl;
        std::cout << "3. Liberar bloque " <<std::endl;
        std::cin >> opc;
        std::cout << "\n Indique el id del bloque: " <<std::endl;

        switch (opc)
        {
        case 1: {
            std::cin >> bloque;
            interfaz.leerBloque(bloque);
        }
            break;
        
        case 2:{
            std::cin >> bloque;
            std::cin >> contenido;
            interfaz.escribirBloque(bloque,contenido);
        }
            break;

        case 3:{
            std::cin >> bloque;
            interfaz.liberarBloque(bloque);
        }
            break;

        default:
            break;
        }


    } while (opc);

    interfaz.mostrarContadores();
    
    return 0;
}
