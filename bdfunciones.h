#ifndef BDFUNCIONES_H
#define BDFUNCIONES_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

struct baseDatos{
    int espBD;       // Espacio Disponible en el bloque.
    int numTabla;    // Numero de las Tablas de la Base de Datos
    int pBloqTabla;  // Primer bloque con las tablas de la BD
    int sigBloBD;    // Siguiente bloque con informacion de BD
    char nombBD[5]; // Nombre de la Base de Datos
};

class bdfunciones
{
public:
    bdfunciones();
    int leerBD();
    int leerTabla(string nombreBD);
    void menuPrincipal();
    int createBD();
    int getBloqueLibre();
    int writeBDBlock(int numBloque, baseDatos structBD); // Recibira de Parametros el nombre de las BD;
    int writeTBBlock(); // Recibira de Parametros los nombres de las Tablas de una BD;
    int writeFLBlock(); // Recibira de Parametros los campos de una Tabla;
    int writeRGBlock(); // Recibira de Parametros los Registros de los campos de una Tabla;

};



struct bloqueTablas{
    int espTB, numCampo, pBloqCampo, sigBloTB;
    char nombTB[20];
};

struct bloqueCampos{
    int espCM, numCM, pBloqReg, sigBloCM;
    char nombCM[20];
};

struct bloqueRegistro{
    int espRG, numRG, sigBloRG;
    //Registros separados por -
};


#endif // BDFUNCIONES_H
