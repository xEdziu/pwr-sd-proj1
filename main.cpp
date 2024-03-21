#include <cstdlib>
#include <ncurses.h>
#include <menu.h>
#include <filesystem>
#include <cstring>
#include <string>
#include <vector>
#include "ArrayList.h"
#include "SinglyLinkedHeadList.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// Używamy namespace std::filesystem dla krótszego zapisu
namespace fs = std::filesystem;

ArrayList<int> *arrayList = nullptr;
SinglyLinkedHeadList<int> *singlyLinkedHeadList = nullptr;

std::vector<std::string> txtFilesInDirectory() {
    std::vector<std::string> files;
    for (const auto & entry : fs::directory_iterator(".")) {
        if (entry.path().extension() == ".txt") {
            files.push_back(entry.path().filename());
        }
    }
    return files;
}

void printIntro() {
    // Print ASCII art and project info
    mvprintw(0, 0, " _____  _    _  _____ ");
    mvprintw(1, 0, "|  __ \\| |  | ||  __ \\");
    mvprintw(2, 0, "| |__) | |/\\| || |__) |");
    mvprintw(3, 0, "|  ___/|      ||  _  / ");
    mvprintw(4, 0, "| |    |  /\\  || | \\ \\ ");
    mvprintw(5, 0, "|_|    |_/  \\_||_|  \\_\\");
    mvprintw(6, 0, "Project 1 - Data Structures | Adrian Goral 272545 | Paulina Szulc 272592");
}

