#include "bdfunciones.h"
#include <iostream>
#include <fstream>

bdfunciones func;

int main()
{
    //func.menuPrincipal();
    func.createBD();
    struct baseDatos bDatos = {1024,2,2,3,"Hixx"};
    func.writeBDBlock(1, bDatos);
    cout << "OK." ;
}
