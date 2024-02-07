/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1: Sofia Postigo Ruiz
   Componente 2: Sergio Tarancón Martínez
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "MatrizT.h"

using namespace std;

// Define aquí la clase ToeplitzMatrix e implementa sus métodos.
//
// No te olvides de indicar y justificar el coste del constructor y el coste de cada método.


bool tratar_caso() {
	int n, m, vini, i, j, v;
	string st;
	bool ceros = true;

	while (ceros) {
		cin >> n >> m >> vini;
		if (n == 0 && m == 0 && vini == 0) ceros = false;
		else {
			MatrizT matriz(n,m,vini);
			bool fin = false;
			while (!fin) {
				cin >> st;
				if (st == "get") {
					cin >> i >> j;
					cout << matriz.get(i, j) << endl;
				}
				else if (st == "set") {
					cin >> i >> j >> v;
					matriz.set(i, j, v);
				}
				else {
					fin = true;
					cout << "---" << endl;
				}
			}
		}
	}
	return ceros;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
