/*
 *Nombre y apellidos de los alumnos:
 *Lucia Garcia García
 *Sofía Postigo Ruiz
 * Usuarios del juez: E52, E31
 */

#include <iostream>
#include <fstream>
#include "Arbin.h"
#include <algorithm>
#include <utility>
#include <algorithm>
using namespace std;

/**
 * Escribe la función que resuelve el problema. Puedes usar funciones auxiliares si lo
 * crees necesario.
 *
 * IMPORTANTE: - NO puedes usar parámetros que sean a la vez, entrada y salida
 *             - Indica el coste de tu función
 *
 */

pair<int, int> alt_nodos(const Arbin<char>& a) {
    if (a.esVacio()) return make_pair(0, 0);
    if (a.hijoIz().esVacio() && a.hijoDr().esVacio()) return make_pair(0, 1);

    pair<int, int> izq = alt_nodos(a.hijoIz());
    pair<int, int> der = alt_nodos(a.hijoDr());

    return make_pair(max(izq.first, der.first) + 1, izq.second + der.second + 1);
}

int solve(const Arbin<char>& a) {
    if (a.esVacio()) return 0;
    if (a.hijoIz().esVacio() && a.hijoDr().esVacio()) return 0;

    pair<int, int> izq = alt_nodos(a.hijoIz());
    pair<int, int> der = alt_nodos(a.hijoDr());

    if (izq.second > der.second) // cortamos la izq pk tiene mas nodos, simportar la altura
        return izq.second + solve(a.hijoDr());
    if (izq.second < der.second) // cortamos la der por tener mas nodos sin importar altura
        return der.second + solve(a.hijoIz());
    if (izq.second == der.second) {//si son iguales miramos la altura
        if (izq.first < der.first) // cortamos izq pk tiene menos altura
            return izq.second + solve(a.hijoDr());
        if (der.first <= izq.first) // cortamos derecha en caso de ser menor altura o iguales (si son iguales dara igual)
            return der.second + solve(a.hijoIz());
    }
}

void resuelveCaso() {
    Arbin<char> arbol = Arbin<char>::leerArbolInorden();

    //Llamada a la función y escritura de los datos
    cout << solve(arbol) << endl;
}


///
int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int casos;
    cin >> casos;
    while (casos--) {
        resuelveCaso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
