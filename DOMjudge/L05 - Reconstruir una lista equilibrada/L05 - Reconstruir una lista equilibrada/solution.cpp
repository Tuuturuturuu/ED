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
    Componente 1: Sergio Tarancon
    Componente 2: Sofia Postigo
  */
  //@ </answer>


  // Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <stack>

using namespace std;


//@ <answer>
// Implementa la función pedida aquí.
// Para ello utiliza las librerías de la STL.
//
// No olvides justificar brevemente el coste.
//

//O(N) siendo N el numero de elementos de la lista introducida
void reconstruir(list<int>& lista) {
    stack<int> pila;
    auto it = lista.begin();
    bool erasedElem = false;

    // contemplar que la lista no sea vacia
    //O(N) siendo N el numero de elementos de la lista introducida
    while (!lista.empty() && it != lista.end()) {
        erasedElem = false;

        if (*it > 0) {//el numero es positivo
            pila.push(-*it); //O(1)
        }
        else if (*it == 0) {//el numero es 0 asi que lo sobreescribimos
            if (!pila.empty()) {
                *it = pila.top(); //O(1)
                pila.pop();//O(1)
            }
            else {//si solo son ceros 
                it = lista.erase(it);
                erasedElem = true;
            }
        }
        else {//el numero es negativo
            if (pila.empty()|| *it != pila.top()) {//si es distinto a lo que hay en la pila se elimina
                it = lista.erase(it);
                erasedElem = true;
            }
            else {
                pila.pop();
            }
        }

        if (!erasedElem)
            ++it;
    }

    //O(N) en el peor de los casos siendo N el numero elementos positivos de la lista introducida
    while (!pila.empty()) {
        lista.push_back(pila.top());
        pila.pop();
    }
}

//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>


// Función que trata un caso de prueba.
bool tratar_caso() {
    int num_elems;
    list<int> lista;

    cin >> num_elems;
    if (cin.eof()) return false;

    // Leemos lista
    for (int i = 0; i < num_elems; i++) {
        int elem;
        cin >> elem;
        lista.push_back(elem);
    }

    // Llamamos a la función pedida
    reconstruir(lista);

    // Imprimimos el resultado
    bool primero = true;
    for (auto x : lista) {
        cout << (primero ? "" : " ") << x;
        primero = false;
    }
    cout << "\n";

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

    // Ejecutamos tratar_caso() hasta que nos devuelva `false`
    while (tratar_caso()) {}

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
