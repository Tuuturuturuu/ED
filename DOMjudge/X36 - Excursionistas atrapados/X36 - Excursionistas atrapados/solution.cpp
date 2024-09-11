// Excursionistas atrapados
// ------------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
#include <fstream>
#include <utility>

// TAD de árboles binarios de búsqueda
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
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

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

// Devuelve:
//  - Primera componente: nº de equipos de rescate necesarios
//  - Segunda componente: número de excursionistas que se encuentran en la ruta con más excursionistas
pair<int, int> excursionistas(const BinTree<int>& t) {

    //casos base
    if (t.empty()) {//si el nodo es vacio
        return{ 0,0 };
    }
    if (t.left().empty() && t.right().empty()) {//si el nodo es hoja
        if (t.root() != 0) {
            return{ 1, t.root() };
        }
        else {
            return { 0, 0 };
        }
    }

    //llamadas recursivas
    auto [eqI, exI] = excursionistas(t.left());
    auto [eqD, exD] = excursionistas(t.right());


    if (t.root() != 0 && eqI == 0 && eqD == 0) //si ambos elementos hijos son 0 y hay u ngrupo de excursionistas
        return{ 1, t.root() + max(exI, exD) };
    else
        return{ eqD + eqI, t.root() + max(exI,exD) };
}
    
 


void tratar_caso() {
    // Introduce aquí el código para tratar un caso de prueba.

    BinTree<int> t = read_tree<int>(cin);
    auto [num_equipos, max_rescate] = excursionistas(t);

    cout << num_equipos << " " << max_rescate << "\n";
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    // La entrada comienza por el número de casos de prueba
    int num_casos;
    cin >> num_casos;

    // Ejecutamos tratar_caso() tantas veces como el primer número leído
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}