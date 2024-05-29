//Aqui se encuentra el archivos de implentación de la clase CARRERA que contiene todo el codigo fuente
//del funcionamiento del la clase
#include "Bodega.h"
#include "usuarios.h"
#include "Login.h"
#include "Bitacora.h"
#include <fstream>
#include <iostream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
using namespace std;
//Elaboracion de CRUD y Bitacora: Carlos David calderón Ramírez      9959-23-848
//Comentado revisado y depurado por:  Evelyn Sofía Andrade Luna   9959-23-1224
// menu CRUD de carreras



void BodegaCRUD::CRUDBodega() {
int choice;
    //int x;
    do {
	system("cls");
	cout<<"\t\t\t--------------------------------------------"<<endl;
	cout<<"\t\t\t|       SISTEMA  ERP | CRUD BODEGA          |"<<endl;
	cout<<"\t\t\t--------------------------------------------"<<endl;
	cout<<"\t\t\t  BODEGAS: "<<endl;
	cout<<"\t\t\t 1. Crear "<<endl;
	cout<<"\t\t\t 2. Modificar "<<endl;
	cout<<"\t\t\t 3. Borrar "<<endl;
	cout<<"\t\t\t 4. Desplegar "<<endl;
	cout<<"\t\t\t 5. Regresar Menu Anterior"<<endl;
    cout<<"\t\t\t --------------------------------------------"<<endl;
	cout<<"\t\t\t |   Opcion a escoger:[1|2|3|4|5|]           |"<<endl;
	cout<<"\t\t\t --------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa tu Opcion: ";
    cin>>choice;

    switch(choice)
    {
	case 1:
        Ingresar();
        system("Pause");
		break;
    case 2:
        system("Cls");
        Modificar();
		system("Pause");
		break;
    case 3:
        system("Cls");
        Borrar();
        system("Pause");
		break;
    case 4:
        Desplegar();
		break;
    case 5:
		break;
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
		cin.get();
	}
    }while(choice!= 5);
}

