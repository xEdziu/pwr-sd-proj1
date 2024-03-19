#include <iostream>
#include "ArrayList.h"

void printList(ArrayList<int>& list) {
    std::cout << "List: ";
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    ArrayList<int> list;

    list.addAtStart(1);
    printList(list);
    list.addAtEnd(2);
    printList(list);
    list.addAtRandom(3);
    printList(list);
    list.addAtStart(4);
    list.addAtEnd(5);
    list.addAtRandom(6);


    printList(list);

    std::cout << std::endl;

    list.removeAtStart();
    printList(list);
    list.removeAtEnd();
    
    list.removeAtRandom();

    printList(list);

    std::cout << std::endl;

    std::cout << "Index of 3: " << list.find(3) << std::endl;
    std::cout << "Get at index 1: " << list.get(1) << std::endl;

    std::cout << "List size: " << list.size() << std::endl;

    return 0;
}