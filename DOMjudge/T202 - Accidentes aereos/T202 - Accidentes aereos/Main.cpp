// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Stack.h"

using namespace std;

struct tAccidentes{
    
    string fecha;
    int victimas;
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada


    int n;
    cin >> n;

    if (!std::cin)
        return false;

    tAccidentes actual;
    Stack<tAccidentes> pila;
    
    for (int i = 0; i < n; i++) {

        cin >> actual.fecha >> actual.victimas;

        while (!pila.empty() && actual.victimas >= pila.top().victimas)
            pila.pop();

        // escribir sol
        if (pila.empty())
            cout << "NO HAY\n";
        else
            cout << pila.top().fecha << "\n";

            pila.push(actual);
    }

    cout << "---\n";

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