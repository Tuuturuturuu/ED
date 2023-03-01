// Nombre del alumno Sofia Postigo
// Usuario del Juez E52


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Queue.h"

using namespace std;

// función que resuelve el problema


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    Queue<int> q;
    int n;
    while (cin >> n && n != 0)
        q.push_back(n);

    if (!std::cin)
        return false;

    q.duplicar();

    // escribir sol
    cout << q << endl;

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