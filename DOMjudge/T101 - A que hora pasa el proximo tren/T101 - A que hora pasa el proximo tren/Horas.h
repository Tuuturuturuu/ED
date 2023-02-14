
#ifndef _HORAS_H
#define _HORAS_H

#include <iostream>

using namespace std;

class Horas {
public:
	class EInvalidHour{};

	Horas(int h, int m, int s);
	Horas();
	bool operator <(const Horas& h2) const;
	friend ostream& operator <<(ostream& out, const Horas& h);
	friend istream& operator >>(istream& in, Horas& h);


private:
	int _hora;
	int _mins;
	int _segs;

	bool comprobar();
};

#endif
