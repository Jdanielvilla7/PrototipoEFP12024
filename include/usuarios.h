
//Creado por Oscar Morales 9959-23-3070

#ifndef USUARIOS_H
#define USUARIOS_H
#include<iostream>

using std::string;

class usuarios
{
    public:
        usuarios();
        virtual ~usuarios();
        bool loginUsuarios();
        void menuUsuarios();
        bool buscar(string user, string passw);
        string getNombre();
        string setNombre(string nombre);

        void insertar();
        void desplegar();
        void modificar();
        void borrar();
        void menuextra();

        alumnos(string usu, string contra);
        string setid(string usu);
        string getid();

        string setnombre(string contra);
        string getnombre();

        struct Usuario {
            char usu[20];
            char contra[50];
        };

    protected:

    private:
		string id;
		string name;
		string pass;

};

#endif // USUARIOS_H

