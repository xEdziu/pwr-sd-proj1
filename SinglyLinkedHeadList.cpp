// SinglyLinkedHeadList.cpp
#include "SinglyLinkedHeadList.h"
#include <cstdlib>
#include <fstream>

template <typename T>
SinglyLinkedHeadList<T>::SinglyLinkedHeadList() : head(nullptr), length(0) {}

template <typename T>
SinglyLinkedHeadList<T>::~SinglyLinkedHeadList() {
    while (head != nullptr) {
        Node<T>* next = head->next;
        delete head;
        head = next;
    }
}

template <typename T>
SinglyLinkedHeadList<T>::SinglyLinkedHeadList(const char* filename) : head(nullptr), length(0) {
    std::ifstream file(filename);
    if (file.is_open()) {
        T item;
        Node<T>* last = nullptr; // Tymczasowy wskaźnik na ostatni element
        while (file >> item) {
            Node<T>* newNode = new Node<T>{item, nullptr};
            if (last == nullptr) { // Lista jest pusta
                head = newNode;
                last = newNode; // Teraz last wskazuje na pierwszy (i jedyny) element
            } else {
                last->next = newNode; // Dodaj nowy węzeł na końcu listy
                last = newNode; // Aktualizacja wskaźnika na ostatni element
            }
            length++;
        }
    }
}


template <typename T>
void SinglyLinkedHeadList<T>::addAtStart(T data) {
    Node<T>* newNode = new Node<T>;
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    length++;
}

template <typename T>
void SinglyLinkedHeadList<T>::removeAtStart() {
    if (head != nullptr) {
        Node<T>* toDelete = head;
        head = head->next;
        delete toDelete;
        length--;
    }
}

template <typename T>
void SinglyLinkedHeadList<T>::addAtRandom(T data) {
    if (head == nullptr) {
        addAtStart(data);
    } else {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->next = nullptr;
        Node<T>* current = head;
        int position = rand() % (length + 1);
        for (int i = 0; i < position - 1 && current != nullptr; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        length++;
    }
}

template <typename T>
void SinglyLinkedHeadList<T>::addAtEnd(T data) {
    Node<T>* newNode = new Node<T>;
    newNode->data = data;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    length++;
}

template <typename T>
void SinglyLinkedHeadList<T>::removeAtRandom() {
    if (head == nullptr) {
        return; // Lista jest pusta, nie ma co usuwać
    } else if (head->next == nullptr) {
        // Lista ma tylko jeden element, więc usuwamy głowę
        delete head;
        head = nullptr;
    } else {
        int position = rand() % length; // Losowanie pozycji od 0 do length - 1
        if (position == 0) {
            // Usuwanie pierwszego elementu
            Node<T>* toDelete = head;
            head = head->next;
            delete toDelete;
        } else {
            // Usuwanie elementu niebędącego pierwszym w liście
            Node<T>* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next; // Przesuwamy
            }
            Node<T>* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
        }
        length--;
    }
}

template <typename T>
void SinglyLinkedHeadList<T>::removeAtEnd() {
    if (head == nullptr) {
        return;
    } else if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node<T>* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    length--;
}

template <typename T>
int SinglyLinkedHeadList<T>::find(T data) {
    Node<T>* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
T SinglyLinkedHeadList<T>::get(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
int SinglyLinkedHeadList<T>::size() {
    return length;
}

template <typename T>
void SinglyLinkedHeadList<T>::print() {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SinglyLinkedHeadList<T>::removeAt(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
        removeAtStart();
    } else {
        Node<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node<T>* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        length--;
    }
}

template class SinglyLinkedHeadList<int>;