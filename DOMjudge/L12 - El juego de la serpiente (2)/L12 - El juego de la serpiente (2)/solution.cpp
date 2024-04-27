/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Indica el nombre y apellidos de los componentes del grupo
    ---------------------------------------------------------
    Componente 1:Sofia Postigo
    Componente 2:Sergio Tarancon
  */
  //@ </answer>

  // Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <functional>
#include <cassert>
#include <queue>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>
#include <map>

using namespace std;

using namespace std;

// Tipo para representar una posición en la cuadrícula mediante un par de
// coordenadas
struct Posicion {
    int x, y;

    Posicion() : Posicion(0, 0) { }
    Posicion(int x, int y) : x(x), y(y) { }

    bool operator==(const Posicion& other) const {
        return x == other.x && y == other.y;
    }
};

// Definimos una función hash para el tipo Posicion.
template<>
class std::hash<Posicion> {
public:
    int operator()(const Posicion& p) const {
        return p.x ^ (p.y << 1);
    }
};

// Tipo de datos enumerado para representar direcciones
enum class Direccion { Norte, Sur, Este, Oeste };

// Sobrecargamos el operador >> para poder leer direcciones más fácilmente.
// Bastará con hacer `cin >> d` donde `d` es una variable de tipo Direccion.
istream& operator>>(istream& in, Direccion& d) {
    string s; in >> s;
    if (s == "N") {
        d = Direccion::Norte;
    }
    else if (s == "S") {
        d = Direccion::Sur;
    }
    else if (s == "E") {
        d = Direccion::Este;
    }
    else if (s == "O") {
        d = Direccion::Oeste;
    }
    return in;
}

// Tipo de datos enumerado para representar elementos del tablero
enum class Elemento { Manzana, Serpiente, Nada };

// Sobrecargamos el operador << para poder escribir elementos del tablero más
// fácilmente. Bastará con hacer `cout << e` donde `e` es una variable de
// tipo Elemento.
ostream& operator<<(ostream& out, const Elemento& e) {
    switch (e) {
    case Elemento::Manzana: out << "MANZANA"; break;
    case Elemento::Serpiente: out << "SERPIENTE"; break;
    case Elemento::Nada: out << "NADA"; break;
    }
    return out;
}

//--------------------------------------------------------------------------
// Modificar a partir de aquí
//--------------------------------------------------------------------------
//@ <answer>

// TAD para el juego de la serpiente. Implementa cada una de las operaciones,
// y justifica su coste.
class JuegoSerpiente {
public:
    JuegoSerpiente() {

    }

    //Complejidad: O(logM) (logaritmica) siendo M el numero de serpientes que hay en el mapa de puntuaciones (en el juego)
    void nueva_serpiente(const string& nombre, const Posicion& posicion) {

        if (mapaSerpientes.count(nombre)) {
            throw domain_error("Serpiente ya existente");
        }
        if (que_hay(posicion) != Elemento::Nada) {
            throw domain_error("Posicion ocupada");
        }

        //añadir la posicion al cuerpo de la serpiente
        InfoSerpiente infoSerpiente(posicion);
        infoSerpiente.cuerpo.push_back(posicion);

        //añadimos la serpiente al mapa de puntuaciones con puntuacion 0
        infoSerpiente.ptrPuntos = mapaPuntuaciones.insert(make_pair(0, nombre));//O(logM)

        mapaSerpientes[nombre] = infoSerpiente;
        //marcar la posicion del tablero introducida como ocupada por una serpiente
        tablero[posicion] = Elemento::Serpiente;
    }

    //Complejidad: O(1) (constante)
    void nueva_manzana(const Posicion& posicion, int crecimiento, int puntuacion) {
        if (que_hay(posicion) != Elemento::Nada) {
            throw domain_error("Posicion ocupada");
        }

        mapaManzanas[posicion].puntos = puntuacion;
        mapaManzanas[posicion].crecimiento = crecimiento;

        //marcar la posicion del tablero introducida como ocupada por una manzana
        tablero[posicion] = Elemento::Manzana;
    }

    //Complejidad: O(1) (constante)
    int puntuacion(const string& nombre) const {
        if (!mapaSerpientes.count(nombre)) {
            throw domain_error("Serpiente no existente");
        }
        return mapaSerpientes.at(nombre).puntos;
    }

