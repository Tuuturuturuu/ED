#include "Horas.h"

// constructores
Horas::Horas() {
	_hora = 0;
	_mins = 0;
	_segs = 0;
}

Horas::Horas(int h, int m, int s) {
	if (!comprobar(h, m, s)) {
		throw EInvalidHour();
	}
	_hora = h;
	_mins = m;
	_segs = s;
}

bool Horas::comprobar(int h, int m, int s) {
	return h < 24 && h >= 0 && m < 60 && m >= 0 && s < 60 && s >= 0;
}

//operators
bool Horas::operator<(const Horas& h2) const {
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

ostream& operator<<(ostream& out, const Horas& h) {

	out << std::setfill('0') << std::setw(2) << h._hora << ':'
		<< std::setfill('0') << std::setw(2) << h._mins << ':'
		<< std::setfill('0') << std::setw(2) << h._segs << '\n';

	return out;
}

istream& operator>>(istream& is, Horas& h) {
	char c;
	int _h, _m, _s;
	is >> _h >> c >> _m >> c >> _s;
	h = Horas(_h, _m, _s);

	return is;
}
