#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <iostream>
#include <vector>
using namespace std;

class Polinomio {
public:

	Polinomio();

	void addMonomio(int coef, int exp);
	double evaluar(int x);

private:
	vector<pair<int, int>> pol;
};
#endif


