#include "ejer_1.h"
#include <iostream>
using namespace std;


Horas::Horas() {
	_horas = 0;
	_minutos = 0;
	_segundos = 0;
}

Horas::Horas(int hora, int minuto, int seg) {
	if(hora < 0 || hora > 23 || minuto < 0 || seg > 59) throw 
	_horas = hora;
	_minutos = minuto;
	_segundos = seg;
}

bool Horas::operator<(const Horas& h2) const {
	return (_horas < h2._horas) && (_minutos == h2._minutos) && (_segundos == h2._segundos);
}

ostream& operator<<(ostream& out, const Horas& h) {
	out << h._horas << ":" << h._minutos << ":" << h._segundos;
	return out;
}

istream& operator>>(istream& in, Horas& h) {

}



