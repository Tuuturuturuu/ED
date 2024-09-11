// --------------------------------------------------------------
// Ejercicio 1

//#include <iostream>
//#include <cassert>
//#include <fstream>
//
//using namespace std;
//
//class ListLinkedSingle {
//private:
//    struct Node {
//        int value;
//        Node* next;
//    };
//
//public:
//    ListLinkedSingle() : head(nullptr) { }
//    ~ListLinkedSingle() {
//        delete_list(head);
//    }
//
//    ListLinkedSingle(const ListLinkedSingle& other)
//        : head(copy_nodes(other.head)) { }
//
//    void push_front(int elem) {
//        Node* new_node = new Node{ elem, head };
//        head = new_node;
//    }
//
//    void push_back(int elem);
//
//    void pop_front() {
//        assert(head != nullptr);
//        Node* old_head = head;
//        head = head->next;
//        delete old_head;
//    }
//
//    void pop_back();
//
//    int size() const;
//
//    bool empty() const {
//        return head == nullptr;
//    };
//
//    const int& front() const {
//        assert(head != nullptr);
//        return head->value;
//    }
//
//    int& front() {
//        assert(head != nullptr);
//        return head->value;
//    }
//
//    const int& back() const {
//        return last_node()->value;
//    }
//
//    int& back() {
//        return last_node()->value;
//    }
//
//    const int& at(int index) const {
//        Node* result_node = nth_node(index);
//        assert(result_node != nullptr);
//        return result_node->value;
//    }
//
//    int& at(int index) {
//        Node* result_node = nth_node(index);
//        assert(result_node != nullptr);
//        return result_node->value;
//    }
//
//
//    void display(std::ostream& out) const;
//    void display() const {
//        display(std::cout);
//    }
//
//    // Declaración del método. Impleméntalo antes de la
//    // función tratar_caso()
//    void ordenar_burbuja() {
//        Node* tope = nullptr;
//        while (tope != this->head) {
//            tope = desplazar_maximo(tope);
//        }
//    }
//private:
//    Node* head;
//
//    void delete_list(Node* start_node);
//    Node* last_node() const;
//    Node* nth_node(int n) const;
//    Node* copy_nodes(Node* start_node) const;
//    Node* desplazar_maximo(Node* tope);
//
//};
//
//ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
//    if (start_node != nullptr) {
//        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
//        return result;
//    }
//    else {
//        return nullptr;
//    }
//}
//
//void ListLinkedSingle::delete_list(Node* start_node) {
//    if (start_node != nullptr) {
//        delete_list(start_node->next);
//        delete start_node;
//    }
//}
//
//void ListLinkedSingle::push_back(int elem) {
//    Node* new_node = new Node{ elem, nullptr };
//    if (head == nullptr) {
//        head = new_node;
//    }
//    else {
//        last_node()->next = new_node;
//    }
//}
//
//void ListLinkedSingle::pop_back() {
//    assert(head != nullptr);
//    if (head->next == nullptr) {
//        delete head;
//        head = nullptr;
//    }
//    else {
//        Node* previous = head;
//        Node* current = head->next;
//
//        while (current->next != nullptr) {
//            previous = current;
//            current = current->next;
//        }
//
//        delete current;
//        previous->next = nullptr;
//    }
//}
//
//int ListLinkedSingle::size() const {
//    int num_nodes = 0;
//
//    Node* current = head;
//    while (current != nullptr) {
//        num_nodes++;
//        current = current->next;
//    }
//
//    return num_nodes;
//}
//
//
//ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
//    assert(head != nullptr);
//    Node* current = head;
//    while (current->next != nullptr) {
//        current = current->next;
//    }
//    return current;
//}
//
//ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
//    assert(0 <= n);
//    int current_index = 0;
//    Node* current = head;
//
//    while (current_index < n && current != nullptr) {
//        current_index++;
//        current = current->next;
//    }
//
//    return current;
//}
//
//void ListLinkedSingle::display(std::ostream& out) const {
//    //out << "[";
//    if (head != nullptr) {
//        out << head->value;
//        Node* current = head->next;
//        while (current != nullptr) {
//            out << " " << current->value;
//            current = current->next;
//        }
//    }
//    //out << "]";
//}
//
////metodo :)
//ListLinkedSingle::Node* ListLinkedSingle::desplazar_maximo(Node* tope) {
//    
//    Node* curr = this->head;
//
//    if (!this->empty() && curr->next!= nullptr) {
//
//        Node* currNext = curr->next;
//        Node* currPrev = curr;
//
//        while (curr->next != tope && curr->next != nullptr) {
//            if (curr->value >= currNext->value) {//intercambias los valores
//                curr->next = currNext->next;
//                currNext->next = curr;
//                if (curr == head) {
//                    this->head = currNext;
//                    //currPrev = currNext;
//                }
//                else {
//                    currPrev->next = currNext;
//                }
//                currPrev = currNext;
//                currNext = currNext->next->next;
//            }
//            else {
//                if (curr == head) {
//                    curr = curr->next;
//                    currNext = currNext->next;
//                }
//                else {
//                    curr = curr->next;
//                    currNext = currNext->next;
//                    currPrev = currPrev->next;
//                }  
//            }
//        }
//    }
//    
//    return curr;
//}



//bool tratar_caso() {
//    // Introduce aquí el código para tratar un caso de prueba.
//    bool ret = false;
//    int N, num;
//    ListLinkedSingle lista;
//    cin >> N;
//    if (N != 0) {
//        ret = true;
//        for (int i = 0; i < N; i++) {
//            cin >> num;
//            lista.push_back(num);
//        } 
//
//        lista.ordenar_burbuja();
//        lista.display();
//        cout << "\n";
//    }
//    return ret;
//}
// --------------------------------------------------------------


//int main() {
//
//    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
//    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
//    // útil para no tener que teclear los casos de prueba por teclado cada vez
//    // que ejecutas el programa.
//    //
//    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
//    // comenta las líneas comprendidas entre los #ifndef y #endif
//#ifndef DOMJUDGE
//    std::ifstream in("sample.in");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf());
//#endif
//
//    // La entrada comienza con el número de casos de prueba.
//    
//
//    // Llamamos tantas veces a `tratar_caso` como nos diga el número.
//    while (tratar_caso()) {
//    }
//
//    // Comenta esto también si has comentado lo anterior.
//#ifndef DOMJUDGE
//    std::cin.rdbuf(cinbuf);
//#endif
//    return 0;
//}

