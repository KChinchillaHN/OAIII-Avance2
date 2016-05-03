#include "bdfunciones.h"
#include <cstring>
#include <math.h>
#include <stdio.h>

ifstream arcFunL;
ofstream arcFunE;
FILE *f;
int numBDG=0, bloqLibre=0;
string nomBD[1];
int numTabBD[1];
bdfunciones bdfunc;
int block_size=512, block_count=2048, pos=0;

bdfunciones::bdfunciones()
{

}

int bdfunciones:: getBloqueLibre(){
    rewind(f);
    fscanf(f,"%i",&bloqLibre);
    return bloqLibre;
}

int bdfunciones::leerTabla(string nombreBD)
{
    int numCampos;
    char line[1000]; // Proximo avance sera un String para no tener que colocar limite
    char *token;
    nombreBD+=".txt";
    arcFunL.open(nombreBD);
    if (!(arcFunL.is_open())){
        cout<<"Archivo se abrio de manera incorrecta \n";
        return 0;
    }
    while (arcFunL >> line){
    //cout << "Linea: "<< line<< "\n";
    token=strtok(line,"-");
    string aux(token);
    numCampos=atoi(aux.c_str());
    token=strtok(NULL,"-");
    cout<< "Nombre de la Tabla: " << token << "\n" << " - - - - - - - - -" << "\n";
    for(int i=0;i<numCampos;i++){
        token=strtok(NULL,"-");
        cout << i+1 << ". "<< token << " \n";
    }
    cout<< " \n";
    }
    arcFunL.close();
}

int bdfunciones::leerBD(){
    int numBD, cont=0, numTab;
    char line[100]; // Proximo avance sera un String para no tener que colocar limite
    char *token;
    int opcBD;
    string opcion="OK";

    arcFunL.open("BDProyecto.txt");
    if (!(arcFunL.is_open())){
        cout<<"Archivo se abrio de manera incorrecta \n";
        return 0;
    }
    arcFunL >> numBD;
    numBDG=numBD;
    string *nomBD = new string[numBD];
    int *numTabBD = new int[numBD];
    while (arcFunL >> line){
        token=strtok(line,"-");
        string aux(token);
        nomBD[cont]=aux;
        token=strtok(NULL," ");
        string aux2(token);
        numTab=atoi(aux2.c_str());
        numTabBD[cont]=numTab;
        cont++;
    }
    arcFunL.close();
    cout<< "\n" <<"Base de Datos Disponibles: \n";
        cout<< "   Nombre BD - - - Num. de Tablas \n";
    for(int i=0;i<numBDG;i++){
        cout<<i+1<<". "<<nomBD[i] << " - - - " << numTabBD[i] << "\n";
    }
    while(opcion=="OK"){
    cout<< "\n\n" << "Ingrese el numero de la BD: ";
    cin >> opcBD;
    if(opcBD>=1 && opcBD<=(numBD+1)){
        opcion="NOOK";
        string auxName=nomBD[(opcBD-1)];
        bdfunc.leerTabla(auxName);
        menuPrincipal();
    }
    else{
        opcion="OK";
    }
    return 1;
}
}

void bdfunciones::menuPrincipal()
{
    int opcPri;
    string opcion="OK";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n";
    cout<<" * Menu de Mantenimiento de Base de Datos  * \n";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n\n";
    cout<<"1. Ver BD disponibles. \n";
    cout<<"2. Salir del Sistema \n\n";
    while(opcion=="OK"){
    cout<<"Ingrese un numero: ";
    cin>>opcPri;
        if(opcPri>=1 && opcPri<=2){
            opcion="NOOK";
            switch (opcPri){
                case 1:
                    bdfunc.leerBD();
                case 2:
                    exit(1);
                default: "El valor ingresado no se encuentra permitido. \n";
            }
        }
        else{
        opcion="OK";
        }
    }

    /*
    func.leerBD();
    func.leerTabla("BDPrueba1");
    */
}

int bdfunciones::createBD()
{
    /*
     * Tamano de los bloques: 1024Bytes
     * # de Bloques: 1024
     * Tamano Total de la BD 1024*1024 = 1MB
     */
    int i;
    char *buffer=(char*)malloc(block_size);
    if(buffer==NULL){
        return -2; // No se ha podido reservar el espacio de memoria.
    }
    f=fopen("BDFile.dat","w"); //Creo el archivo maestro de las BD.
    if(f==NULL){
        return -1; // Error al abrir el archivo.
    }
    fprintf(f,"%i",bloqLibre); // Indicador del siguiente bloque Libre
    fprintf(f,"%i",block_size);
    fprintf(f,"%i",block_count);
    memset(buffer,'*',block_size);
    for(i=0 ; i<block_count; i++){
        fwrite(buffer,(sizeof(char)),block_size,f);
    }
    fclose(f);
    free(buffer);
    return 0; // El proceso se llevo a cabo con exito.
}

int bdfunciones::writeBDBlock(int numBloque, baseDatos structBD)
{
    f=fopen("BDFile.dat","rw+");
    if(f==NULL){
        cout << "Error \n"; // No se pudo abrir el archivo, Verifique que exista.
    }
    cout << "Valor de F: " << f << "\n";
    pos=((numBloque*block_size)-block_size)+4;
    fseek(f,pos,SEEK_SET);
    cout<< "espBD: " << structBD.espBD << "\n";
    fwrite(&structBD,sizeof(structBD),1,f);

    return 1;
    fclose(f);
}


