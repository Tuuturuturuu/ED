// Di�metro de un �rbol binario
// ----------------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
#include <algorithm>
#include<fstream>
#include <utility>

// TAD de �rboles binarios de b�squeda
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

using namespace std;


// Define las funciones auxiliares que sean necesarias

//primer elemento(first): devuelve la longitud de la rama las larga del arbol
//segundo elemento(second): devuelve el diametro de este arbol
template <typename T>
pair<int, int> calcular(const BinTree<T>& t) {

    //casos base
    if (t.empty()) return { 0,0 };
    if (t.right().empty() && t.left().empty()) {//si es hoja
        return { 1, 1};
    }

    //casos recursivos
    auto[ramaMasLargaI, diamI] = calcular(t.left());
    auto[ramaMasLargaD, diamD] = calcular(t.right());

    int diamRamas = 1 + ramaMasLargaI + ramaMasLargaD;
    int diamActual = max(max(diamI, diamD), diamRamas);
    
    return {1 + max(ramaMasLargaI, ramaMasLargaD), diamActual };
}

template <typename T>
int diametro(const BinTree<T>& t) {
    return calcular(t).second;  
}   


void tratar_caso() {
    BinTree<char> t = read_tree<char>(cin);
    cout << diametro(t) << "\n";
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    // La entrada comienza por el n�mero de casos de prueba
    int num_casos;
    cin >> num_casos;

    // Ejecutamos tratar_caso() tantas veces como el primer n�mero le�do
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}