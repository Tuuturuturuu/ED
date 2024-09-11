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
    Componente 1:Sergio Tarancon
    Componente 2:Sofia Postigo  
  */
  //@ </answer>


  // A�ade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>  // Para la clase pair
#include <tuple>    // Para la clase tuple
#include <algorithm>


    using namespace std;

    /*
  Implementaci�n de �rboles binarios vista en clase
*/

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definici�n de NodePointer,
    // que TreeNode va a ser definida m�s adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}




//@ <answer>
// ----------------------------------------------
// Modificar a partir de aqu�
// ----------------------------------------------

// Implementa la funci�n pedida a continuaci�n e indica y justifica su coste.

// Puedes definir las funciones auxiliares que sean necesarias. Para cada una
// de ellas, indica y justifica su coste.

//Recurrencia:T(n) = { k1  si 1 <= n < 2 
//                   { 2T(n/2) + k2n si n >= 2
//Complejidad: O(n) siendo n el n�mero de nodos del �rbol
template <typename T>
int calcularMellas(const BinTree<T>& t,int alt, int i, bool &isLastFull) {
    int mellas = 0;
    // i = atura por la que vas recorriendo (comienza en 1)
    // casos base
    if (alt == 1) {//arbol de altura 1
        return 0;
    }
    if (i == alt - 1) {//llegamos penultima altura del arbol

        if (isLastFull == t.left().empty() && t.left().empty()) {
            mellas = 1;
        }
        isLastFull = !t.left().empty();

        if (isLastFull == t.right().empty() && t.right().empty()) {
            mellas = 1;
        }
        isLastFull = !t.right().empty();
    }
    else {//llamadas recursivas
        if (!t.empty()) {
            mellas += calcularMellas(t.left(), alt, i + 1, isLastFull);
            mellas += calcularMellas(t.right(), alt, i + 1, isLastFull);
        } 
    }
    return mellas;
}

//Recurrencia:T(n) = { k1  si 1 <= n < 2 
//                   { 2T(n/2) + k2n si n >= 2
//Complejidad: O(n) siendo n el n�mero de nodos del �rbol
template <typename T>
int altura(const BinTree<T>& t) {
    //caso base 
    if (t.empty()) return 0;
    if (t.left().empty() && t.right().empty()) return 1;

    //caso recursivo
    int altD = altura(t.right());
    int  altI = altura(t.left());

    return max(altD,altI) + 1;
}

//Complejidad: O(n) siendo n el n�mero de nodos del �rbol
template <typename T>
int num_mellas(const BinTree<T>& t) {
    int alt = altura(t);//O(n)
    int mellas = 0;//contador de mellas
    //el booleano comienza a true para contabilizar el caso en el que haya una mella en el primer hijo
    bool isLastFull = true;
    if (alt >= 1) {
        mellas = calcularMellas(t, alt, 1, isLastFull);//O(n)
    }
    return mellas;
} 

// ----------------------------------------------
// No modificar a partir de la l�nea
// ----------------------------------------------
//@ </answer>

// Funci�n para tratar UN caso de prueba.
void tratar_caso() {
    BinTree<char> t = read_tree<char>(cin);
    cout << num_mellas(t) << "\n";
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

    // La entrada comienza con el n�mero de casos de prueba.
    int num_casos;
    cin >> num_casos;

    // Llamamos a `tratar_caso` tantas veces como el n�mero anterior.
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
