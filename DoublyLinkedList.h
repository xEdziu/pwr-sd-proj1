#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <typename T>
struct NodeDoubleList {
    T data;
    NodeDoubleList* next;
    NodeDoubleList* prev;
};

template <typename T>
class DoublyLinkedList {
private:
    NodeDoubleList<T>* head;
    NodeDoubleList<T>* tail;
    int length;

public:

    /*
        * Default constructor
        * Initializes the head, tail and length
        * @param none
        * @return none
    */
    DoublyLinkedList();

    /*
        * Constructor
        * Initializes the head, tail, length and builds the list from a file
        * @param filename - the file from which the list is to be built
        * @return none
    */
    DoublyLinkedList(const char* filename);

    /*
        * Destructor
        * Deallocates memory for the list
        * @param none
        * @return none
    */
    ~DoublyLinkedList();

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
        * Removes an item at the start of the list
        * @param none
        * @return none
    */
    void removeAtStart();

    /*
        * Removes an item at a random position in the list
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
        * @return the index of the item in the list
    */
    int find(T data);

    /*
        * Gets an item from the list
        * @param index - the index of the item to be retrieved
        * @return the item at the index
    */
    T get(int index);

    /*
        * Gets the size of the list
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

        /*
        * Removes an item at a specific index
        * @param index - the index of the item to be removed
        * @return none
    */
    void removeAt(int index);
};

#endif