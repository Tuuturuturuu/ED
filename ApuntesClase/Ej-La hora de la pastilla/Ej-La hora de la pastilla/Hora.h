#include <iostream>

using namespace std;
using Duracion = int;

//Representacion B
class Hora {
public:
	Hora() : numSegundos(0) {};
	Hora(int horas, int minutos, int segundos) : numSegundos((horas*3600) + (minutos*60) + segundos) {};

	Duracion diferencia(const Hora& hora) const; // funcion constructora
	Hora suma(Duracion d) const;
	Hora horaPastilla(const Hora& primera, const Hora& ultima,
		int num_pastillas, int i);

private:
	// Numero de segundostranscurridos desde la hora 00:00:00 de ese dia
		int numSegundos;
};Duracion Hora::diferencia(const Hora& hora) const {
	if (hora.numSegundos >= this->numSegundos) {
		return hora.numSegundos - this->numSegundos;
	}
	else {
		return this->numSegundos - hora.numSegundos;
	}

}

Hora Hora::suma(Duracion d) const {
	Hora result(0, 0, 0);
	result.numSegundos = (this->numSegundos + d) % (24 * 3600);
	return result;
}

Hora Hora::horaPastilla(const Hora& primera, const Hora& ultima, int num_pastillas, int i) {

}



