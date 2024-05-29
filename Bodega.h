// archivo de encabezado de la clase Bodega
//contiene definiciones de funciones, definiciones de clases
#ifndef BODEGA_H
#define BODEGA_H
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>

using namespace std;
//Elaborado por : Josue Daniel Villagrán Pinto 9490-11-17319
struct Bodega {
    int codigo;
    char tipobodega[50];
    char nombre[50];
    char direccion[50];
    char estado[50];
};
class BodegaCRUD {
public:
    void Ingresar();
    void Modificar();
    void Borrar();
    void Desplegar();
    void CRUDBodega();
    bool Validar(int codigo);
};

#endif // BODEGA_H

// Usamos archivos de encabezado para tener un orden y mas limpio nuestro codigo y facil de encontrar errores


