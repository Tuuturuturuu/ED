// Nombre del alumno Sofia Postigo
// Usuario del Juez E52

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Polinomio.h"

using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    Polinomio p;
    int exp, coef;
    cin >> coef >> exp;

    if (!std::cin)
        return false;
    
    while (!(coef == 0 && exp == 0)) {
        p.addMonomio(coef, exp);
        cin >> coef >> exp;
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        long long int x;
        cin >> x;
        cout << p.evaluar(x) << " ";
    }

    cout << endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}