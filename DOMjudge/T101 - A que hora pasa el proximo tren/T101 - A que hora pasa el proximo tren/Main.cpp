// Nombre del alumno Sofia Postigo Ruiz
// Usuario del Juez E52

#include "Horas.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int hs, numH;

    cin >> hs >> numH;

    if (hs == 0 && numH == 0)
        return false;

    vector<Horas> horarios(hs);

    for (int j = 0; j < hs; j++)
        cin >> horarios[j];

    for (int i = 0; i < numH; i++) {
        Horas h;

        try {
            cin >> h;
            auto pos = lower_bound(horarios.begin(), horarios.end(), h);
            if (pos != horarios.end())
                cout << *pos;
            else
                cout << "NO\n";
        }
        catch (Horas::EInvalidHour& e) {
            cout << "ERROR" << endl;
        }

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

    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
