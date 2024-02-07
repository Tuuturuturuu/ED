#include <iostream>

const int MAX_CHARS = 26;

class ConjuntoChar {
public:
	ConjuntoChar();
	bool pertenece(char letra) const;
	void anyadir(char letra);
	int busquedaBinaria(char l) const;

private:
	int num_elems;
	char elems[MAX_CHARS];
};

ConjuntoChar::ConjuntoChar() {
	num_elems = 0;
}

//log(N) con N = num_elems
bool ConjuntoChar::pertenece(char letra) const {
	int i = busquedaBinaria(letra);
	if (i < num_elems && elems[i] == letra) return true;
	else return false;
}

//O(N) con N = num_elems
void ConjuntoChar::anyadir(char letra) {
	int i = busquedaBinaria(letra);
	if (i == num_elems || elems[i] != letra){
		for (int j = num_elems; j > i; j--) {
			elems[j] = elems[j - 1];
		}
		elems[i] = letra;
		num_elems++;
	}

}

//log(N) con N = num_elems
int ConjuntoChar::busquedaBinaria(char l) const {
	int ini = 0;
	int fin = this->num_elems;
	bool ret = false;
	int mitad = (ini + fin) / 2;


	while (ini <= fin && !ret) {

		if (elems[mitad] == l) {
			ret = true;
		}
		else if (elems[mitad] < l) {//el nuevo segmento va de ini (0) a m - 1
			fin = mitad - 1;
		}
		else {// el nuevo segmento va de m + 1 a fin (num_elems)
			ini = mitad + 1;
		}
	}
	return mitad;
}

