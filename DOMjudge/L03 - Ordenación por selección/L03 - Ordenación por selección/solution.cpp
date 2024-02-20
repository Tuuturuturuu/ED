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
    Componente 1:Sofia Postigo Ruiz
    Componente 2:Sergio Tarancon Martinez
  */
  //@ </answer>

#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 


/*
  Implementaci�n de listas doblemente enlazadas circulares

  https://github.com/manuelmontenegro/ED/blob/main/lineales/list_linked_double_v4/list_linked_double.h

*/

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

    // Implementa este m�todo m�s abajo
    void sort_and_dedup();

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);

    // M�todos privados. Implem�ntalos m�s abajo
    Node* minimum(Node* begin, Node* end) const;
    void detach(Node* n);
    void attach(Node* n, Node* position);
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

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------

//O(N) siendo N el numero de elementos comprendidos entre begin y end, en el peor de los casos siendo N num_elems
ListLinkedDouble::Node* ListLinkedDouble::minimum(Node* begin, Node* end) const {
    Node* curr = begin;
    Node* min = curr;
    while (curr != end->next) {
        if (curr->value < min->value) {
            min = curr;
        }
        curr = curr->next;
    }
    return min;
}

//O(1)
void ListLinkedDouble::detach(Node* n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    n->next = n;
    n->prev = n;
    num_elems--;
}
//O(1)
void ListLinkedDouble::attach(Node* n, Node* position) {
    n->next = position;
    n->prev = position->prev;
    position->prev->next = n;
    position->prev = n;
    num_elems++;
}

//O(N^2) siendo N el  numero de elementos de la lista
void ListLinkedDouble::sort_and_dedup() {
    if(head->next!= head){ 
        Node* lastMin = head;
        while (lastMin != head->prev) {//O(N)
            Node* min = minimum(lastMin->next, head->prev);//O(N)
            detach(min);
            if (min->value != lastMin->value || lastMin == head) {
                attach(min, lastMin->next);
                lastMin = lastMin->next;
            }
        }
    }
}

using namespace std;

// Implementa aqu� la funci�n para tratar UN caso de prueba. La funci�n `main`
// llamar� a esta funci�n `tratar_caso` tantas veces como casos de prueba hay
// en la entrada.

//O(N) siendo N el numero de elementos de la lista
void tratar_caso() {
    ListLinkedDouble list;
    long long  int elem;
    bool fin = false;
    while (!fin) {
        cin >> elem;
        if (elem == -1) { fin = true; }
        else {
            list.push_back(elem);
        }
    }
    list.sort_and_dedup();
    list.display();
    cout << endl;
}

//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>


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

    // Llamamos tantas veces a `tratar_caso` como nos diga el n�mero.
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}