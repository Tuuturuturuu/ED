// Nombre del alumno Sofía Postigo Ruiz
// Usuario del Juez E52

#include "Set.h"
#include <iostream>
#include <iomanip>
#include <fstream>

// función que resuelve el problema
void resolver(Set<int> &s1, Set<int> s2) {
    
    s1.diff(s2);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    Set<int> set1;
    Set <int> set2;
    cin >> set1;
    cin >> set2;

    if (!std::cin)
        return false;

   resolver(set1, set2);

    // escribir sol
   if (set1.isEmpty()) {
       cout << "e" << endl;
   }  
   else
        cout << set1;

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


