// SinglyLinkedHeadList.cpp
#include "SinglyLinkedHeadList.h"
#include <cstdlib>
#include <fstream>

template <typename T>
SinglyLinkedHeadList<T>::SinglyLinkedHeadList() : head(NULL), length(0) {}

template <typename T>
SinglyLinkedHeadList<T>::~SinglyLinkedHeadList() {
    while (head != NULL) {
        Node<T>* next = head->next;
        delete head;
        head = next;
    }
}

template <typename T>
SinglyLinkedHeadList<T>::SinglyLinkedHeadList(const char* filename) : head(NULL), length(0) {
    srand(time(0));
    int lines = 0;
    std::ifstream file(filename);
    if (file.is_open()) {
        T item;
        while (file >> item) {
            addAtEnd(item);
            lines++;
        }
        file.close();
    }
    length = lines;
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
    if (head != NULL) {
        Node<T>* toDelete = head;
        head = head->next;
        delete toDelete;
        length--;
    }
}

template <typename T>
void SinglyLinkedHeadList<T>::addAtRandom(T data) {
    if (head == NULL) {
        addAtStart(data);
    } else {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->next = NULL;
        Node<T>* current = head;
        int position = rand() % (length + 1);
        for (int i = 0; i < position - 1 && current != NULL; i++) {
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
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    length++;
}

template <typename T>
void SinglyLinkedHeadList<T>::removeAtRandom() {
    if (head == NULL) {
        return;
    } else if (head->next == NULL) {
        delete head;
        head = NULL;
    } else {
        Node<T>* current = head;
        int position = rand() % length;
        for (int i = 0; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        Node<T>* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
    }
    length--;
}

template <typename T>
void SinglyLinkedHeadList<T>::removeAtEnd() {
    if (head == NULL) {
        return;
    } else if (head->next == NULL) {
        delete head;
        head = NULL;
    } else {
        Node<T>* current = head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        delete current->next;
        current->next = NULL;
    }
    length--;
}

template <typename T>
int SinglyLinkedHeadList<T>::find(T data) {
    Node<T>* current = head;
    int index = 0;
    while (current != NULL) {
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
    while (current != NULL) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template class SinglyLinkedHeadList<int>;