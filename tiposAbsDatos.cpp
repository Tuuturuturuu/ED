- imp dif entre pasar por valor y por referencia 
(es mas efivinte)

---------------

cuando un metodo es constante, no modifica el objeto sobre el que trabaja 
por ejemplo quedaria:

int daysInMonth(int m) const;

una clase en c++ se ve asi:

esto lo definiriamos en un .h: la definición de la clase con la cabecera de los metodos

class tDate2{
    private:
        int day;
        int moth;
        int year;
        int daysInMonth(int m) const;
        bool correctDate() const;

    public:
    tDate2(int d, int m, int y); //constructor
    int diff(const tDate2 & d) const;

}
---------------- 

tambien se pueden poner estos contructores:
//! no entendi bien preguntar diego
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
tambien puedes hacer este constructor:
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