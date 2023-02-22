#ifndef _HORAS_H
#define _HORAS_H

#include <iostream>
#include <iomanip>

using namespace std;

class Horas {
public:
	class EInvalidHour {};

	friend ostream& operator<<(ostream& out, const Horas& h);
	friend istream& operator>>(istream& is, Horas& h);

	Horas();
	Horas(int h, int m, int s);
	bool operator <(const Horas& h2) const;

private:
	int _hora;
	int _mins;
	int _segs;

	bool comprobar(int h, int m, int s);
};

#endif
