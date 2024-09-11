
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

    void display() const { display(std::cout); }

    // El método se implementa más abajo, fuera de la definición de la clase.
    void desparizar(ListLinkedDouble& aux);
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
    //out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << " " << current->value;
            current = current->next;
        }
    }
    //out << "]";
}


std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}



//hacer aqui la funcion
void ListLinkedDouble::desparizar(ListLinkedDouble& aux) {
    Node* curr = this->head->next;
    Node* currNext = curr->next;
    Node* currAux = aux.head->prev;

    while (curr != head) {
        if ((curr->value % 2) == 0) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            if (currAux == head) {//si el elemento que se inserta es el primero
                curr->prev = currAux;
                curr->next = currAux;

                currAux->next = curr;
                currAux->prev = curr;
            }
            else {
                curr->next = currAux->next;
                curr->prev = currAux;

                currAux->next->prev = curr;
                currAux->next = curr;

                currAux = curr;

            }
            curr = currNext;
            currNext = currNext->next;
        }
        else {
            curr = curr->next;
            currNext = currNext->next;
        }
    }

}


void tratar_caso() {
    // Escribe aquí el código para leer de la entrada
    // un caso de prueba y procesarlo.
  
    int elem;
    ListLinkedDouble lista, aux;
    cin >> elem;
        while (elem != 0) {
            lista.push_back(elem);
            cin >> elem;
        }

        cin >> elem;
        while (elem != 0) {
            aux.push_back(elem);
            cin >> elem;
        }

        lista.desparizar(aux);
        lista.display();
        cout << "\n";
        aux.display();
        cout << "\n";

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
    int num_casos;
    cin >> num_casos;


    // Llamamos tantas veces a `tratar_caso` como nos diga el número.
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

    // Comenta esto también si has comentado lo anterior.   
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
