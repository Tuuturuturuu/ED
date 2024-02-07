
#include <iostream>
#include <stdio.h> 
#include <vector>

const int N = 20000;
const int M = 20000;
using namespace std;

class MatrizT {			
public:
	//Coste del constructor: O(N) siendo N = n+m-1 (recorre todos los elementos del vector)
	MatrizT(int n, int m, int v) : n(n), m(m), v(v){
		for (int i = 0; i < n + m - 1; i++) {
			this->vectorDiag[i] = v;
		}
	};

	int get(int i, int j) const;
	void set(int i, int j, int v);

private:
	int n; //filas
	int m; //columnas
	int v; // valor
	int vectorDiag[N+M-1]; //vector de diagonales
};

//O(1)
int MatrizT::get(int i, int j) const {
	return this->vectorDiag[j - i + this->n - 1];
}

//O(1)
void MatrizT::set(int i, int j, int v) {
	this->vectorDiag[j - i + this->n - 1] = v;
}
