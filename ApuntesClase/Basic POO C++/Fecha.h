#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Fecha{
    
    public:
        //constructores y metodos publicos en public

        Fecha(int dia, int mes, int anyo);
        Fecha(int anyo);
        Fecha();

        int get_dia()  const;
        void set_dia(int dia);
        int get_mes() const;
        void set_mes(int mes);
        int get_anyo() const;
        void set_anyo(int anyo);

        void imprimir() const;
        bool esNavidad(const Fecha &f);
        //al pasar los parametros por referencia como sonstantes, (con const y &) no estamos haciendo una nueva copia de los mismos como con el & solo, ni estamos modificandolos dentro de la funcion como si no pusieramos & (al ser constantes)
        bool compara(const Fecha &f1, const Fecha &f2);

        private:

        int dia;
        int mes;
        int anyo;

};

#endif