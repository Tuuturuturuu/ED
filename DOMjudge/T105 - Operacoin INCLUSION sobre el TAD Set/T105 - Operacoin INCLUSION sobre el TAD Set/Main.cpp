// Nombre del alumno Sofia Postigo Ruiz
// Usuario del Juez E52


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"


// función que resuelve el problema
void resolver(Set<int>& set1, Set<int>& set2) {

    if (set1 <= set2) 
        cout << '1' << endl;
    else
        cout << '0' << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    Set<int> s1, s2;
    cin >> s1;
    cin >> s2;
    

    if (!std::cin)
        return false;

    

    // escribir sol
    resolver(s1, s2);

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}