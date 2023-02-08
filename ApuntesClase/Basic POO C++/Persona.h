#ifndef PERSONA_H
#define PERSONA_H

#include "Fecha.h"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Persona{
    public:
        Persona(string nombre, int dia, int mes, int anyo);
        Persona(string nombre, int dia, int mes, int anyo);

    private:
        string nombre;
        Fecha fechaNacimiento;


};

#endif;