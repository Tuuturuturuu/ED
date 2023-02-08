#include "Fecha.h"

using namespace std;

//CONSTRUCTOR POR DEFECTO: (sin parametros)
Fecha::Fecha(){ //si lo definimos fuera de la clase añadimos Fecha::
    dia = 1;
    mes = 1;
    anyo = 1900;
}
//CONSTRUCTOR ON PARAMETROS:
Fecha::Fecha(int dia, int mes, int anyo){
    this->dia = dia;
    this->mes = mes;
    this->anyo = anyo;
}
//SOBRECARGA DE CONSTRUCTORES: (sobreescribir un constructor q ya tenemos para hacer algo especifico)
Fecha::Fecha(int anyo){
    this->dia = 1;
    this->mes = 1;
    this->anyo = anyo;
}
//DELEGACION DE CONSTRUCTORES:
Fecha::Fecha(int anyo): Fecha(1,1,anyo){
    //vacio
}
//a esto se le llama LISTA DE INICIALIZACION (como en persona)
Fecha::Fecha(int dia, int mes, int anyo):dia(dia), mes(mes), anyo(anyo){
    //vacio
}

//asi el resto de implementaciones, pueden ir fuera o dentro de la definición de la clase

//cont indica que el metodo no altera el estado del objeto, se llaman METODOS OBSERVAADORES los metodos constantes. Syuelen ser: los getters, los metodos para imprimir y los to_Satring
int Fecha::get_dia() const {
    return dia;
}

int Fecha::get_mes() const {
    return mes;
}

void Fecha::set_dia(int dia){
    this->dia = dia;
}

void Fecha::set_mes(int mes){
    this->mes = mes;
}

int Fecha::get_anyo() const {
    return anyo;
}

void Fecha::set_anyo(int anyo){
    this->anyo = anyo;
}

void Fecha::imprimir() const {
    cout << setfill('0') << setw(2) << dia << "/" << setw(2)<< mes << setw(4)<< "/" << anyo;
}

bool Fecha::esNavidad(const Fecha &f){ //aseguramos que imprimir no va a modificar el estado  de f
    return f.get_dia() == 25 && f.get_mes() == 12;
}



