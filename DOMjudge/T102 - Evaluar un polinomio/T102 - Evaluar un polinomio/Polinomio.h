#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <iostream>
#include <vector>

using namespace std;

class Polinomio {
public:

	Polinomio();
	int binarySearch(int ini, int fin, const std::pair<int, int>& mon);

	void addMonomio(int cociente, int grado);
	long long int evaluar(long long int x);

private:
	vector<pair<int, int>> pol;
};

#endif