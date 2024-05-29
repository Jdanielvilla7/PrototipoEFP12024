//Creado por Jose Gallardo 9959-23-106
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "usuarios.h"
#include "Login.h"
#include "Bitacora.h"
#include "Bodega.h"


using namespace std;

void menuGeneral();
void catalogos();
void reportes();
void procesos();
void ayuda();
void seguridad();
void imprimirRegistro( fstream& );

string codigoPrograma="1";
Bitacora Auditoria;
string user, contrasena;

int main()
{
        // Llamamos al objeto e ingresamos los parametros
    Login ingreso(user, contrasena);

    // Creamos un bool que verifique y despliegue el metodo VerificarUsuario
    bool UsuarioCorrecto = ingreso.VerificarUsuario();

    // Luego de ingresar con usuario y contraseña se nos despliega otro menu
    if (UsuarioCorrecto)
    {
        menuGeneral();
    }

    return 0;
}

void menuGeneral()
{
    int choice;


    do
    {
        system("cls");
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t|         SISTEMA ERP          |" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t 1. Catalogos" << endl;
        cout << "\t\t\t 2. Informes" << endl;
        cout << "\t\t\t 3. Seguridad" << endl;
        cout << "\t\t\t 4. Salir del Sistema" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t|Opcion a escoger:[1/2/3/4/5/6]  |" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            catalogos();
            break;
        case 2:{
              // abrir el archivo en modo de lectura y escritura
               fstream Bodega( "bodegas.dat", ios::in | ios::out | ios::binary);

               // salir del programa si fstream no puede abrir el archivo
               if ( !Bodega )
                {
                  cerr << "No se pudo abrir el archivo." << endl;
                  system("pause");


               }
            imprimirRegistro(Bodega);

            break;
        }
        case 3:
              {
               Bitacora Auditoria;
               Auditoria.visualizarBitacora();
            }
            break;
        case 4:
                    Auditoria.ingresoBitacora(user,codigoPrograma,"LGO"); //llamada para registrar la bitacora de seguridad
            exit(0);
        default:
            cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.ignore();
            cin.get();
        }
    } while (choice != 4);
}

void catalogos()
{
    int choice;

    do
    {
        system("cls");
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t|                SISTEMA ERP                |" << endl;
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t 1. Bodega" << endl;
        cout << "\t\t\t 2. Retornar menu anterior" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\t | Opcion a escoger:[1-2]|" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            BodegaCRUD bodCRUD;
            bodCRUD.CRUDBodega();
            break;
        }
        case 2:
            menuGeneral();
            break;
        default:
            cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.ignore();
            cin.get();
        }
    } while (choice != 2);
}





// crear archivo de texto con formato para imprimirlo
void imprimirRegistro( fstream &leerDeArchivo )
{
   // crear archivo de texto
   ofstream archivoImprimirSalida( "imprimir.txt", ios::out );

   // salir del programa si ofstream no puede crear el archivo
   if ( !archivoImprimirSalida ) {
      cerr << "No se pudo crear el archivo." << endl;
      exit( 1 );

   } // fin de instruccion if



   // colocar el apuntador de posicion de archivo al principio del archivo de registros
   leerDeArchivo.seekg( 0 );

   // leer el primer registro del archivo de registros
   Bodega bodega;
   leerDeArchivo.read( reinterpret_cast< char * >( &bodega ),
      sizeof( Bodega ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivo.eof() ) {

      // escribir un registro individual en el archivo de texto

        archivoImprimirSalida<< "Codigo     : " << bodega.codigo << endl;
        archivoImprimirSalida << "Nombre     : " << bodega.nombre << endl;
        archivoImprimirSalida << "Tipo Bodega: " << bodega.tipobodega << endl;
        archivoImprimirSalida << "Direccion  : " << bodega.direccion << endl;
        archivoImprimirSalida << "Estado     : " << bodega.estado << endl;
        archivoImprimirSalida << "-----------------------------" << endl;

      // leer siguiente registro del archivo de registros
      leerDeArchivo.read( reinterpret_cast< char * >( &bodega ),
         sizeof( Bodega ) );

   } // fin de instrucci�n while

} // fin de la funci�n imprimirRegistro


