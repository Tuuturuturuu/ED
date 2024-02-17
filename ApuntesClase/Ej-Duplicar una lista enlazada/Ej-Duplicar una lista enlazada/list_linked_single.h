/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementación del TAD Lista mediante listas enlazadas simples.
  *
  * Versión inicial.
  */

#ifndef __LIST_LINKED_SINGLE_H
#define __LIST_LINKED_SINGLE_H

#include <cassert>
#include <iostream>
#include <string>

class ListLinkedSingle {
private:
    struct Node {
        std::string value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    void push_front(const std::string& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const std::string& elem);
    void duplicate();
    void invert();
    void merge(ListLinkedSingle other);

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

    const std::string& front() const {
        assert(head != nullptr);
        return head->value;
    }

    std::string& front() {
        assert(head != nullptr);
        return head->value;
    }

    const std::string& back() const {
        return last_node()->value;
    }

    std::string& back() {
        return last_node()->value;
    }

    const std::string& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    std::string& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;

};

//O(N) siendo N el  numero de elementos de la lista
void ListLinkedSingle::duplicate() {
    Node* curr = head;
    Node* next = curr->next;
    while (curr->next != nullptr) {
        
        Node* new_node = new Node{};
        new_node->value = curr->value;
        curr->next = new_node;
        new_node->next = next;
        curr = next;
        next = next->next;
    }
    Node* newLastNode = new Node{};
    newLastNode->value = curr->value;
    curr->next = newLastNode;
    newLastNode->next = nullptr;
}

//O(N) siendo N el  numero de elementos de la lista
void ListLinkedSingle::invert() {
    Node* prev = head;
    Node* curr = prev->next;
    Node* next = curr->next;
    while (curr->next != nullptr) {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }
    curr->next = prev;
    head->next = nullptr;
    head = curr;
}

//O(N) siendo N el  numero de elementos de la lista
void ListLinkedSingle::merge(ListLinkedSingle o) {
    Node* other = o.head;
    Node* curr = head;
    Node* next = curr->next;

    while (curr != nullptr && other != nullptr) {
        if (curr->value <= other->value) {
            curr->next = other;
            curr = next;
            next = next->next;
        }
        else {
            next = curr;
            curr = other;
            other = other->next;
            curr->next = next;
            curr = next;
            next = next->next;
        }
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const std::string& elem) {
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


#endif