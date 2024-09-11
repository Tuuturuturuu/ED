#include <fstream>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
class ElGrande {
public:

    ElGrande() {  }

    void anyadir_jugador(const string& jugador) {
        if (mapaJugadores.count(jugador)) {
            throw domain_error("Jugador existente");
        }
        infoJugador info;
        mapaJugadores[jugador] = info;
    }

    void colocar_caballero(const string& jugador, const string& region) {
        if (!mapaJugadores.count(jugador)) {
            throw domain_error("Jugador no existente");
        }
        //if(mapaRegiones.count(region))"
        
        string prevPredominante = mapaRegiones[region].jugadorPredominante;

        mapaRegiones[region].mapaJugadorescaballerosRegion[jugador] += 1;

        //si tras smarle el jugador ahora predomina en al region
        if (mapaRegiones[region].mapaJugadorescaballerosRegion[jugador] > mapaRegiones[region].mapaJugadorescaballerosRegion[prevPredominante]) {
            mapaRegiones[region].jugadorPredominante = jugador;
            mapaJugadores[jugador].numRegionesPredominadas += 1;
            mapaJugadores[prevPredominante].numRegionesPredominadas -= 1;

        }
        else if (mapaRegiones[region].mapaJugadorescaballerosRegion[jugador] == mapaRegiones[region].mapaJugadorescaballerosRegion[prevPredominante]) {
            mapaRegiones[region].jugadorPredominante = "";
            mapaJugadores[prevPredominante].numRegionesPredominadas -= 1;
            mapaRegiones[region].disputa = true;
        }
    }

    int puntuacion(const string& jugador) {
        if (!mapaJugadores.count(jugador)) {
            throw domain_error("Jugador no existente");
        }
        return mapaJugadores[jugador].numRegionesPredominadas;
    }

    vector<string> regiones_en_disputa() {
        vector<string> regiones;
        for (auto it = mapaRegiones.begin(); it != mapaRegiones.end(); ++it) {
            if (it->second.disputa) {
                regiones.push_back(it->first);
            }
        }
        return regiones;
    }

    void expulsar_caballeros(const string& region) {
        if (!mapaRegiones.count(region) || mapaRegiones[region].mapaJugadorescaballerosRegion.empty()) {
            throw domain_error("Region vacia");
        }
        if (!mapaRegiones[region].disputa && mapaRegiones[region].jugadorPredominante != "") {//si predominaba alguien
            mapaJugadores[mapaRegiones[region].jugadorPredominante].numRegionesPredominadas -= 1;
        }
        mapaRegiones[region].mapaJugadorescaballerosRegion.clear();
        mapaRegiones[region].disputa = false;
    }

private:

    struct infoRegion {
        string jugadorPredominante;
        bool disputa = false;
        //<jugador, numero de caballeros q tiene en esta region>
        unordered_map<string, int> mapaJugadorescaballerosRegion;
    };
    //<region, infoRegion>
    map<string, infoRegion> mapaRegiones;
    
    struct infoJugador {
        int numRegionesPredominadas = 0;
    };
    //nombre jugador, info jugador
    unordered_map<string, infoJugador> mapaJugadores;
};

bool tratar_caso() {
    ElGrande eg;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "anyadir_jugador") {
                string l;
                cin >> l;
                eg.anyadir_jugador(l);
            }
            else if (comando == "colocar_caballero") {
                string jug;
                string reg;
                cin >> jug >> reg;
                eg.colocar_caballero(jug, reg);
            }
            else if (comando == "puntuacion") {
                string jug;
                cin >> jug;
                int p = eg.puntuacion(jug);
                cout << "Puntuacion de " << jug << ": " << p << "\n";
            }
            else if (comando == "regiones_en_disputa") {
               
                vector<string> v = eg.regiones_en_disputa();
                cout << "Regiones en disputa:\n";
                for (int i = 0; i < v.size(); i++)
                    cout << v[i] << "\n";
            }
            else if (comando == "expulsar_caballeros") {
                string reg;
                cin >> reg;
                eg.expulsar_caballeros(reg);
            }

        }
        catch (std::domain_error& e) {
            cout << "ERROR: " << e.what() << "\n";
        }

        cin >> comando;
    }
    cout << "---\n";

    return true;
}

int main() {

    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // La entrada comienza con el número de casos de prueba.


    // Llamamos tantas veces a `tratar_caso` como nos diga el número.
    while (tratar_caso()) {
    }

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

