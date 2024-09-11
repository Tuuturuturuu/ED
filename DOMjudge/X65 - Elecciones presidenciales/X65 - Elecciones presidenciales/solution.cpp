// Elecciones Presidenciales
// -------------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;


class ConteoVotos {
public:
    void nuevo_estado(const string& nombre, int num_compromisarios) {
        if (mapaEstados.count(nombre)) {
            throw domain_error("Estado ya existente");
        }
        mapaEstados[nombre].numComp = num_compromisarios;
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        if (!mapaEstados.count(estado)) {
            throw domain_error("Estado no encontrado");
        }

        infoEstado& ie = mapaEstados[estado];
        //se suma al partido el nuemro de votos en ese estado
        ie.mapaPartidosEstado[partido] += num_votos;

        //se actualiza el ganador con el nuevo conteo de votos:
        if (ie.puntosGanador == 0) {
            ie.ganador = partido;
            ie.puntosGanador = ie.mapaPartidosEstado[partido];
            mapaPartidos[partido] += ie.numComp;
        }
        else {//ya hay algun partido que va ganando
            if (ie.mapaPartidosEstado[partido] > ie.puntosGanador) {//si hay un nuevo ganador
                //restamos los comp del antiguo ganador
               
                mapaPartidos[mapaEstados[estado].ganador] -= mapaEstados[estado].numComp;
                //actualizo el nuevo gandor
                ie.puntosGanador = ie.mapaPartidosEstado[partido];
                ie.ganador = partido;
                //sumo los comp al nuevo ganador
                mapaPartidos[partido] += ie.numComp;
            }
        }
    }

    string ganador_en(const string& estado) const {
        if (!mapaEstados.count(estado)) {
            throw domain_error("Estado no encontrado");
        }
        return mapaEstados.at(estado).ganador;
    }

    vector<pair<string, int>> resultados() const {
        vector<pair<string, int>> listaPartidos;
       
        for (auto it = mapaPartidos.begin(); it != mapaPartidos.end(); ++it) {
            if(it->second >= 1){
                listaPartidos.push_back(make_pair(it->first,it->second));
            }
        }
        return listaPartidos;
    }

private:

    struct infoEstado{
        int numComp = 0;
        string ganador = "";
        int puntosGanador = 0;
        //por cada estado, tenemos un mapa de partidos con el nombre de partido (first)y el numero de votos que tiene en ese estado
        unordered_map<string,int> mapaPartidosEstado;
    };

    //por cada nombre del partido (first) tienes su ionformacion (second)
    unordered_map<string, infoEstado> mapaEstados;

    //por cada nombre de partido (first) tenemos el numero de comensales totales en el pais de ese partido (int, second)
    map<string,int> mapaPartidos;
};


bool tratar_caso() {
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    ConteoVotos cv;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                string estado;
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                cv.nuevo_estado(estado, num_compromisarios);
            }
            else if (comando == "sumar_votos") {
                string estado;
                string partido;
                int num_votos;
                cin >> estado >> partido >> num_votos;
                cv.sumar_votos(estado, partido, num_votos);
            }
            else if (comando == "ganador_en") {
                string estado;
                cin >> estado;
                string ganador = cv.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            }
            else if (comando == "resultados") {
                for (const auto& [partido, num_comp] : cv.resultados()) {
                    cout << partido << " " << num_comp << "\n";
                }
            }
        }
        catch (std::exception& e) {
            cout << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (tratar_caso()) {}
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}