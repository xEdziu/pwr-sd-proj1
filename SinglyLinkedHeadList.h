// SinglyLinkedHeadList.h
#ifndef SINGLYLINKEDHEADLIST_H
#define SINGLYLINKEDHEADLIST_H

#include <iostream>
#include "Node.h"

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
        * Constructor
        * Initializes the head and length
        * @param filename - the file from which the list is to be built
        * @return none
    */
    SinglyLinkedHeadList(const char* filename);

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
        * Removes an item from the start of the list
        * @param none
        * @return none
    */
    void removeAtStart();

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
        * Finds an item in the list
        * @param data - the item to be found
        * @return the index of the item
    */
    int find(T data);

    /*
        * Gets an item from the list
        * @param index - the index of the item
        * @return the item at the index
    */
    T get(int index);

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

    
    void removeAt(int index);
};

#endif // SINGLYLINKEDHEADLIST_H