#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cstdlib>
#include <ctime>

template <typename T>
class ArrayList {
public:
    
    /*
        * Default constructor
        * Initializes the capacity, length and allocates memory for the array
        * @param none
        * @return none
    */
    ArrayList();

    /*
        * Destructor
        * Deallocates memory for the array
        * @param none
        * @return none
    */
    ~ArrayList();

    /*
        * Adds an item at the start of the list
        * @param item - the item to be added
        * @return none
    */
    void addAtStart(T item);

    /*
        * Adds an item at a random position in the list
        * @param item - the item to be added
        * @return none
    */
    void addAtRandom(T item);

    /*
        * Adds an item at the end of the list
        * @param item - the item to be added
        * @return none
    */
    void addAtEnd(T item);

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
        * Finds the index of an item in the list
        * @param item - the item to be found
        * @return the index of the item if found, -1 otherwise
    */
    int find(T item);

    /*
        * Gets an item from the list
        * @param index - the index of the item to be retrieved
        * @return the item at the specified index
    */
    T get(int index);

    /*
        * Gets the size of the list
        * @param none
        * @return the size of the list
    */
    int size();

private:
    T* array;
    int capacity;
    int length;

    /*
        * Resizes the array - doubles the capacity
        * @param none
        * @return none
    */
    void resize();

    /*
        * Adds an item at a specified index in the list
        * @param index - the index at which the item is to be added
        * @param item - the item to be added
        * @return none
    */
    void addAt(int index, T item);

    /*
        * Removes an item from a specified index in the list
        * @param index - the index from which the item is to be removed
        * @return none
    */
    void removeAt(int index);
};

#endif // ARRAYLIST_H