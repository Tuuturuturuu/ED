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
    Componente 1: Sof�a Postigo Ruiz
    Componente 2:
  */
  //@ </answer>

#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <ctype.h>


/*
  Implementaci�n de listas enlazadas simples vista en clase.

  https://github.com/manuelmontenegro/ED/tree/main/lineales/list_linked_single_v2

  En este caso, los valores contenidos en los nodos no son de tipo entero,
  sino de tipo char, porque es lo que requiere el ejercicio. En la Semana 4
  veremos c�mo hacer que una misma implementaci�n del TAD Lista pueda
  aplicarse a distintos tipos de elementos (int, char, string, etc.)
*/
class ListLinkedSingle {
private:
    struct Node {
        char value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }

    // Nuevo constructor. Se implementar� fuera de la clase.
    // Mira m�s abajo para ver d�nde tienes que implementarlo.
    ListLinkedSingle(const std::string& text);

    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const char& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const char& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const char& front() const {
        assert(head != nullptr);
        return head->value;
    }

    char& front() {
        assert(head != nullptr);
        return head->value;
    }

    const char& back() const {
        return last_node()->value;
    }

    char& back() {
        return last_node()->value;
    }

    const char& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    char& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // M�todo `destripar`. Se implementar� fuera de la clase.
    // Mira m�s abajo para ver d�nde tienes que implementarlo.
    void destripar(ListLinkedSingle& dest);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const char& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------

// Implementa el constructor y el m�todo pedidos. Indica y justifica el coste
// antes de cada implementaci�n, mediante un comentario.
// 

//O(N) siendo N el numero de caracteres del string "text"
ListLinkedSingle::ListLinkedSingle(const std::string& text) {
    this->head = nullptr;
    for (int i = text.size() - 1; i >= 0; i--) {
        this->push_front(text[i]); //O(1) constante
    }
}

/*
*
Este ejercicio/ metodo ser�a mucho mas sencillo trabajando con una lista
doblemente enlazada, en lugar de con unaenlazada simple

El metodo destripar tiene una complejidad de
O(N) siendo N el numero de elementos de la lista this (al ser todos O(N)
el coste final del metodo tambien lo ser�)

*/
void ListLinkedSingle::destripar(ListLinkedSingle& dest) {
    Node* curr = head;
    Node* other = dest.head;
    Node* lastLetter = curr;

    if (head != nullptr) {
        
        //quitar nums principio de this
        while (curr != nullptr && !isalpha(curr->value)) {
            head = head->next;
            lastLetter = head;
            curr->next = nullptr;

            if (dest.head != nullptr)
                other->next = curr;

            other = curr;
            curr = head;

            if (dest.head == nullptr) {
                dest.head = other;
            }
        }

        //avanzar buscando la ultima letra
        while (head != nullptr && curr->next != nullptr) {
            if (isalpha(curr->value)) {
                lastLetter = curr;
            }
            curr = curr->next;
        }

        if (curr !=nullptr && isalpha(curr->value)){
            lastLetter = curr;
        }


        //quitar nums a partir de la ultima letra apuntada por lastLetter
        if (head != nullptr) {
            curr = lastLetter->next;

            if (curr != nullptr) {

                if (curr->next != nullptr || (lastLetter->next == curr && !isalpha(curr->value))) {

                    lastLetter->next = nullptr;

                    if (dest.head != nullptr)
                        other->next = curr;
                    else
                        dest.head = curr;
                }
            }
        }
    }
}

using namespace std;

// Implementa aqu� la funci�n para tratar UN caso de prueba. La funci�n `main`
// llamar� a esta funci�n `tratar_caso` tantas veces como casos de prueba hay
// en la entrada.

void tratar_caso() {
    string text;
    cin >> text;
    ListLinkedSingle ls(text);
    ListLinkedSingle dest;

    ls.destripar(dest);
    ls.display();
    cout << endl;
    dest.display();
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
