// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "SetOfInts3.h"

using  namespace std;

SetOfInts3 kMenores(int k) {
    SetOfInts3 set;
    int con;
    
    while (cin >> con  && con != -1){
        if (set.size() == 0)
            set.add(con);
        if (con < set.getMax() || set.size() < k){
           set.add(con);
           if (set.size() > k) {
               set.removeMax();
           }
        }
    }
    return set;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int k;
    
    cin >> k;
    if (k == 0)
        return false;

    SetOfInts3 set = kMenores(k);

    // escribir sol
    cout << set << endl;

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
