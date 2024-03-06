/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */


 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
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


  // A�ade los #include que necesites
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <stack>

using namespace std;


//@ <answer>
// Implementa la funci�n pedida aqu�.
// Para ello utiliza las librer�as de la STL.
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
// No modificar nada por debajo de esta l�nea
// -------------------------------------------------------------
//@ </answer>


// Funci�n que trata un caso de prueba.
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

    // Llamamos a la funci�n pedida
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
    // Si est�s ejecutando el programa en tu ordenador, las siguientes l�neas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // �til para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las l�neas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Ejecutamos tratar_caso() hasta que nos devuelva `false`
    while (tratar_caso()) {}

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
