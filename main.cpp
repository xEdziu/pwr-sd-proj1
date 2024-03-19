#include <iostream>
#include "ArrayList.h"

int main() {
    ArrayList<int> list;

    list.addAtStart(1);
    list.addAtEnd(2);
    list.addAtRandom(3);
    list.addAtStart(4);
    list.addAtEnd(5);
    list.addAtRandom(6);


    std::cout << "List: ";
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list.get(i) << " ";
    }

    std::cout << std::endl;

    list.removeAtStart();
    list.removeAtEnd();
    list.removeAtRandom();

    std::cout << "List: ";
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list.get(i) << " ";
    }

    std::cout << std::endl;

    std::cout << "Index of 3: " << list.find(3) << std::endl;
    std::cout << "Get at index 1: " << list.get(1) << std::endl;

    std::cout << "List size: " << list.size() << std::endl;

    return 0;
}