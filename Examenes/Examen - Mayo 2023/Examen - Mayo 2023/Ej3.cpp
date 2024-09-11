
#include <fstream>
#include <cassert>
#include <iostream>
#include <deque>
#include <unordered_map>

using namespace std;

class TiendaCamisetas {
public:

    TiendaCamisetas() {  }

    void inserta_izquierda(const std::string& color) {

        barraCamis.push_front(color);
        mapaColores[color] += 1;
    }

    void inserta_derecha(const std::string& color) {

        barraCamis.push_back(color);
        mapaColores[color] += 1;
    }

    void compra_izquierda() {
        if (barraCamis.empty()) {
            throw domain_error("Tienda sin camisetas");
        }

        mapaColores[barraCamis.front()] -= 1;
        barraCamis.pop_front();
    }

    void compra_derecha() {
        if (barraCamis.empty()) {
            throw domain_error("Tienda sin camisetas");
        }

        mapaColores[barraCamis.back()] -= 1;
        barraCamis.pop_back();
    }

    //int = n camis COMO MINIMO hay que comprar para que te de la primera cami unica (por ambos lados)
    //
    pair<int, string>pregunta() {
        int minimo = 1;
        string lado = "";
        auto itD = barraCamis.rbegin();
        auto itI = barraCamis.begin();

        bool encontrado = false;
        
        while ((itD != barraCamis.rend() && itI != barraCamis.end()) && !encontrado) {
           
            if (mapaColores[*itD] == 1 && mapaColores[*itI] > 1) {
                lado = "DERECHA";
                encontrado = true;
            }
            else if (mapaColores[*itI] == 1 && mapaColores[*itD] > 1) {
                lado = "IZQUIERDA";
                encontrado = true;
            }
            else if (mapaColores[*itI] == 1 && mapaColores[*itD] == 1) {
                lado = "CUALQUIERA";
                encontrado = true;
            }
            else {
                //avanzamos los iteradores
                ++itI;
                ++itD;
                minimo++;
            }   
        }
        if (lado == "") {
            return { -1, "" };
        }
        else {
            return {minimo, lado};
        }
    }



private:

    //por cada color el numer de camisetas que hay de ese color
    unordered_map<string, int> mapaColores;

    //doble cola con las camisetas
    deque<string> barraCamis;

};



bool tratar_caso() {
    TiendaCamisetas tc;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "inserta_derecha") {
                string color;
                cin >> color; 
                tc.inserta_derecha(color);
            }
            else if (comando == "inserta_izquierda") {
                string color;
                cin >> color;
                tc.inserta_izquierda(color);
            }
            else if (comando == "compra_derecha") {
                tc.compra_derecha();
            }
            else if (comando == "compra_izquierda") {
                tc.compra_izquierda();
            }
            else if (comando == "pregunta") {
                pair<int, string> p = tc.pregunta();
                if (p.first == -1) {
                    cout << "NADA INTERESANTE" << "\n";
                }
                else {
                    cout << p.first << " " << p.second << "\n";
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


