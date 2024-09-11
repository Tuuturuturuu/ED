
#include <fstream>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>


using namespace std;
class Ferrovistan {
public:

    Ferrovistan() {  }

    void nueva_linea(const string& nombre) {
        if (mapaLineas.count(nombre)) {
            throw domain_error("Linea existente");
        }
        map<int, string> map;
        mapaLineas[nombre] = map;
    }
    
    void nueva_estacion(const string& linea, const string& nombre, int posicion) {
        if (!mapaLineas.count(linea)) {
            throw domain_error("Linea no existente");
        }
        if (mapaEstaciones[nombre].count(linea)) {
            throw domain_error("Estacion duplicada en linea");
        }
        if (mapaLineas[linea].count(posicion)) {
            throw domain_error("Posicion ocupada");
        }
        mapaEstaciones[nombre][linea] = posicion;
        mapaLineas[linea][posicion] = nombre;
    }

    void eliminar_estacion(const string& estacion) {
        if (!mapaEstaciones.count(estacion)) {
            throw domain_error("Estacion no existente");
        }

        //it que recorre todas las lineas que pasan por esta estacion
        //it first = nombre de la linea, it second = posicion de esa estacion dentro de la linea
        auto it = mapaEstaciones[estacion].begin();

        while (it != mapaEstaciones[estacion].end()) {
            //mapaLineas[linea].erase(position);
            mapaLineas[it->first].erase(it->second);
            ++it;
        }
        mapaEstaciones.erase(estacion);
    }

    vector<string> lineas_de(const string& estacion) const {
        if (!mapaEstaciones.count(estacion)) {
            throw domain_error("Estacion no existente");
        }
        auto it = mapaEstaciones.at(estacion).begin();
        vector<string> lista;
        while (it != mapaEstaciones.at(estacion).end()) {
            lista.push_back(it->first);
            ++it;
        }
        return lista;
    }

    string proxima_estacion(const string& linea, const string& estacion) const {
        if (!mapaLineas.count(linea)) {
            throw domain_error("Linea no existente");
        }
        if (!mapaEstaciones.count(estacion) || !mapaEstaciones.at(estacion).count(linea)) {
            throw domain_error("Estacion no existente");
        }
        if (mapaLineas.at(linea).rbegin()->first == mapaEstaciones.at(estacion).at(linea)) {
            //si es el ultimo elemento
            throw domain_error("Fin de trayecto");
        }
        
        //como lo habia hecho yo:
           /* auto it = mapaLineas.at(linea).begin();
            while (it->second != estacion) {
                ++it;
            }
            return mapaLineas.at(linea).at((++it)->first);*/

        //como se hace:
        int posEstacion = mapaEstaciones.at(estacion).at(linea);
        auto posSiguiente = mapaLineas.at(linea).upper_bound(posEstacion);

        return posSiguiente->second;
    }

private:
    //nombre de la estacion, info de la estacion
    unordered_map<string, map<int,string>> mapaLineas;
    //nombre de las estaciones y la linea en la que estan y la pos en la que estan
    unordered_map<string, map<string, int>> mapaEstaciones;

};

bool tratar_caso() {
    Ferrovistan f;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "nueva_linea") {
                string l;
                cin >> l;
                f.nueva_linea(l);
            }
            else if (comando == "nueva_estacion") {
                string linea;
                string estacion;
                int pos;
                cin >> linea >> estacion >> pos;
                f.nueva_estacion(linea, estacion, pos);
            }
            else if (comando == "lineas_de") {
                string est;
                cin >> est;
                vector<string> v = f.lineas_de(est);
                cout << "Lineas de Sevistan: ";
                for (int i = 0; i < v.size(); i++)
                    cout << v[i] << " ";
                cout << "\n";
            }
            else if (comando == "proxima_estacion") {
                string linea;
                string estacion;
                cin >> linea >> estacion;
                string s = f.proxima_estacion(linea, estacion);
                cout << s << "\n";
            }
            else if (comando == "eliminar_estacion") {
                string estacion;
                cin >> estacion;
                f.eliminar_estacion(estacion);
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
