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
    std::cout << "1. Usar LRU Replacer  " <<std::endl;
    std::cout << "2. Usar Clock Replacer " <<std::endl;
    cin>> opc;

    Interfaz interfaz(opc);

    do {
        std::cout << "----------- Operaciones -----------" <<std::endl;
        std::cout << "1. Leer bloque " <<std::endl;
        std::cout << "2. Escribir bloque " <<std::endl;
        std::cout << "3. Liberar bloque " <<std::endl;
        std::cout << "4. Despinear bloque " <<std::endl;
        std::cin >> opc;
        std::cout << "\n Indique el id del bloque: " <<std::endl;

        switch (opc)
        {
        case 1: {
            std::cin >> bloque;
            interfaz.leerBloque(bloque);
            cout << "Pinear pagina: si(1), no(2)\n";
            cin >> opc;
            if(opc == 1)
                interfaz.pinPage(bloque);
            interfaz.print();
        }
            break;
        
        case 2:{
            std::cin >> bloque;
            std::cin >> contenido;
            interfaz.escribirBloque(bloque,contenido);
            cout << "Pinear pagina: si(1), no(2)\n";
            cin >> opc;
            if(opc == 1)
                interfaz.pinPage(bloque);
            interfaz.print();
        }
            break;

        case 3:{
            std::cin >> bloque;
            interfaz.liberarBloque(bloque);
            interfaz.print();
        }
            break;
        case 4: {
            std::cin >> bloque;
            interfaz.unpinPage(bloque);
            interfaz.print();
        }
            break;
        default:
            break;
        }
    } while (opc);

    interfaz.mostrarContadores();
    
    return 0;
}
