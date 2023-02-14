
TEMA 1 : TADs-- -- -- -- -- -- -- -- -- -- --

Tipos Abstractos de Datos : 

Implementaciones de patrones que son independientes del lenguaje de
programacion(son comunes en c++, java, python..) y que nos permiten definir soluciones a problemas de estructiracion de los datos(pilas, colas, diccionarios / mapas).

Un TAD oculta completamente los detalles internos de implementacion,mostrando al programador unicamente las operaciones del interfaz. (el programador solu puede usar el TAD a partir de las operaciones d la interfaz)

-- -- -- -- -- -- -- -- -- -- -- 
Estructura de Datos:

Es la implementacion contreta de un TAD, usando los tipos y funciones ya existentes en el lenguaje de programacion que se use

TAD -> idea (valores + operaciones)
ED -> implementacion
-- -- -- -- -- -- -- -- -- -- -- 

imp dif entre pasar por valor y por referencia(es mas efivinte)

-- -- -- -- -- -- -- -- -- -- --

cuando un metodo es constante,
no modifica el objeto sobre el que trabaja
por ejemplo quedaria :

int daysInMonth(int m) const;

una clase en c++ se ve asi:

esto lo definiriamos en un .h: la definición de la clase con la cabecera de los metodos

class tDate{
    private:
        int day;
        int moth;
        int year;
        int daysInMonth(int m) const;
        bool correctDate() const;

    public:
        tDate(int d, int m, int y); //constructor
        int diff(const tDate & d1, tDate d2) const;
        //los metodos que no modifican el objeto q usan se les pone const
        tDate newDate(int day, int month, int year);
        tDate incr(tDate date);
        void print(tDate date) const;

}
---------------- 

tambien se pueden poner estos contructores:
tDate2(int d, int m, int y):dia(d), month(m), year(y){}

----------------
recordar los .cpp para la implementacion y los .h para las cabeceras

indicamos de que clase es cada metodo de unhaciendo: 
using namespace tDate2
o tDate2:: delante de las cabeceras de los metodos,
el constructor seria por ejemplo:

tDate2::tDate2(int d, int m, int y){
    this-> day = d;
    //atributo -> parametro
    this-> month = m;
    this-> year = y;

}
/*
tambien puedes hacer este constructor:
(se llama constructor por copia)
*/
tDate2:: tDate2(const tDate2 &date){
    day = date.day;
    month = date.month;
    year = date.year;
}
---------------
en los .h acordarse de poner:

#ifndef DATE2_H_
#define DATE2_H_
...

#endif

y en los cpp:
#include "coso.h"
----------------

