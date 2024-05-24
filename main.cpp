#include <iostream>
#include <string>

#include "Interfaz.h"

int main()
{
    int numBlocks = 5;
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
    }
    cout<<"Misscount: "<<interfaz.getMissCount();
    cout<<", Hitcount: "<<interfaz.getHitcount()<<endl;
    return 0;
}