    //Complejidad: avanzar la serpiente tiene coste O(1) (constante), excepto en el 
    //caso de que la serpiente sea eliminada, en cuyo caso el coste sería O(N), siendo N el numero de elementos del cuerpo 
    //de la serpiente a eliminar/la longitud de esta.
    // Ademas en el caso en el que una serpiente coma una manzana de puntuacion mayor a 0, el coste de inserción en el mapa 
    // de Puntuaciones sería O(logM) con M siendo el numero de serpientes del mapa de Puntuaciones (y del juego)
    bool avanzar(const string& nombre, const Direccion& dir) {
        bool ret = false;

        if (!mapaSerpientes.count(nombre)) {
            throw domain_error("Serpiente no existente");
        }

        //el mapa de serpientes se actualizará automaticamente con todos los cambios
        //que se le hagan a infoS, pues se ha declarado como &infoS
        InfoSerpiente& infoS = mapaSerpientes[nombre];

        //se aumentan las coords de la cabeza de la serpiente en la direccion introducida
        int x = infoS.pos.x;
        int y = infoS.pos.y;

        switch (dir) {
        case Direccion::Norte:
            y += 1;
            break;
        case Direccion::Sur:
            y -= 1;
            break;
        case Direccion::Este:
            x += 1;
            break;
        case Direccion::Oeste:
            x -= 1;
            break;
        }

        //comprobamos si la casilla destino a la que queremos avanzar la cabeza esta ocupada y que elemento ocupa
        if (que_hay({ x,y }) == Elemento::Serpiente) {//casilla ocupada por serpiente 

            if ((infoS.cuerpo.back().x == x) && (infoS.cuerpo.back().y == y) && infoS.crecimiento == 0) {//la casilla destino es la que ocupa la cola de la misma serpiente
                movimiento(nombre, x, y, infoS);//O(1)
            }
            else {
                int longitud = mapaSerpientes[nombre].cuerpo.size();

                //O(N) siendo N el numero de posiciones que ocupa la serpiente en el tablero (la longitud total de la serpiente)
                for (int i = 0; i < longitud; i++) {//se elimina todo el cuerpo de la serpiente al morir
                    tablero[infoS.cuerpo.front()] = Elemento::Nada;
                    infoS.cuerpo.pop_front();
                }
                //eliminas del mapa de puntuaciones la serpiente que ha comido la manzana para mas tarde volverla a añadir con su nueva puntuacion
                mapaPuntuaciones.erase(infoS.ptrPuntos);//O(1)

                mapaSerpientes.erase(nombre);//se elimina la serpiente del juego

                
                ret = true;
            }
        }
        else if (que_hay({ x,y }) == Elemento::Manzana) {//casilla ocupada por manzana

            //se desplaza la serpiente
            movimiento(nombre, x, y, infoS);//O(1)
            if (mapaManzanas[{x, y}].puntos != 0) {
                //eliminas del mapa de puntuaciones la serpiente que ha comido la manzana para mas tarde volverla a añadir con su nueva puntuacion
                mapaPuntuaciones.erase(infoS.ptrPuntos);//O(1) (estamos accediendo directamente ci nel iterador a la posicion que queremos)
                //sumas a la serpiente los puntos adquiridos por la manzana
                infoS.puntos += mapaManzanas[{x, y}].puntos;

                //añades la serpiente de nuevo al mapa de puntuaciones con su nueva puntuacion
                infoS.ptrPuntos = mapaPuntuaciones.insert(make_pair(infoS.puntos, nombre));//O(logM)
            }
            //sumas a la serpiente el crecimiento que otorga la manzana
            infoS.crecimiento += mapaManzanas[{x, y}].crecimiento;
            //borras la manzana del juego
            mapaManzanas.erase({ x,y });
        }
        else {//si la casilla destino está vacia se desplaza la serpinete de forma normal
            movimiento(nombre, x, y, infoS);//O(1)
        }

        return ret;
    }

    //Complejidad: O(1) (constante)
    Elemento que_hay(const Posicion& p) const {
        if (!tablero.count(p)) {//si esa posicion del tablero un no existe, devuelve/la "inicializa" a nada
            return Elemento::Nada;
        }
        else {
            return tablero.at(p);
        }
    }

    //O(T) siendo T en el peor caso, el numero de serpientes cuyas puntuaciones queremos mostrar ("num" introducido por parametro)
    vector<pair<string, int>> mejores_puntuaciones(int num) const {
        vector<pair<string, int>> v;  
        auto it = mapaPuntuaciones.begin();
        for (int i = 0; i < num && it !=mapaPuntuaciones.end(); i++) {
            v.push_back({it->second, it->first});
            ++it;
        }
        return v;
    }

private:
    // Añade los atributos y funciones privadas que veas necesarias.
    struct InfoSerpiente {
        Posicion pos;
        multimap<int, string, greater<int>>::iterator  ptrPuntos;//puntero a la posicion de la serpiente en el mapa de puntuaciones
        int puntos;
        int crecimiento;
        list<Posicion> cuerpo;
        InfoSerpiente() {}
        InfoSerpiente(Posicion pos) : pos(pos), puntos(0), crecimiento(0) { };
    };

