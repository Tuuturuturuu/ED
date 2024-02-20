/*
* ---------------------------------------------------
*                ESTRUCTURAS DE DATOS
* ---------------------------------------------------
*              Manuel Montenegro Montes
*              Facultad de Informática
*         Universidad Complutense de Madrid
* ---------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include "list_linked_single.h"

using namespace std;

void tratar_caso_duplicar() {
    ListLinkedSingle list;

    int elem;
    bool fin = false;
    while (!fin) {
        cin >> elem;
        if (elem == 0) { fin = true; }
        else {
            list.push_back(elem);
        }
    }

    list.duplicate();
    list.display();
    cout << endl;
}

void tratar_caso_invertir() {
    ListLinkedSingle list;

    int elem;
    bool fin = false;
    while (!fin) {
        cin >> elem;
        if (elem == 0) { fin = true; }
        else {
            list.push_back(elem);
        }
    }

    list.invert();
    list.display();
    cout << endl;
}

int main() {
    /*
    ListLinkedSingle l;
    l.push_back("Sofia");
    l.push_back("Diego");
    l.push_back("Dario");
    l.display(); std::cout << std::endl;

    //invert list
    std::cout << "Invertida:" << std::endl;
    l.invert();
    l.display(); std::cout << std::endl;
    
    //duplicate list
    std::cout << "Duplicada:" << std::endl;
    l.duplicate();
    l.display(); std::cout << std::endl;

    //merge two lists
    ListLinkedSingle list;
    list.push_back("b");
    list.push_back("d");
    list.push_back("e");

    ListLinkedSingle other;
    other.push_back("a");
    other.push_back("c");
    other.push_back("f");

    std::cout << "Mergeada con other:" << std::endl;
    list.merge(other);
    list.display(); std::cout << std::endl;

    */
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // La entrada comienza con el n�mero de casos de prueba.
    int num_casos;
    cin >> num_casos;

    // Llamamos tantas veces a `tratar_caso` como nos diga el n�mero.
    for (int i = 0; i < num_casos; i++) {
        tratar_caso_invertir();
    }

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}