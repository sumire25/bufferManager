#include <iostream>
#include <string>

#include "Interfaz.h"

int main()
{
    int opc = 1;
    int numBlocks = 5;
    int bloque;
    std::string contenido;

    Interfaz interfaz(numBlocks, 10, 3);
    do {
        std::cout << "1. Leer bloque " <<std::endl;
        std::cout << "2. Escribir bloque " <<std::endl;
        std::cin >> opc;

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
        
        default:
            break;
        }


    } while (opc);


    /*int numBlocks = 5;
    string contenido;
    Interfaz interfaz(numBlocks, 10, 3);
    for(int i=0; i<numBlocks; i++)
    {
        interfaz.leerBloque(i);
    }
    for(int i=0; i<numBlocks; i++)
    {
        getline(cin,contenido);
        interfaz.escribirBloque(i,contenido);
    }
    for(int i=0; i<numBlocks; i++)
    {
        interfaz.leerBloque(i);
    }*/
    cout<<"Misscount: "<<interfaz.getMissCount();
    cout<<", Hitcount: "<<interfaz.getHitcount()<<endl;
    return 0;
}