    struct InfoManzana {
        int puntos;
        int crecimiento;
        InfoManzana() {}
        InfoManzana(int p, int c) : puntos(p), crecimiento(c) { };
    };

    //mapa del tablero que relaciona las posiciones (claves) con el elemento que hay en cada una de esas posiciones
    unordered_map<Posicion, Elemento> tablero;

    //mapa de serpientes cuyas claves son los nombres de las serpientes y sus valores son la informacion de la serpiente con ese nombre
    //(InfoSerpiente que contiene la posicion, puntos, creciineto y cuerpo de la serpiente)
    unordered_map<string, InfoSerpiente> mapaSerpientes;

    //mapa de manzanas que tiene una clave con la posicion de cada manzana y cuyo valor es la informacion de esa manzana
    //(InfoManzana, que contiene los puntos y el crecimiento que otorga la manzana
    unordered_map<Posicion, InfoManzana> mapaManzanas;

    //multimapa cuyas claves son las disintas puntaciones que van tomando las serpientes (int) y sus valores los
    //nombres de la/las serpientes que poseen esa puntuacion (string)
    multimap<int, string, greater<int>> mapaPuntuaciones;


    //metodo privado el cual  dado un nombre de una serpiente que se desea desplazar, unas coordenadas y la informacion de esa serpiente,
    //desplaza la serpiente a esa posicion y gestiona el crecimiento de esta
    //Complejidad: O(1) (constante)
    void movimiento(const string& nombre, int& x, int& y, InfoSerpiente& i) {
        i.pos.x = x;
        i.pos.y = y;

        tablero[{x, y}] = Elemento::Serpiente;
        i.cuerpo.push_front({ x, y });//O(1)

        if (i.crecimiento == 0) {
            tablero[i.cuerpo.back()] = Elemento::Nada;//O(1)
            i.cuerpo.pop_back();//O(1)
        }

        if (i.crecimiento > 0) {
            i.crecimiento--;
        }
    }
};

// Función para tratar un caso de prueba. Devuelve false si, en lugar de un
// caso de prueba, se ha encontrado con la marca de fin de entrada
// (EOF). Devuelve true en caso contrario.

//Complejidad: en el caso general, tiene coste O(1) (constante), excepto en el 
//caso de que se avance una serpiente y esta sea eliminada, en cuyo caso el coste sería O(N), siendo N el numero de elementos del cuerpo 
//de la serpiente a eliminar/la longitud de esta
//En el caso de mostrar las T serpientes con mas puntuacion, ("mejores_puntuaciones"), el coste será O(T)
bool tratar_caso() {
    // Implementar
    JuegoSerpiente juego;
    string instruc, nom;
    Direccion dir;
    int x, y, punt, crecimiento;
    cin >> instruc;

    if (cin.eof()) return false;

    while (instruc != "FIN") {
        try {
            if (instruc == "nueva_serpiente") {
                cin >> nom >> x >> y;
                juego.nueva_serpiente(nom, { x,y });//O(logM)
            }
            else if (instruc == "nueva_manzana") {
                cin >> x >> y >> crecimiento >> punt;
                juego.nueva_manzana({ x,y }, crecimiento, punt);//O(1)
            }
            else if (instruc == "que_hay") {
                cin >> x >> y;
                cout << juego.que_hay({ x,y }) << "\n";//O(1)
            }
            else if (instruc == "avanzar") {
                cin >> nom >> dir;
                if (juego.avanzar(nom, dir)) {//O(1)/O(N)/O(logM) con N = longitud de la serpiente a eliminar, M = numero de serpientes del juego
                    cout << nom << " muere\n";
                }
            }
            else if (instruc == "puntuacion") {
                cin >> nom;
                int puntos = juego.puntuacion(nom);//O(1)
                cout << nom << " tiene " << puntos << " puntos\n";
            }
            else if (instruc == "mejores_puntuaciones") {
                cin >> punt;
                vector<pair<string, int>> v = juego.mejores_puntuaciones(punt);//O(T) siendo T = punt

                cout << "Las " << v.size() << " mejores puntuaciones:\n";
                for (int i = 0; i < v.size(); i++) {
                    cout << "  " << v[i].first << " (" << v[i].second << ")\n";
                }
            }
        }
        catch (exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> instruc;
    }
    cout << "---\n";

    return true;
}


//@ </answer>
//--------------------------------------------------------------------------
// No modificar a partir de aquí
//--------------------------------------------------------------------------


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

    // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
    while (tratar_caso()) {}

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
