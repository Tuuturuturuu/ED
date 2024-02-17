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
#include "list_linked_single.h"


int main() {
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

    
}