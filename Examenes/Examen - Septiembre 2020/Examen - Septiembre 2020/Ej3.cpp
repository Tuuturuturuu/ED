
#include <fstream>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
class CarreraCiclismo {
public:

    vector<int> tiempoEquipo() {
        vector<int> equipos;
        for (auto it = mapaEquipos.begin(); it != mapaEquipos.end(); ++it) {
            equipos.push_back(mapaEquipos[it->first].puntuacionEquipo);
        }
        return equipos;
    }

    pair<string, int> primerCiclista() {
        auto it = mapaCiclistaCarrera.begin();
        while (it != mapaCiclistaCarrera.end()) {

        }
    }

    bool leerDatos(int nEquipos) {
        int nEquipos, numCiclistas;
        string equipo, ciclista;

        for (int i = 0; i < nEquipos; i++) {
            cin >> equipo >> numCiclistas;
            for (int j = 0; j < numCiclistas; j++) {
                cin >> ciclista;
                mapaCiclistaCarrera[ciclista].equipo = equipo; 
            }
        }
        int nEtapas, nSalida, tiempoMax, tiempoEtapa;
        cin >> nEtapas;
        for (int i = 0; i < nEtapas; i++) {
            cin >> nSalida >> tiempoMax;
            
            mapaEtapas[i + 1].puntuacionMax = tiempoMax;
            
            for (int j = 0; j < nSalida; j++) {
                cin >> ciclista >> tiempoEtapa;
                mapaEtapas[i + 1].mapaEtapasCiclistas[ciclista] = tiempoEtapa;
                
                mapaCiclistaCarrera[ciclista].mapaCiclistaEtapas[i + 1] = tiempoEtapa;
                mapaCiclistaCarrera[ciclista].puntuacionCiclistaCarrera += tiempoEtapa;
                mapaEquipos[mapaCiclistaCarrera[ciclista].equipo].mapaCiclistas[ciclista] += tiempoEtapa;
                mapaEquipos[mapaCiclistaCarrera[ciclista].equipo].puntuacionEquipo += tiempoEtapa;
            }
        }
    }
   

private:
    struct infoCiclistaCarrera {
        
        string equipo;
        //<etapa, puntuacion>
        map<int, int> mapaCiclistaEtapas;
        int puntuacionCiclistaCarrera = 0; //puntuacion Total del ciclista
    };
    map<string, infoCiclistaCarrera> mapaCiclistaCarrera;

    struct infoEquipo {
        //lista de mapas de ciclistas
        //<lista<map<ciclista,puntuacion total ciclista>>
        map<string, int> mapaCiclistas;
        int puntuacionEquipo = 0;//puntuacion total del equipo
    };

    //<equipo, infoEquipo>
    map<string, infoEquipo> mapaEquipos;

    struct infoEtapa {
        //<ciclista, puntuacion>
        map<string, int> mapaEtapasCiclistas;
        int puntuacionMax = 0;
    };

    //<etapa, infoEtapa>
    map<int, infoEtapa> mapaEtapas;
};

bool tratar_caso() {
    CarreraCiclismo cc;
    bool ret = true;
    int nEquipos;
    if (cin >> nEquipos) {
        cc.leerDatos(nEquipos);
    }
    else {
        ret = false;
    }
    cout << "---\n";

    return ret;
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


