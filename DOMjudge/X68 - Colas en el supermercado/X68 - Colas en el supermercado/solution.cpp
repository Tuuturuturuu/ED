// Colas en el supermercado
// ------------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <vector>
#include <queue>


using namespace std;

class Supermercado {
public:
    int N;

    Supermercado(int num_colas) {
        this->N = num_colas;
    }

    void nuevo_cliente(const string& dni, int num_cola) {
       
        if (num_cola < 0 || num_cola >= N) {
            throw domain_error("Cola inexistente");
        }
        if (mapaClientes.count(dni)) {
            throw domain_error("Cliente duplicado");
        }
        //anadir el cliente al final de la cola num_cola
        mapaColas[num_cola].push_front(dni);
        mapaClientes[dni].posEnCola = mapaColas[num_cola].begin();
        //anadir al clinete con la cola que le corresponde
        mapaClientes[dni].cola = num_cola;

    }

    void cambiar_cola(const string& dni, int num_cola) {
        
        if (num_cola < 0 || num_cola >= N) {
            throw domain_error("Cola inexistente");
        }
        if (!mapaClientes.count(dni)) {
            throw domain_error("Cliente inexistente");
        }
        if (mapaClientes[dni].cola != num_cola) {
            //borramos al cliente de la cola
            mapaColas[mapaClientes[dni].cola].erase(mapaClientes[dni].posEnCola);

            //añadimos el cliente al fina de la nueva cola
            mapaColas[num_cola].push_front(dni);
            mapaClientes[dni].posEnCola = mapaColas[num_cola].begin();
            mapaClientes[dni].cola = num_cola;
        }
    }

    int consultar_cliente(const string& dni) const {
        if (!mapaClientes.count(dni)) {
            throw domain_error("Cliente inexistente");
        }
        return mapaClientes.at(dni).cola;
    }

    int cuantos_en_cola(int num_cola) const {
        if (num_cola < 0 || num_cola >= N) {
            throw domain_error("Cola inexistente");
        }
        if (!mapaColas.count(num_cola)) {
            return 0;
        }
        return mapaColas.at(num_cola).size();
    }

    vector<string> clientes_en_cola(int num_cola) const {
        vector<string> listaClientes;
        if (!mapaColas.count(num_cola)) {
            return {};
        }
        if (num_cola < 0 || num_cola >= N) {
            throw domain_error("Cola inexistente");
        }

        auto it = mapaColas.at(num_cola).begin();
        while(it != mapaColas.at(num_cola).end()) {
            listaClientes.push_back(*it);
            ++it;
        }
        return listaClientes;
    }

private:
    struct infoCliente {
        int cola;
        list<string>::iterator posEnCola;
    };
    //por cada numero de cola tienes una cola de clientes
    unordered_map<int, list<string>> mapaColas;
    //por cada cliente ttienes el numero de la cola en la que esta
    unordered_map<string, infoCliente> mapaClientes;
};


bool tratar_caso() {
    int num_colas;
    cin >> num_colas;


    if (cin.eof()) return false;

    Supermercado sup(num_colas);

    string comando;
    cin >> comando;
    while (comando != "FIN") {
        try {
            if (comando == "nuevo_cliente") {
                string dni; cin >> dni;
                int num_cola; cin >> num_cola;
                sup.nuevo_cliente(dni, num_cola);
            }
            else if (comando == "cambiar_cola") {
                string dni; cin >> dni;
                int num_cola; cin >> num_cola;
                sup.cambiar_cola(dni, num_cola);
            }
            else if (comando == "consultar_cliente") {
                string dni; cin >> dni;
                int p = sup.consultar_cliente(dni);
                cout << "El cliente " << dni << " esta en la cola " << p << "\n";
            }
            else if (comando == "cuantos_en_cola") {
                int num_cola; cin >> num_cola;
                int result = sup.cuantos_en_cola(num_cola);
                cout << "En la cola " << num_cola << " hay " << result << " clientes\n";
            }
            else if (comando == "clientes_en_cola") {
                int num_cola; cin >> num_cola;
                vector<string> lista = sup.clientes_en_cola(num_cola);
                cout << "En la cola " << num_cola << " estan:";
                for (const string& s : lista) {
                    cout << " " << s;
                }
                cout << "\n";
            }
        }
        catch (exception& e) {
            cout << "ERROR: " << e.what() << "\n";
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