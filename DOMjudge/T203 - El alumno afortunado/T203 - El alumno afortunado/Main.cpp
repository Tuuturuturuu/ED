// Nombre del alumno Sofia Postigo
// Usuario del Juez E52


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Queue.h"
using namespace std;

// función que resuelve el problema
int resolver(Queue<int>& q, int saltos) {
    int i = 0;
    while (q.size() > 1) {
        if (i == saltos) {
            q.pop_front();
            i = 0;
        }

        int front = q.front();
        q.push_back(front);
        q.pop_front();
        
        i++;
    }
    return q.front();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, saltos;
    cin >> n >> saltos;

    if (n == 0 && saltos == 0)
        return false;


    Queue<int> q;

    for (int i = 1; i <= n; i++)
        q.push_back(i);

    int sol = resolver(q, saltos);

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
