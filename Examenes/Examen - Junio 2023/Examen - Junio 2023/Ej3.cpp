
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <set>
#include <queue>
#include <map>
#include <fstream>

using namespace std;

class SistemaBatallas {
public:

    SistemaBatallas() {  }

    void aparece_villano(const std::string& v, int s, int a) {
        if(mapaVillanos.count(v)){
            throw invalid_argument("Personaje ya existente");
        }
        mapaVillanos[v].danoAtaque = a;
        mapaVillanos[v].vida = s;
       
        //registrar en batalla/turnos
        colaDeTurnos.push_front({v,s});
        mapaVillanos[v].posTurno = colaDeTurnos.begin();
       
    }

    void aparece_heroe(const std::string& h, int s) {
        if (mapaHeroes.count(h)) {
            throw invalid_argument("Personaje ya existente");
        }
        mapaHeroes[h].vida = s;
        //registrar en batalla/turnos
        colaDeTurnos.push_front({ h,s });
        mapaHeroes[h].posTurno = colaDeTurnos.begin();
    }
    
    void aprende_ataque(const std::string& h, const string& a, int v) {
        if (!mapaHeroes.count(h)) {
            throw invalid_argument("Heroe inexistente");
        }
        if (mapaHeroes[h].listaAtaques.count(a)) {
            throw invalid_argument("Ataque repetido");
        }
        mapaHeroes[h].listaAtaques.insert({ a,v });
    }

    vector<pair<string, int>> mostrar_ataques(const std::string& h) const {
        if (!mapaHeroes.count(h)) {
            throw invalid_argument("Heroe inexistente");
        }
        vector<pair<string, int>> listaAtaques;
        for (auto it = mapaHeroes.at(h).listaAtaques.begin(); it != mapaHeroes.at(h).listaAtaques.end(); ++it) {
            listaAtaques.push_back(make_pair(it->first, it->second));
        }
        return listaAtaques;
    }

    vector<pair<string, int>> mostrar_turnos() const {
        //vector<pair<string, int>> listaTurnos = colaDeTurnos;
        vector<pair<string, int>> listaTurnos;
        
        for (auto it = colaDeTurnos.rbegin(); it != colaDeTurnos.rend(); ++it) {
            listaTurnos.push_back(make_pair(it->first, it->second));   
        }
        return listaTurnos;
    }

    bool villano_ataca(const std::string& v, const std::string& h) {
        if (!mapaHeroes.count(h)) {
            throw invalid_argument("Heroe inexistente");
        }
        if (!mapaVillanos.count(v)) {
            throw invalid_argument("Villano inexistente");
        }
        if(colaDeTurnos.back().first != v) {//si no es el turno del villano que te pasan
            throw invalid_argument("No es su turno");
        }

        bool ret = false;
        //se le resta vida al heroe
        mapaHeroes[h].vida -= mapaVillanos[v].danoAtaque;

        //actualizamos la cola de turnos
        auto it = colaDeTurnos.insert(mapaHeroes[h].posTurno, { h,mapaHeroes[h].vida });
        colaDeTurnos.erase(mapaHeroes[h].posTurno);
        mapaHeroes[h].posTurno = it;
        //auto it = colaDeTurnos.begin();
        //while (it != mapaHeroes[h].posTurno) { ++it; }
        //it->second = mapaHeroes[h].vida;
        
        //si al atacar se queda sin vida se le borra del mapa del heroes y de la cola de Turnos
        if (mapaHeroes[h].vida <= 0) {
            colaDeTurnos.erase(mapaHeroes[h].posTurno);
            mapaHeroes.erase(h);
            ret = true;
        }
        //actualizamos la cola de turnos, quitamos al villano de la pos y le reañadimos al final axctualizando tambien el pnutero al turno
        colaDeTurnos.pop_back();
        colaDeTurnos.push_front({v,mapaVillanos[v].vida});
        mapaVillanos[v].posTurno = colaDeTurnos.begin();

        return ret;
    }

