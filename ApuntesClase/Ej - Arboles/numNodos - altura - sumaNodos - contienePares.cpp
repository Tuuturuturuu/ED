#include "https://raw.githubusercontent.com/manuelmontenegro/ED-2021/master/arboles/bintree_v3/bintree.h"
#include <iostream>

using namespace std;

//calcular el numero de nodos de un arbol
template <typename T>
int numero_nodos(const BinTree<T> &tree) {
    //caso base
    if(tree.right().empty() && tree.left().empty())
        return 1;

    //caso recursivo
    int nodosD= 0, nodosI= 0;
    
    if(!tree.right().empty()){
        nodosD = numero_nodos(tree.right()); 
    }

    if(!tree.left().empty()){
        nodosI  = numero_nodos(tree.left()); 
    }
    //combinar resultados (operarlos)
    return nodosD + nodosI + 1;
}

//calcular la altura de un arbol
template <typename T>
int altura(const BinTree<T> &tree) {
    //caso base
    if(tree.right().empty() && tree.left().empty())
        return 1;
    //caso orecursivo
    int alturaD= 0, alturaI = 0;

    if(!tree.left().empty()){
        alturaI = altura(tree.left());
    }
    if(!tree.right().empty()){
        alturaD = altura(tree.right());
    }

    //calculo de resutados
    if(alturaI <= alturaD){
        return alturaD + 1;
    }
    else{
        return alturaI + 1;
    }
}


//calcular la suma de todos los valores de los nodos de un arbol
int suma_nodos(const BinTree<int> &tree) {
    //caso base
    if(tree.empty()){
        return 0;
    }
    if(tree.right().empty() && tree.left().empty()){
        return tree.root();
    }

    //caso recursivo
    int nodosI = suma_nodos(tree.right());
    int nodosD = suma_nodos(tree.left());

    //combinar resultados
    return nodosI + nodosD + tree.root();
}

//comprobar si el arbol cointiene o no 1 o mas numeros pares
bool contiene_pares(const BinTree<int> &tree) {
    // caso base
    if(tree.empty()) return false;
    if(tree.right().empty() && tree.left().empty()){
        return tree.root() % 2 == 0;
    }

    //paso recursivo -> no es necesario, se ponen directamente abajo las llamadas recurssivas para q en vez de 
    //ejecutarse SIEMPRE las llamadas recursivas, solo se haga si no se cumple la primera condicion del return

    // bool parI = contiene_pares(tree.left());
    // bool parD = contiene_pares(tree.right());

    //combinar solucion -> se DEBE PONER SI O SI LA PRIMERA CONDICION ESA, pues asi, si e nodo actual en el
    //que se esta es par, no hay que recorrer el resto del arbol y simplemente se devuelve true (te estarias
    //quitando de encima muchisimas llamadas recursivas que vienen a continuacionen el return)
    return tree.root()%2 == 0 || contiene_pares(tree.left()) || contiene_pares(tree.right());
}

int main() {
    BinTree<int> comun = {{7}, 3, {9}};
    BinTree<int> t1 = {{}, 5, comun};
    BinTree<int> t2 = {comun, 4, {8}};

    cout << "numero_nodos(comun) = " << numero_nodos(comun) << endl;
    cout << "numero_nodos(t1) = " << numero_nodos(t1) << endl;
    cout << "numero_nodos(t2) = " << numero_nodos(t2) << endl;


    cout << "altura(comun) = " << altura(comun) << endl;
    cout << "altura(t1) = " << altura(t1) << endl;
    cout << "altura(t2) = " << altura(t2) << endl;

    cout << "suma_nodos(comun) = " << suma_nodos(comun) << endl;
    cout << "suma_nodos(t1) = " << suma_nodos(t1) << endl;
    cout << "suma_nodos(t2) = " << suma_nodos(t2) << endl;

    cout << "contiene_pares(comun) = " << boolalpha << contiene_pares(comun) << endl;
    cout << "contiene_pares(t1) = " << boolalpha <<  contiene_pares(t1) << endl;
    cout << "contiene_pares(t2) = " << boolalpha <<  contiene_pares(t2) << endl;
    return 0;
}
