#include "SinglyLinkedHeadTailList.h"
#include <cstdlib>
#include <fstream>

template <typename T>
SinglyLinkedHeadTailList<T>::SinglyLinkedHeadTailList() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
SinglyLinkedHeadTailList<T>::SinglyLinkedHeadTailList(const char* filename) : head(nullptr), tail(nullptr), length(0) {
    std::ifstream file(filename);
    T data;
    while (file >> data) {
        addAtEnd(data);
    }
}

template <typename T>
SinglyLinkedHeadTailList<T>::~SinglyLinkedHeadTailList() {
    while (head != nullptr) {
        Node<T>* next = head->next;
        delete head;
        head = next;
    }
}

template <typename T>
void SinglyLinkedHeadTailList<T>::addAtStart(T data) {
    Node<T>* newNode = new Node<T>{data, head};
    head = newNode;
    if (length == 0) {
        tail = head;
    }
    length++;
}

template <typename T>
void SinglyLinkedHeadTailList<T>::addAtRandom(T data) {
    if (head == nullptr) {
        addAtStart(data);
    } else {
        int randomIndex = rand() % (length + 1);
        if (randomIndex == 0) {
            addAtStart(data);
        } else if (randomIndex == length) {
            addAtEnd(data);
        } else {
            Node<T>* current = head;
            for (int i = 0; i < randomIndex - 1; i++) {
                current = current->next;
            }
            Node<T>* newNode = new Node<T>{data, current->next};
            current->next = newNode;
            length++;
        }
    }
}

template <typename T>
void SinglyLinkedHeadTailList<T>::addAtEnd(T data) {
    Node<T>* newNode = new Node<T>{data, nullptr};
    if (length == 0) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    length++;
}

template <typename T>
void SinglyLinkedHeadTailList<T>::removeAtStart() {
    if (length == 0) return;
    Node<T>* nodeToDelete = head;
    head = head->next;
    delete nodeToDelete;
    length--;
    if (length == 0) {
        tail = nullptr;
    }
}

template <typename T>
void SinglyLinkedHeadTailList<T>::removeAtRandom() {
    if (length == 0) return;
    if (length == 1) {
        removeAtStart();
    } else {
        int randomIndex = rand() % length;
        if (randomIndex == 0) {
            removeAtStart();
        } else if (randomIndex == length - 1) {
            removeAtEnd();
        } else {
            Node<T>* current = head;
            for (int i = 0; i < randomIndex - 1; i++) {
                current = current->next;
            }
            Node<T>* nodeToDelete = current->next;
            current->next = nodeToDelete->next;
            delete nodeToDelete;
            length--;
        }
    }
}

template <typename T>
void SinglyLinkedHeadTailList<T>::removeAtEnd() {
    if (length == 0) return;
    if (length == 1) {
        delete head;
        head = tail = nullptr;
    } else {
        Node<T>* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    length--;
}

template <typename T>
int SinglyLinkedHeadTailList<T>::find(T data) {
    Node<T>* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == data) return index;
        current = current->next;
        index++;
    }
    return -1;  // Not found
}

template <typename T>
T SinglyLinkedHeadTailList<T>::get(int index) {
    if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
int SinglyLinkedHeadTailList<T>::size() {
    return length;
}

template <typename T>
void SinglyLinkedHeadTailList<T>::print() {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SinglyLinkedHeadTailList<T>::removeAt(int index) {
    if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
    if (index == 0) {
        removeAtStart();
    } else if (index == length - 1) {
        removeAtEnd();
    } else {
        Node<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node<T>* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
        length--;
    }
}

template class SinglyLinkedHeadTailList<int>;