//Función que valida si ya existe la bodega para evitar redundancia de datos
 bool BodegaCRUD::Validar(int codigo){
        fstream archivo("bodegas.dat", ios::binary | ios::in | ios::out);
        if (!archivo) {
            return false;
        }

        Bodega bodega;
        bool encontrada = false;
        while (archivo.read(reinterpret_cast<char*>(&bodega), sizeof(Bodega))) {
            if (bodega.codigo == codigo) {
                encontrada = true;
                break;
            }
        }

        archivo.close();

       return encontrada;
}
// aqui se agregan carreras que son almacenadas
void BodegaCRUD::Ingresar() {
    string codigoPrograma="3000";
    system("cls");
    cout<<"\n------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n-------------------------------------------------Agregar Carrera--------------------------------------------"<<endl;
    Bodega bodega;
    cout << "Ingrese el codigo de la bodega: ";
    cin >> bodega.codigo;
    cin.ignore();
    if (Validar(bodega.codigo)){
        system("cls");
        cout << "El codigo de la bodega que desea crear ya existe!!" << endl << endl<< endl<< endl;
        return;
    }

    cout << "Ingrese el nombre de la bodega: ";
    cin.getline(bodega.nombre, 50);

    cout << "Ingrese el tipo de bodega: ";
    cin.getline(bodega.tipobodega, 50);

    cout << "Ingrese la direccion de la bodega: ";
    cin.getline(bodega.direccion, 50);

    cout << "Ingrese el estado de la bodega: ";
    cin.getline(bodega.estado, 50);


    ofstream archivo("bodegas.dat", ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&bodega), sizeof(Bodega));
    archivo.close();


    Bitacora Auditoria;
    string user,pass;

    Auditoria.ingresoBitacora(user,codigoPrograma,"ICA");//IBO = Insertar Bodega

    cout << "Bodega agregada exitosamente!" << endl;
}
// modificar bodegas
void BodegaCRUD::Modificar() {
    string codigoPrograma="3000";
    cout<<"\n------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n-------------------------------------------------Modificacion de Bodegas--------------------------------------------"<<endl;
    int codigo;
    cout << "Ingrese el codigo de la bodega a modificar: ";
    cin >> codigo;

    fstream archivo("bodegas.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay bodegas registradas." << endl;
        return;
    }

    Bodega bodega;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&bodega), sizeof(Bodega))) {
        if (bodega.codigo == codigo) {
            cout << "Ingrese el nuevo nombre de la bodega: ";
            cin.ignore();
            cin.getline(bodega.nombre, 50);

            cout << "Ingrese el nuevo tipo : ";
            cin.getline(bodega.tipobodega, 50);

            cout << "Ingrese la nueva direccion: ";
            cin.getline(bodega.direccion, 50);

            cout << "Ingrese el nuevo estado : ";
            cin.getline(bodega.estado, 50);

            archivo.seekp(-static_cast<int>(sizeof(Bodega)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&bodega), sizeof(Bodega));

            encontrada = true;
            break;
        }
    }

    archivo.close();

    Bitacora Auditoria;
    string user,pass;

    Auditoria.ingresoBitacora(user,codigoPrograma,"UBO");//UBO = Update Bodega

    if (!encontrada) {
        cout << "No se encontró la bodega con el codigo ingresado." << endl;
    }
    else {
        cout << "Bodega modificada exitosamente!" << endl;
    }

}
// elimina bodegas que ya no deseamos que estan registradas
void BodegaCRUD::Borrar() {
    string codigoPrograma="3000";
    int codigo;
    cout<<"\n------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n------------------------------------------------- Eliminar Bodegas --------------------------------------------"<<endl;
    cout << "Ingrese el codigo de la bodega a eliminar: ";
    cin >> codigo;

    ifstream archivo("bodegas.dat", ios::binary);
    if (!archivo) {
        cout << "No hay bodegas registradas." << endl;

    }

    ofstream archivoTmp("bodegas_tmp.dat", ios::binary);
    Bodega bodega;
    bool eliminada = false;
    while (archivo.read(reinterpret_cast<char*>(&bodega), sizeof(Bodega))) {
        if (bodega.codigo != codigo) {
            archivoTmp.write(reinterpret_cast<const char*>(&bodega), sizeof(Bodega));
        } else {
            eliminada = true;
        }
    }

    archivo.close();
    archivoTmp.close();

    remove("bodegas.dat");
    rename("bodegas_tmp.dat", "bodegas.dat");


    Bitacora Auditoria;
    string user,pass;

    Auditoria.ingresoBitacora(user,codigoPrograma,"DBO");//DBO = Delete Bodega

    if (eliminada) {
        cout << "Bodega eliminada exitosamente!" << endl;

    } else {
        cout << "No se encontró la bodega con el codigo ingresado." << endl;
    }

}
// Nos muestra las bodegas registradas
void BodegaCRUD::Desplegar() {
    system("cls");
    string codigoPrograma="3000";
    cout<<"-----------------Despliegue de carreras registradas---------------------"<<endl;
    ifstream archivo("bodegas.dat", ios::binary);
    if (!archivo) {
        cout << "No hay bodegas registradas." << endl;
        return;
    }

    Bodega bodega;
    while (archivo.read(reinterpret_cast<char*>(&bodega), sizeof(Bodega))) {
        cout << "Codigo     : " << bodega.codigo << endl;
        cout << "Nombre     : " << bodega.nombre << endl;
        cout << "Tipo Bodega: " << bodega.tipobodega << endl;
        cout << "Direccion  : " << bodega.direccion << endl;
        cout << "Estado     : " << bodega.estado << endl;
        cout << "-----------------------------" << endl;
    }

    archivo.close();


    Bitacora Auditoria;
    string user,pass;

    Auditoria.ingresoBitacora(user,codigoPrograma,"RBO");// RBO = Read Bodega

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