void displaySubChoices(const char *choice, MENU *main_menu) {
    const char *subChoices[] = {
        "Create Empty Structure",
        "Build from file",
        "Add element at start",
        "Add element at end",
        "Add element at random position",
        "Remove element from start",
        "Remove element from end",
        "Remove element from random position",
        "Find element",
        "Get element from index",
        "Print list",
        "Exit"
    };

    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices = ARRAY_SIZE(subChoices);
    ITEM *cur_item;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    int startx = 0;
    int starty = 8;

    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for(int i = 0; i < n_choices; ++i) {
        my_items[i] = new_item(subChoices[i], "");
    }
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "F1 to Exit, ESC to go back to main menu");
    set_menu_mark(my_menu, " * ");
    set_menu_win(my_menu, stdscr);
    set_menu_sub(my_menu, derwin(stdscr, n_choices + 1, 40, starty, startx));
    post_menu(my_menu);
    refresh();

    bool leave = false;

    while((c = getch()) != KEY_F(1) && !leave) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: /* Enter */
                cur_item = current_item(my_menu);
                if (strcmp(item_name(cur_item), "Print list") == 0) {
                    clear();
                    //check which structure is selected
                    if (strcmp(choice, "Array List") == 0) {

                        mvprintw(0, 0, "Press any key to return to main menu");
                        mvprintw(1, 0, "Array List: ");
                        for (int i = 0; i < arrayList->size(); ++i) {+
                            mvprintw(i+2, 0, "%d", arrayList->get(i));
                        }
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        
                        mvprintw(0, 0, "Press any key to return to main menu");
                        mvprintw(1, 0, "Singly Linked List - Head: ");
                        for (int i = 0; i < singlyLinkedHeadList->size(); ++i) {
                            mvprintw(i+2, 0, "%d", singlyLinkedHeadList->get(i));
                        }

                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //print singly linked list
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //print doubly linked list
                    }
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Exit") == 0) {
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Create Empty Structure") == 0) {
                    clear();
                    mvprintw(0, 0, "Press any key to return to main menu");
                    if (strcmp(choice, "Array List") == 0) {
                        arrayList = new ArrayList<int>();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        singlyLinkedHeadList = new SinglyLinkedHeadList<int>();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //create singly linked list
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //create doubly linked list
                    }
                    mvprintw(1, 0, "Empty structure created");
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Build from file") == 0) {
                    clear();
                    mvprintw(0, 0, "Build from file");
                    std::vector<std::string> files = txtFilesInDirectory();
                    for (int i = 0; i < files.size(); ++i) {
                        mvprintw(i+1, 0, "%d: %s",i+1, files[i].c_str());
                    }
                    //ask for number of file
                    echo();
                    mvprintw(files.size()+1, 0, "Enter number of file: ");
                    int fileNumber;
                    scanw("%d", &fileNumber);
                    noecho();
                    //check which structure is selected
                    if (strcmp(choice, "Array List") == 0) {
                        //build array list from file
                        arrayList = new ArrayList<int>(files[fileNumber - 1].c_str());
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        singlyLinkedHeadList = new SinglyLinkedHeadList<int>(files[fileNumber - 1].c_str());
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //build singly linked list from file
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //build doubly linked list from file
                    }
                    mvprintw(files.size()+3, 0, "Structure built from file");
                    mvprintw(files.size()+4, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Add element at start") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter integer element to add: ");
                    scanw("%d", &element);
                    noecho();
                    //check which structure is selected
                    if (strcmp(choice, "Array List") == 0) {
                        //add element at start
                        arrayList->addAtStart(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //add element at start
                        singlyLinkedHeadList->addAtStart(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //add element at start
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //add element at start
                    }
                    
                    mvprintw(0, 0, "Element added at start");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Add element at end") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter element to add: ");
                    scanw("%d", &element);
                    noecho();

                    if (strcmp(choice, "Array List") == 0) {
                        //add element at end
                        arrayList->addAtEnd(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //add element at end
                        singlyLinkedHeadList->addAtEnd(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //add element at end
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //add element at end
                    }

                    mvprintw(0, 0, "Element added at end");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Add element at random position") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter element to add: ");
                    scanw("%d", &element);
                    noecho();
                    
                    if (strcmp(choice, "Array List") == 0) {
                        //add element at random position
                        arrayList->addAtRandom(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //add element at random position
                        singlyLinkedHeadList->addAtRandom(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //add element at random position
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //add element at random position
                    }

                    mvprintw(0, 0, "Element added at random position");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Remove element from start") == 0) {
                    clear();
                    if (strcmp(choice, "Array List") == 0) {
                        //remove element from start
                        arrayList->removeAtStart();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //remove element from start
                        singlyLinkedHeadList->removeAtStart();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //remove element from start
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //remove element from start
                    }

                    mvprintw(0, 0, "Element removed from start");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Remove element from end") == 0) {
                    clear();
                    if (strcmp(choice, "Array List") == 0) {
                        //remove element from end
                        arrayList->removeAtEnd();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //remove element from end
                        arrayList->removeAtEnd();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //remove element from end
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //remove element from end
                    }

                    mvprintw(0, 0, "Element removed from end");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                }
                else if (strcmp(item_name(cur_item), "Remove element from random position") == 0) {
                    clear();
                    
                    if (strcmp(choice, "Array List") == 0) {
                        //remove element from random position
                        arrayList->removeAtRandom();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //remove element from random position
                        singlyLinkedHeadList->removeAtRandom();
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //remove element from random position
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //remove element from random position
                    }

                    mvprintw(0, 0, "Element removed from random position");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;

                }
                else if (strcmp(item_name(cur_item), "Find element") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter element to find: ");
                    scanw("%d", &element);
                    noecho();
                    int index = -1;

                    if (strcmp(choice, "Array List") == 0) {
                        //find element
                        index = arrayList->find(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //find element
                        index = singlyLinkedHeadList->find(element);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //find element
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //find element
                    }


                    if (index != -1) {
                        mvprintw(1, 0, "Element found at index: %d", index);
                    }
                    else {
                        mvprintw(1, 0, "Element not found");
                    }

                    mvprintw(2, 0, "Press any key to return to main menu");
                    leave = true;
                    break;

                }
                else if (strcmp(item_name(cur_item), "Get element from index") == 0) {
                    clear();
                    int index;
                    echo();
                    mvprintw(0, 0, "Enter index: ");
                    scanw("%d", &index);
                    noecho();
                    int element;
                    
                    if (strcmp(choice, "Array List") == 0) {
                        //get element from index
                        element = arrayList->get(index);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head") == 0) {
                        //get element from index
                        element = singlyLinkedHeadList->get(index);
                    }
                    else if (strcmp(choice, "Singly Linked List - Head & Tail") == 0) {
                        //get element from index
                    }
                    else if (strcmp(choice, "Doubly Linked List") == 0) {
                        //get element from index
                    }

                    mvprintw(1, 0, "Element at index %d: %d", index, element);

                    mvprintw(2, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                }
                break;
            case 27: /* ESC */
                leave = true;
                break;
            if (!leave) {
                // Jeśli nie opuszczamy, odśwież menu
                refresh();
            }
        }
    }
    // Przed opuszczeniem funkcji:
    unpost_menu(my_menu);  // Odpięcie menu
    for(int i = 0; i < n_choices; ++i) {
        free_item(my_items[i]);  // Zwolnienie pamięci zajmowanej przez elementy
    }
    free_menu(my_menu);  // Zwolnienie pamięci zajmowanej przez menu
    
    clear();
    printIntro();
    post_menu(main_menu);  // Ponowne postawienie menu
    mvprintw(LINES - 2, 0, "F1 to Exit");
    refresh();  // Odświeżenie ekranu
}

int main() {

    const char *choices[] = {
        "Array List",
        "Singly Linked List - Head",
        "Singly Linked List - Head & Tail",
        "Doubly Linked List"
    };

    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices = ARRAY_SIZE(choices);
    ITEM *cur_item;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    int startx = 0;
    int starty = 8;

    printIntro();

    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for(int i = 0; i < n_choices; ++i) {
        my_items[i] = new_item(choices[i], "");
    }
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "F1 to Exit");
    set_menu_mark(my_menu, " * ");
    set_menu_win(my_menu, stdscr);
    set_menu_sub(my_menu, derwin(stdscr, n_choices + 1, 40, starty, startx));
    post_menu(my_menu);
    refresh();

    while((c = getch()) != KEY_F(1)) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: /* Enter */
            { 
                ITEM *cur_item = current_item(my_menu);
                unpost_menu(my_menu);  // Odpięcie menu przed przejściem do sub-menu
                clear();  // Wyczyszczenie ekranu przed przejściem do sub-menu
                printIntro();
                displaySubChoices(item_name(cur_item), my_menu);  // Wyświetlenie sub-menu
                break;
            }
        }
    }

    unpost_menu(my_menu);  // Odpięcie menu
    for(int i = 0; i < n_choices; ++i) {
        free_item(my_items[i]);  // Zwolnienie pamięci zajmowanej przez elementy
    }
    free_menu(my_menu);  // Zwolnienie pamięci zajmowanej przez menu
    endwin();
    
    return 0;
}