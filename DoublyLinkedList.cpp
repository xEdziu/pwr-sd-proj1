#include "DoublyLinkedList.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const char* filename) : head(nullptr), tail(nullptr), length(0) {
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
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head != nullptr) {
        NodeDoubleList<T>* next = head->next;
        delete head;
        head = next;
    }
}

template <typename T>
void DoublyLinkedList<T>::addAtStart(T data) {
    NodeDoubleList<T>* newNodeDoubleList = new NodeDoubleList<T>;
    newNodeDoubleList->data = data;
    newNodeDoubleList->next = head;
    newNodeDoubleList->prev = nullptr;
    if (head != nullptr) {
        head->prev = newNodeDoubleList;
    }
    head = newNodeDoubleList;
    if (tail == nullptr) {
        tail = head;
    }
    length++;
}

template <typename T>
void DoublyLinkedList<T>::addAtRandom(T data) {
    if (head == nullptr) {
        addAtStart(data);
    } else {
        int position = rand() % length;
        if (position == 0) {
            addAtStart(data);
        } else if (position == length - 1) {
            addAtEnd(data);
        } else {
            NodeDoubleList<T>* newNodeDoubleList = new NodeDoubleList<T>;
            newNodeDoubleList->data = data;
            NodeDoubleList<T>* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            newNodeDoubleList->next = current->next;
            newNodeDoubleList->prev = current;
            current->next->prev = newNodeDoubleList;
            current->next = newNodeDoubleList;
            length++;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::addAtEnd(T data) {
    NodeDoubleList<T>* newNodeDoubleList = new NodeDoubleList<T>;
    newNodeDoubleList->data = data;
    newNodeDoubleList->next = nullptr;
    newNodeDoubleList->prev = tail;
    if (tail != nullptr) {
        tail->next = newNodeDoubleList;
    }
    tail = newNodeDoubleList;
    if (head == nullptr) {
        head = tail;
    }
    length++;
}

template <typename T>
void DoublyLinkedList<T>::removeAtStart() {
    if (head != nullptr) {
        NodeDoubleList<T>* toDelete = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete toDelete;
        length--;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeAtRandom() {
    if (head != nullptr) {
        int position = rand() % length;
        if (position == 0) {
            removeAtStart();
        } else if (position == length - 1) {
            removeAtEnd();
        } else {
            NodeDoubleList<T>* current = head;
            for (int i = 0; i < position; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::removeAtEnd() {
    if (tail != nullptr) {
        NodeDoubleList<T>* toDelete = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        delete toDelete;
        length--;
    }
}

template <typename T>
int DoublyLinkedList<T>::find(T data) {
    NodeDoubleList<T>* current = head;
    int position = 0;
    while (current != nullptr) {
        if (current->data == data) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}

template <typename T>
T DoublyLinkedList<T>::get(int position) {
    if (position < 0 || position >= length) {
        return T();
    }
    NodeDoubleList<T>* current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
int DoublyLinkedList<T>::size() {
    return length;
}

template <typename T>
void DoublyLinkedList<T>::print() {
    NodeDoubleList<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::removeAt(int position) {
    if (position < 0 || position >= length) {
        return;
    }
    if (position == 0) {
        removeAtStart();
    } else if (position == length - 1) {
        removeAtEnd();
    } else {
        NodeDoubleList<T>* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        length--;
    }
}

template class DoublyLinkedList<int>;