// SinglyLinkedHeadList.h
#ifndef SINGLYLINKEDHEADLIST_H
#define SINGLYLINKEDHEADLIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class SinglyLinkedHeadList {
private:
    Node<T>* head;
    int length;
public:

    /*
        * Default constructor
        * Initializes the head and length
        * @param none
        * @return none
    */
    SinglyLinkedHeadList();

    /*
        * Destructor
        * Deallocates memory for the list
        * @param none
        * @return none
    */
    ~SinglyLinkedHeadList();

    /*
        * Adds an item at the start of the list
        * @param data - the item to be added
        * @return none
    */
    void addAtStart(T data);

    /*
        * Removes an item from the start of the list
        * @param none
        * @return none
    */
    void removeAtStart();

    /*
        * Adds an item at a random position in the list
        * @param data - the item to be added
        * @return none
    */
    void addAtRandom(T data);

    /*
        * Adds an item at the end of the list
        * @param data - the item to be added
        * @return none
    */
    void addAtEnd(T data);

    /*
        * Removes an item from a random position in the list
        * @param none
        * @return none
    */
    void removeAtRandom();

    /*
        * Removes an item from the end of the list
        * @param none
        * @return none
    */
    void removeAtEnd();

    /*
        * Returns the size of the list
        * @param none
        * @return the size of the list
    */
    int size();

    /*
        * Prints the list
        * @param none
        * @return none
    */
    void print();
};

#endif // SINGLYLINKEDHEADLIST_H