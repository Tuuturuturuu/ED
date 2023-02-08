#include "Persona.h"

using namespace std;



    Persona::Persona(string nombre, int dia, int mes, int anyo):fechaNacimiento(dia, mes, anyo) { //al crear el constructor de Persona se llama al constructor de Fecha con los parametros
        this->nombre = nombre;
    }

    //Tambien podriamos hacer: esto se llama LISTA DE INICIALIZACION
    Persona::Persona(string nombre, int dia, int mes, int anyo):nombre(nombre),fechaNacimiento(dia, mes, anyo){
        //vacio
    }
