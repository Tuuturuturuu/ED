
#include "Horas.h"

using namespace std;


//metodos publicos:
Horas::Horas() {
	_hora = 0;
	_mins = 0;
	_segs = 0;
}

Horas::Horas(int h, int m, int s) {
	if (!comprobar()) {
		throw EInvalidHour();
	}
	_hora = h;
	_mins = m;
	_segs = s;
}

bool Horas::operator <(const Horas& h2) const {
	//hora
	if (_hora > h2._hora) 
		return false;
	
	if (_hora < h2._hora)
		return true;
	//mins
	if (_mins > h2._mins) 
		return false;
	
	if (_mins < h2._mins)
		return true;
	//segs
	if (_segs > h2._segs) 
		return false;
	
	if (_segs < h2._segs)
		return true;

	return false;
}

ostream& operator <<(ostream& out, const Horas& h) {
	//formamos un output y se returnea para imprimirlo
	out << h._hora << ":" << h._mins << ":" << h._segs;
	return out;
}

istream& operator >>(istream& is, Horas& h) {
	//is >> h._hora >> h._mins >> h._segs;
	char input[8];
	is >> input;
	scanf(input, "%02d:%02d:%02d", h._hora, h._mins, h._segs);
	is.clear();
	return is;
}

//metodos privados:
bool Horas::comprobar() {
	return _hora < 24 && _hora >= 0 && _mins < 60 && _mins >= 0 && _segs < 60 && _segs >= 0;
}
