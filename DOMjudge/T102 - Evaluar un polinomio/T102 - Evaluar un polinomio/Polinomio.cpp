#include "Polinomio.h"
#include <cmath>
#include <iterator>
using namespace std;

Polinomio::Polinomio() {
}
int Polinomio::binarySearch(int ini, int fin, const std::pair<int, int>& mon){
    if (ini == fin)
        return ini;
    else{
        int mitad = (ini + fin) / 2;
        if (pol[mitad].second > mon.second)
            return binarySearch(ini, mitad, mon);
        else if (pol[mitad].second < mon.second)
            return binarySearch(mitad + 1, fin, mon);
        else{ //igual exponente, sumo coeficientes
            pol[mitad].first += mon.first;
            return -1;
        }
    }
}

void Polinomio::addMonomio(int cociente, int grado){
    if (cociente != 0 || grado != 0){
        int pos = binarySearch(0, pol.size(), std::make_pair(cociente, grado));
        if (pos != -1){
            pol.insert(pol.begin() + pos, std::make_pair(cociente, grado));
        }
    }
}

long long int Polinomio::evaluar(long long int x) {
	long long int val = 0;
	long long int c = 0;
	long long int pow = 1;

	
	for (long long int i = 0; i < pol.size(); i++) {
		while (c < pol[i].second) {
			pow *= x;
			c++;
		}
		val += pol[i].first * pow;
		
	}
	
	return val;
}
