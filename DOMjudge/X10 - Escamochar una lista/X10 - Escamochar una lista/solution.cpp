// Escamochar una lista
    // --------------------
    // Estructuras de datos

    #include <iostream>
    #include <cassert>
    #include <fstream>

    using namespace std;

    class ListLinkedSingle {
    private:
        struct Node {
            int value;
            Node* next;
        };

    public:
        ListLinkedSingle() : head(nullptr) { }
        ~ListLinkedSingle() {
            delete_list(head);
        }

        ListLinkedSingle(const ListLinkedSingle& other)
            : head(copy_nodes(other.head)) { }

        void push_front(int elem) {
            Node* new_node = new Node{ elem, head };
            head = new_node;
        }

        void push_back(int elem);

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

        const int& front() const {
            assert(head != nullptr);
            return head->value;
        }

        int& front() {
            assert(head != nullptr);
            return head->value;
        }

        const int& back() const {
            return last_node()->value;
        }

        int& back() {
            return last_node()->value;
        }

        const int& at(int index) const {
            Node* result_node = nth_node(index);
            assert(result_node != nullptr);
            return result_node->value;
        }

        int& at(int index) {
            Node* result_node = nth_node(index);
            assert(result_node != nullptr);
            return result_node->value;
        }


        void display(std::ostream& out) const;
        void display() const {
            display(std::cout);
        }

        // Declaración del método. Impleméntalo antes de la
        // función tratar_caso()
        void escamochar(ListLinkedSingle& dest);

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

    void ListLinkedSingle::push_back(int elem) {
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

//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------


// ¡No olvides indicar el coste del método!
void ListLinkedSingle::escamochar(ListLinkedSingle& dest) {
    if (!this->empty()) {
        Node* curr = this->head;
        Node* lastPositive = nullptr;
        dest.head = nullptr;

        if (this->head->value < 0) {//si el primer elemento es negatico
            dest.head = this->head;
        }
        else {
            lastPositive = this->head;
        }
        Node* lastNeg = dest.head;

        //hasta que encuentra el primer positivo
        while (curr->next != nullptr && curr->value < 0) {
            lastNeg = curr;
            curr = curr->next;
        }

        if (curr->value > 0) {
            lastPositive = curr;
            this->head = curr;
        }

        if (curr->next != nullptr) {
            this->head = curr;
        }

        while (curr->next != nullptr) {
            if (curr->value >= 0) {
                lastPositive = curr;
            }
            curr = curr->next;
        }

        if (lastPositive == nullptr) {
            dest.head = head;
            this->head = nullptr;
        }
        else {
            //si el ultimo elemento es positivo
            if (curr->value >= 0) {
                lastPositive = curr;
            }

            if (lastNeg == nullptr) {
                lastNeg = lastPositive->next;
                dest.head = lastNeg;
            }
            else if (lastPositive != this->head) {
                lastNeg->next = lastPositive->next;
            }
            lastPositive->next = nullptr;
        }
    }
}


void tratar_caso() {
    // Introduce aquí el código para tratar un caso de prueba.

    ListLinkedSingle l1, l2;
    int N, num;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        l1.push_front(num);
    }

    l1.escamochar(l2);
    l1.display();
    cout << "\n";
    l2.display();
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

