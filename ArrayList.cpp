#include "ArrayList.h"
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

template <typename T>
ArrayList<T>::ArrayList() : capacity(1), length(0), array(new T[1]) {
    srand(time(0));
}

template <typename T>
ArrayList<T>::ArrayList(const char* filename) {
    capacity = 1;
    length = 0;
    array = new T[1];
    srand(time(0));
    std::ifstream file(filename);
    if (file.is_open()) {
        T item;
        while (file >> item) {
            addAtEnd(item);
        }
        file.close();
    }
}


template <typename T>
ArrayList<T>::~ArrayList() {
    delete[] array;
}

template <typename T>
void ArrayList<T>::addAtStart(T item) {
    addAt(0, item);
}

template <typename T>
void ArrayList<T>::addAtRandom(T item) {
    int index = rand() % (length + 1);
    addAt(index, item);
}

template <typename T>
void ArrayList<T>::addAtEnd(T item) {
    if (length == capacity) {
        resize();
    }
    array[length++] = item;
}

template <typename T>
void ArrayList<T>::removeAtStart() {
    removeAt(0);
}

template <typename T>
void ArrayList<T>::removeAtRandom() {
    if (length == 0) {
        throw std::out_of_range("Cannot remove from empty list");
    }
    int index = rand() % length;
    removeAt(index);
}

template <typename T>
void ArrayList<T>::removeAtEnd() {
    if (length == 0) {
        throw std::out_of_range("Cannot remove from empty list");
    }
    --length;
}

template <typename T>
int ArrayList<T>::find(T item) {
    for (int i = 0; i < length; ++i) {
        if (array[i] == item) {
            return i;
        }
    }
    return -1;
}

template <typename T>
T ArrayList<T>::get(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

template <typename T>
int ArrayList<T>::size() {
    return length;
}

template <typename T>
void ArrayList<T>::resize() {
    T* newArray = new T[capacity * 2];
    for (int i = 0; i < length; ++i) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity *= 2;
}

template <typename T>
void ArrayList<T>::addAt(int index, T item) {
    if (index < 0 || index > length) {
        throw std::out_of_range("Index out of range");
    }
    if (length == capacity) {
        resize();
    }
    for (int i = length; i > index; --i) {
        array[i] = array[i - 1];
    }
    array[index] = item;
    ++length;
}

template <typename T>
void ArrayList<T>::removeAt(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    for (int i = index; i < length - 1; ++i) {
        array[i] = array[i + 1];
    }
    --length;
}

template <typename T>
void ArrayList<T>::print() {
    std::cout << "List: ";
    for (int i = 0; i < length; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template class ArrayList<int>;