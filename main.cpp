#include <iostream>
#include <string>

#include "Interfaz.h"

int main()
{
    int numBlocks = 5;
    Interfaz interfaz(numBlocks, 10, 3);
    for(int i=0; i<numBlocks; i++)
    {
        interfaz.leerBloque(i);
    }
    return 0;
}
