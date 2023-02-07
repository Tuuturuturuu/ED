#ifndef _HORAS_H
#define _HORAS_H

#include <iostream>
#include <string>
using namespace std;


class Horas {
public: 

	Horas();
	Horas(int hora, int minuto, int seg);
	bool operator<(const Horas& h2) const;
	friend ostream& operator<<(ostream& out, const Horas& h); //poner el friend para que no me de error
	friend istream& operator>>(istream& in, const Horas& h);

private:
	int _horas;
	int _minutos;
	int _segundos;

};
#endif

