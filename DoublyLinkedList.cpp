#include "DoublyLinkedList.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(NULL), tail(NULL), length(0) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const char* filename) : head(NULL), tail(NULL), length(0) {
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
    while (head != NULL) {
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
    newNodeDoubleList->prev = NULL;
    if (head != NULL) {
        head->prev = newNodeDoubleList;
    }
    head = newNodeDoubleList;
    if (tail == NULL) {
        tail = head;
    }
    length++;
}

template <typename T>
void DoublyLinkedList<T>::addAtRandom(T data) {
    if (head == NULL) {
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
    newNodeDoubleList->next = NULL;
    newNodeDoubleList->prev = tail;
    if (tail != NULL) {
        tail->next = newNodeDoubleList;
    }
    tail = newNodeDoubleList;
    if (head == NULL) {
        head = tail;
    }
    length++;
}

template <typename T>
void DoublyLinkedList<T>::removeAtStart() {
    if (head != NULL) {
        NodeDoubleList<T>* toDelete = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete toDelete;
        length--;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeAtRandom() {
    if (head != NULL) {
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
    if (tail != NULL) {
        NodeDoubleList<T>* toDelete = tail;
        tail = tail->prev;
        if (tail != NULL) {
            tail->next = NULL;
        }
        delete toDelete;
        length--;
    }
}

template <typename T>
int DoublyLinkedList<T>::find(T data) {
    NodeDoubleList<T>* current = head;
    int position = 0;
    while (current != NULL) {
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
    while (current != NULL) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template class DoublyLinkedList<int>;