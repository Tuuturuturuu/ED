#include <iostream>
#include <cassert>
#include <memory>
#include <fstream>
#include <utility>

using namespace std;

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

tuple<bool, int, int> esABB(const BinTree<int>& tree) {
    if (tree.empty()) {
        return { true, 0, 0 };
    }
    if (tree.left().empty() && tree.right().empty()) {
        return { true, tree.root(), tree.root()};
    }

    auto[abbI, minI, maxI]= esABB(tree.left());
    auto[abbD, minD, maxD] = esABB(tree.left());
    
    bool esAbb = false;
    int min, max;
    if (tree.root() % 2 == 0) {//nodo es par
        if (abbI && abbD && (minI % 2 == 0 && minI > tree.root()) && (maxD %2 == 0 && maxD < tree.root())) {
            esAbb = true;
        }
        else if (minI % 2 == 0 && minI <= tree.root() ){
            min = tree.root();
        }
        else if (maxD % 2 == 0 && maxD >= tree.root()) {
            max = tree.root();
        }
        
    }
    else {//nodo impar
        if (abbI && abbD && (maxI % 2 != 0 && maxI < tree.root()) && (minD % 2 != 0 && minD > tree.root())) {
            esAbb = true;
        }
        else if (maxI % 2 != 0 && maxI >= tree.root()) {
            min = tree.root();
        }
        else if (minD % 2 != 0 && minD <= tree.root()) {
            max = tree.root();
        }
    }
    return {esAbb, min, max};
}

bool es_abbp(const BinTree<int>& tree) {

    tuple<bool, int, int>  tupla = esABB(tree);
    return std::get<0>(tupla);
}


// Funci�n que trata un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    bool abp = es_abbp(t);
    if (abp) cout << "SI\n";
    else  cout << "NO\n";
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
