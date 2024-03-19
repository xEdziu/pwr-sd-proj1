#include <iostream>
#include "ArrayList.h"



int main() {
    ArrayList<int> list;

    list.addAtStart(1);
    list.print();
    list.addAtEnd(2);
    list.print();
    list.addAtRandom(3);
    list.print();
    list.addAtStart(4);
    list.addAtEnd(5);
    list.addAtRandom(6);


    list.print();

    std::cout << std::endl;

    list.removeAtStart();
    list.print();
    list.removeAtEnd();
    
    list.removeAtRandom();

    list.print();

    std::cout << std::endl;

    std::cout << "Index of 3: " << list.find(3) << std::endl;
    std::cout << "Get at index 1: " << list.get(1) << std::endl;

    std::cout << "List size: " << list.size() << std::endl;

    return 0;
}