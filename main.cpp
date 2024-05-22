#include <iostream>
#include <string>

#include "Interfaz.h"

int main()
{
    int numBlocks = 40;
    Interfaz interfaz(numBlocks, 10, 5);
    for(int i=0; i<numBlocks; i++)
    {
        interfaz.leerBloque(i);
    }
    return 0;
}