    bool heroe_ataca(const std::string& v, const std::string& h, const std::string& a) {
        if (!mapaHeroes.count(h)) {
            throw invalid_argument("Heroe inexistente");
        }
        if (!mapaVillanos.count(v)) {
            throw invalid_argument("Villano inexistente");
        }
        if (colaDeTurnos.back().first != h) {
            throw invalid_argument("No es su turno");
        }
        if (!mapaHeroes[h].listaAtaques.count(a)) {
            throw invalid_argument("Ataque no aprendido");
        }

        bool ret = false;
        mapaVillanos[v].vida -= mapaHeroes[h].listaAtaques[a];

        //actualizamos la cola de turnos
        auto it = colaDeTurnos.insert(mapaVillanos[v].posTurno, {v,mapaVillanos[v].vida});
        colaDeTurnos.erase(mapaVillanos[v].posTurno);
        mapaVillanos[v].posTurno = it;
        //auto it = colaDeTurnos.begin();
        //while (it != mapaVillanos[v].posTurno) { ++it; }
        //it->second = mapaVillanos[v].vida;

        if (mapaVillanos[v].vida <= 0) {//si el villano muere se le elimina del mapa de  vilanos y de turnos
            colaDeTurnos.erase(mapaVillanos[v].posTurno);
            mapaVillanos.erase(v);
            ret = true;
        }

        //se elimina al heroe de la ista de turnos y se añade al final
        colaDeTurnos.pop_back();
        colaDeTurnos.push_front({ h,mapaHeroes[h].vida });
        mapaHeroes[h].posTurno = colaDeTurnos.begin();

        return ret;
    }

private:

    struct infoHeroe {
        
        int vida;
        list<pair<string, int>>::iterator posTurno;
        //nombre del ataque y dano que hace el ataque
        map<string, int> listaAtaques;
    };

    struct infoVillano {
       
        int vida;
        int danoAtaque;
        list<pair<string, int>>::iterator posTurno;
    };

    unordered_map<string, infoHeroe> mapaHeroes;

    unordered_map<string, infoVillano> mapaVillanos;

    //turno, nombre del personaje
    list<pair<string,int>> colaDeTurnos;
};



bool tratar_caso() {
    SistemaBatallas sb;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "aparece_villano") {
                string nombre;
                int vida, ataque;
                cin >> nombre >> vida >> ataque;
                sb.aparece_villano(nombre, vida, ataque);
            }
            else if (comando == "aparece_heroe") {
                string nombre;
                int vida, ataque;
                cin >> nombre >> vida;
                sb.aparece_heroe(nombre, vida);
            }
            else if (comando == "aprende_ataque") {
                string heroe, ataque;
                int puntos;
                cin >> heroe >> ataque >> puntos;
                sb.aprende_ataque(heroe,ataque,puntos);
            }
            else if (comando == "mostrar_ataques") {
                string heroe;
                cin >> heroe;
                vector<pair<string,int>> ataques = sb.mostrar_ataques(heroe);
                cout << "Ataques de " << heroe<< "\n";
                for (const pair<string,int>& a : ataques) {
                    cout << a.first << " " << a.second << "\n";
                }
            }
            else if (comando == "mostrar_turnos") {
                
                vector<pair<string, int>> turnos = sb.mostrar_turnos();
                cout << "Turno: \n";
                for (const pair<string, int>& t : turnos) {
                    cout << t.first << " " << t.second << "\n";
                }
            }
            else if (comando == "villano_ataca") {
                string villano, heroe;
                cin >> villano >> heroe;
                bool si = sb.villano_ataca(villano, heroe);
                cout << villano << " ataca a " << heroe << "\n";
                if (si) {
                    cout << heroe << " derrotado" << "\n";
                }
            }
            else if (comando == "heroe_ataca") {
                string villano, heroe,ataque;
                cin >> heroe >> ataque >> villano;
                bool si = sb.heroe_ataca(villano, heroe, ataque);
                cout << heroe << " ataca a " << villano << "\n";
                if (si) {
                    cout << villano << " derrotado" << "\n";
                } 
            }
        }
        catch (std::invalid_argument& e) {
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


