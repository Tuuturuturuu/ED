// Partición de una lista enlazada ordenada
// ----------------------------------------
// Estructuras de datos

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;
    void display_reverse(std::ostream& out) const;


    void display() const { display(std::cout); }
    void display_reverse() const { display_reverse(std::cout); }


    // Nuevo método
    // Se implementa más abajo
    void partition(int pivot);


private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);

    // Nuevos métodos
    // Se implementan más abajo
    static void attach(Node* node, Node* before);
    static void detach(Node* node);
};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}
void ListLinkedDouble::display_reverse(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->prev->value;
        Node* current = head->prev->prev; // faltaba un prev
        while (current != head) {
            out << ", " << current->value; // coma y value del reves
            current = current->prev;
        }
    }
    out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

// No olvides el coste!
void ListLinkedDouble::attach(Node* node, Node* before) {
    // Implementar
    //meter node en la lista despues de before
    node->next = before;
    node->prev = before->prev;

    //reajustar los punteros de la lista con node en medio
    before->prev->next = node;
    before->prev = node;
}

// No olvides el coste!
//Complejidad: O(1)
void ListLinkedDouble::detach(Node* node) {
    // Implementar
    //punteros de la lista se descuelgan de node
    node->next->prev = node->prev;
    node->prev->next = node->next;

    //next y prev de node apuntan a node
    node->next = node;
    node->prev = node;
}


// No olvides el coste!
void ListLinkedDouble::partition(int pivot) {
    // Implementar
    bool end = false;
    int s = this->size();
    if (s > 1 && !this->empty()) {
        Node* curr = this->head->next;
        Node* p = curr;
        int i = 1;
       /* curr = head->next;
        Desde i = 1 hasta size() :
            Si curr->value es menor o igual que el pivote, avanzar curr.
            Si curr->value es mayor que el pivote, desengancharlo y engancharlo antes de la cabeza(es decir, ponerlo al final) y actualizar curr*/

        while (curr != this->head) {
        //while(i < this->size()){
            //al principio coges p (el primer valor mayor que pivot) y luego en el reto de los casos no
            if (curr == this->head->next) {
                while (curr->value <= pivot && s > 0) {
                    curr = curr->next;
                    s--;
                }
                p = curr;
            }
            //si encunetra un nodo con un valor menor o igual que pivot lo mueve a detras de p
            if (curr->value <= pivot) {
                Node* currNext = curr->next;
                this->detach(curr);
                this->attach(curr, p);
                curr = currNext;
                
            }
            else {// si el valor del nodo es mayor que pivot avanza al elem siguiente
                curr = curr->next;
            }
            i++;
        }
       
    }
}



void tratar_caso() {
    int num, pivot;
    ListLinkedDouble lista;

    //leer la lista y el pivote
    cin >> num;
    while (num != 0) {
        lista.push_back(num);
        cin >> num;
    }
    cin >> pivot;

    //operar
    lista.partition(pivot);

    //mostrar la salida
    cout << lista << "\n";
    lista.display_reverse();
    cout << "\n";
}



int main() {
#ifndef DOMJUDGE
        std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}