
#include <fstream>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>


using namespace std;
class Hospital {
public:

    Hospital() {  }
    void  altaMedico(const string& medico) {
        if (mapaMedicos.count(medico)) {
            throw domain_error("Medico existente");
        }
        list<string> pacientes;
        mapaMedicos[medico] = pacientes;
    }

    void pedirConsulta(const string& paciente, const string& medico) {
        if (!mapaMedicos.count(medico)) {
            throw domain_error("Medico inexistente");
        }
        if (mapaPacientes[paciente].medicosPaciente.count(medico)) {
            throw domain_error("Paciente ya esperando");
        }
        mapaMedicos[medico].push_front(paciente);

        mapaPacientes[paciente].posicionesCliente[medico] = mapaMedicos[medico].begin();
        mapaPacientes[paciente].medicosPaciente.insert(medico);
    }

    string siguientePaciente(const string& medico) const {
        if (!mapaMedicos.count(medico)) {
            throw domain_error("Medico inexistente");
        }
        if (mapaMedicos.at(medico).empty()) {
            throw domain_error("Medico sin pacientes");
        }
        return mapaMedicos.at(medico).back();
    }

    void atenderConsulta(const string& medico) {
        if (!mapaMedicos.count(medico)) {
            throw domain_error("Medico inexistente");
        }
        if (mapaMedicos[medico].empty()) {
            throw domain_error("Medico sin pacientes");
        }
        mapaPacientes[mapaMedicos[medico].back()].medicosPaciente.erase(medico);
        //mapaPacientes[mapaMedicos[medico].back()].posCliente;
        mapaMedicos[medico].pop_back();
    }

    vector<string> abandonarConsulta(const string& paciente) {
        if(!mapaPacientes.count(paciente)) {
            throw domain_error("Paciente inexistente");
        }

        vector<string> medicos;
        auto it = mapaPacientes[paciente].medicosPaciente.begin();
        while (it != mapaPacientes[paciente].medicosPaciente.end()) {
            medicos.push_back(*it);
            mapaMedicos[*it].erase(mapaPacientes[paciente].posicionesCliente[*it]);
            ++it;
        }
        mapaPacientes[paciente].medicosPaciente.clear();
        return medicos;
    }

private:
    struct infoPaciente{
        set<string> medicosPaciente;

        unordered_map<string,list<string>::iterator> posicionesCliente;
    };

    unordered_map<string, list<string>> mapaMedicos;

    unordered_map<string, infoPaciente> mapaPacientes;

};

bool tratar_caso() {
    Hospital h;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "altaMedico") {
                string l;
                cin >> l;
                h.altaMedico(l);
            }
            else if (comando == "pedirConsulta") {
                string pac;
                string med;
                cin >> pac >> med;
                h.pedirConsulta(pac, med);
            }
            else if (comando == "siguientePaciente") {
                string med;
                cin >> med;
                string p = h.siguientePaciente(med);
                cout << p << "\n";
            }
            else if (comando == "abandonarConsulta") {
                string pac;
                cin >> pac;
                vector<string>v = h.abandonarConsulta(pac);
                cout << "Medicos abandonados: ";
                for (int i = 0; i < v.size(); i++) {
                    cout << v[i] << " ";
                }
                cout << "\n";
            }
            else if (comando == "atenderConsulta") {
                string med;
                cin >> med;
                h.atenderConsulta(med);
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


