// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
#include <fstream>
#include <utility>

using namespace std;

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

pair<int, int> botin_y_vida(const BinTree<int>& t) {
    if (t.empty()) {
        return{ 0,1};
    }
    if (t.left().empty() && t.right().empty()) {//es hoja
        if (t.root() == 0) {
            return {0, 2};
        }
        else if (t.root() > 0) {
            return{t.root(), 1};
        }
        else {//t.root() < 0
            return{0,  1 - t.root()};
        }
    }
    auto [botinI, vidaI] = botin_y_vida(t.left());
    auto [botinD, vidaD] = botin_y_vida(t.right());

    int botinNodo, vidaNodo;
    if (botinI > botinD) {
        if (t.root() > 0) {
            botinNodo = botinI + t.root();
            vidaNodo = vidaI;
        }
        else if (t.root() < 0) {
            botinNodo = botinI;
            vidaNodo = vidaI - t.root();
        }
        else {
            botinNodo = botinI;
            vidaNodo = vidaI - 1;
        }
    }
    else if (botinI < botinD) {
        if (t.root() > 0) {
            botinNodo = botinD + t.root();
            vidaNodo = vidaD;
        }
        else if (t.root() < 0) {
            botinNodo = botinD;
            vidaNodo = vidaD - t.root();
        }
        else {
            botinNodo = botinD;
            vidaNodo = vidaD - 1;
        }
    }
    else {//botinD == botinI
        if (vidaI < vidaD) {
            if (t.root() > 0) {
                botinNodo = botinI + t.root();
                vidaNodo = vidaI;
            }
            else if (t.root() < 0) {
                botinNodo = botinI;
                vidaNodo = vidaI - t.root();
            }
            else {
                botinNodo = botinI;
                vidaNodo = vidaI - 1;
            }
        }
        else {
            if (t.root() > 0) {
                botinNodo = botinD + t.root();
                vidaNodo = vidaD;
            }
            else if (t.root() < 0) {
                botinNodo = botinD;
                vidaNodo = vidaD - t.root();
            }
            else {
                botinNodo = botinD;
                vidaNodo = vidaD - 1;
            }
        }
    }
    return{botinNodo, vidaNodo};
}


// Función que trata un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    auto [b, v] = botin_y_vida(t);
    cout << b << " " << v << "\n";
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


