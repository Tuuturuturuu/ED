
#include <fstream>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>


using namespace std;

//lista de punteros que apuntan a todos los platos pedidios por la mesa INT 
//en la cola de pedidos 
using posicionesPedidos = list<list<pair<int, string>>::iterator>;


class Restaurante {
public:

    Restaurante() {  }

    void nueva_mesa(int num){
        if (mapaMesas.count(num)) {
            throw domain_error("Mesa ocupada");
        }
        infoMesa info;
        mapaMesas[num] = info;
    }

    void nuevo_pedido(int mesa, const string& plato) {
        if (!mapaMesas.count(mesa)) {
            throw domain_error("Mesa vacia");
        }
        colaPedidos.push_front({ mesa,plato });
        mapaMesas[mesa].mapaPlatos[plato].push_back(colaPedidos.begin());
    }

    void cancelar_pedido(int mesa, const string& plato) {
        if (!mapaMesas.count(mesa)) {
            throw domain_error("Mesa vacia");
        }
        if (!mapaMesas[mesa].mapaPlatos.count(plato)) {
            throw domain_error("Producto no pedido por la mesa");
        }

        colaPedidos.erase(mapaMesas[mesa].mapaPlatos[plato].back());

        mapaMesas[mesa].mapaPlatos[plato].pop_back(); 

        if (mapaMesas[mesa].mapaPlatos[plato].empty()) {
            mapaMesas[mesa].mapaPlatos.erase(plato);
        }
       
    }

    pair<int, string> servir() {
        if (colaPedidos.empty()) {
            throw domain_error("No hay pedidos pendientes");
        }

        pair<int, string> ret = colaPedidos.back();

        mapaMesas[ret.first].mapaPlatos[ret.second].pop_front();

        if (mapaMesas[ret.first].mapaPlatos[ret.second].empty()) {
            mapaMesas[ret.first].mapaPlatos.erase(ret.second);
        }
     

        colaPedidos.pop_back();

        return ret;
    }

    vector<string> que_falta(int mesa) const {
        if (!mapaMesas.count(mesa)) {
            throw domain_error("Mesa vacia");
        }
        vector<string> platos;
        auto it =mapaMesas.at(mesa).mapaPlatos.begin();

        while (it != mapaMesas.at(mesa).mapaPlatos.end() ){
            platos.push_back(it->first);
            ++it;
        }
        return platos;
    }

private:
    struct infoMesa {
        //plato -> posiciones en la lista de pedidos de ese plato para esa mesa
        map<string, posicionesPedidos> mapaPlatos;

    };
    //num mesa a platos de esa mesa
    unordered_map<int, infoMesa> mapaMesas;

    //cola de mesas con el plato q han pedido
    list<pair<int,string>> colaPedidos;
};


bool tratar_caso() {
    Restaurante t;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "nueva_mesa") {
                int num;
                cin >> num;
                t.nueva_mesa(num);
            }
            else if (comando == "nuevo_pedido") {
                string plato;
                int mesa;
                cin >> mesa >> plato;
                t.nuevo_pedido(mesa, plato);
            }
            else if (comando == "cancelar_pedido") {
                string plato;
                int mesa;
                cin >> mesa >> plato;
                t.cancelar_pedido(mesa, plato);
            }
            else if (comando == "servir") {
                pair<int, string> s = t.servir();
                cout << s.second << " " << s.first << "\n";
            }
            else if (comando == "que_falta") {
                int num;
                cin >> num;
                vector<string> v = t.que_falta(num);
                cout << "En la mesa " << num << " falta:\n";
                for (int i = 0; i < v.size(); i++) {
                    cout << "  " << v[i] << "\n";
                }
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
