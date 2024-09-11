
#include <iostream>
#include <fstream>

#include <cassert>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        string value;
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

    void push_front(const string& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const string& elem) {
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

    const string& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    string& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const string& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    string& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const string& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    string& operator[](int index) {
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

    void display() const { display(std::cout); }

    // El método se implementa más abajo, fuera de la definición de la clase.
    void rotar_derecha();

private:
    // Declara aquí los métodos auxiliares privados que necesites,

    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
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


std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

//hacer aqui la funcion
//Complejidad: O(N) siendo N el numero de elementos de la lista

void ListLinkedDouble::rotar_derecha() {
    if (!this->empty() && this->size() > 1) {
        Node* curr = head->next;
        Node* currNextI = head->next->next->next;
        bool end = false;
        while (!end) {

            if ((this->size() % 2) != 0) {//numero impar de elems
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;

                curr->next = currNextI;
                curr->prev = currNextI->prev;

                currNextI->prev->next = curr;
                currNextI->prev = curr;
                if (curr->prev != head && currNextI->prev->prev != head) {
                    curr = currNextI;
                    currNextI = currNextI->next->next;
                }
                else {
                    end = true;
                }
            }
            else {//numero par de elementos
                if (currNextI == head) {
                    curr->next->prev = curr->prev;
                    curr->prev->next = curr->next;

                    curr->next = currNextI->next;
                    curr->prev = currNextI;

                    currNextI->next->prev = curr;
                    currNextI->next = curr;

                    end = true;
                }
                else {
                    curr->next->prev = curr->prev;
                    curr->prev->next = curr->next;

                    curr->next = currNextI;
                    curr->prev = currNextI->prev;

                    currNextI->prev->next = curr;
                    currNextI->prev = curr;

                    //avanzar punteeros
                    curr = currNextI;
                    currNextI = currNextI->next->next;
                }
            }
        }
    }
}


bool tratar_caso() {
    // Escribe aquí el código para leer de la entrada
    // un caso de prueba y procesarlo.
    bool ret = true;

    int N;
    string elem;
    ListLinkedDouble lista;

    if(cin >> N) {
        for (int i = 0; i < N; i++) {
            cin >> elem;
            lista.push_back(elem);
        }

        lista.rotar_derecha();
        lista.display();
        cout << "\n";
    }
    else {
        ret = false;
    }
    
    return ret;
}

int main() {

    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // La entrada comienza con el número de casos de prueba.
    

    // Llamamos tantas veces a `tratar_caso` como nos diga el número.
    while (tratar_caso()) {
    }

    // Comenta esto también si has comentado lo anterior.   
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

