#include <cstdlib>
#include <ncurses.h>
#include <menu.h>
#include <filesystem>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "ArrayList.h"
#include "SinglyLinkedHeadList.h"
#include "SinglyLinkedHeadTailList.h"
#include "DoublyLinkedList.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// Używamy namespace std::filesystem dla krótszego zapisu
namespace fs = std::filesystem;

ArrayList<int> *arrayList = nullptr;
SinglyLinkedHeadList<int> *singlyLinkedHeadList = nullptr;
SinglyLinkedHeadTailList<int> *singlyLinkedHeadTailList = nullptr;
DoublyLinkedList<int> *doublyLinkedList = nullptr;

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

template<typename Structure>
void displaySubChoices(const char *choice, MENU* main_menu, Structure* &structure) {
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
                    mvprintw(0, 0, "Press any key to return to main menu");
                    for (int i = 0; i < structure->size(); ++i) {
                        mvprintw(i+1, 0, "%d", structure->get(i));
                    }
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Exit") == 0) {
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Create Empty Structure") == 0) {
                    clear();
                    mvprintw(0, 0, "Press any key to return to main menu");
                    structure = new Structure();
                    mvprintw(1, 0, "Empty structure created");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Build from file") == 0) {
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
                    structure = new Structure(files[fileNumber - 1].c_str());
                    mvprintw(files.size()+3, 0, "Structure built from file");
                    mvprintw(files.size()+4, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Add element at start") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter integer element to add: ");
                    scanw("%d", &element);
                    noecho();
                    //check which structure is selected
                    structure->addAtStart(element);
                    mvprintw(0, 0, "Element added at start");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Add element at end") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter element to add: ");
                    scanw("%d", &element);
                    noecho();
                    structure->addAtEnd(element);
                    mvprintw(0, 0, "Element added at end");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Add element at random position") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter element to add: ");
                    scanw("%d", &element);
                    noecho();
                    structure->addAtRandom(element);
                    mvprintw(0, 0, "Element added at random position");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Remove element from start") == 0) {
                    clear();
                    structure->removeAtStart();
                    mvprintw(0, 0, "Element removed from start");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Remove element from end") == 0) {
                    clear();
                    structure->removeAtEnd();
                    mvprintw(0, 0, "Element removed from end");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Remove element from random position") == 0) {
                    clear();
                    structure->removeAtRandom();
                    mvprintw(0, 0, "Element removed from random position");
                    mvprintw(1, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Find element") == 0) {
                    clear();
                    int element;
                    echo();
                    mvprintw(0, 0, "Enter element to find: ");
                    scanw("%d", &element);
                    noecho();
                    int index = structure->find(element);
                    if (index != -1) {
                        mvprintw(1, 0, "Element found at index: %d", index);
                    } else {
                        mvprintw(1, 0, "Element not found");
                    }
                    mvprintw(2, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Get element from index") == 0) {
                    clear();
                    int index;
                    echo();
                    mvprintw(0, 0, "Enter index: ");
                    scanw("%d", &index);
                    noecho();
                    int element = structure->get(index);
                    mvprintw(1, 0, "Element at index %d: %d", index, element);
                    mvprintw(2, 0, "Press any key to return to main menu");
                    leave = true;
                    break;
                } else if (strcmp(item_name(cur_item), "Exit") == 0) {
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

template<typename Structure, typename T>
void testOperation(Structure* &structure, const std::string& operationType, T operationArgument,int removeOperationArgument,
 int findOperationArgument, int iteration, int size,  std::ofstream& output, std::string structureName) {
    clock_t start, end;
    if (operationType == "addAtStart") {
        start = clock();
        structure->addAtStart(operationArgument);
        end = clock();
    } else if (operationType == "addAtEnd") {
        start = clock();
        structure->addAtEnd(operationArgument);
        end = clock();
    } else if (operationType == "addAtRandom") {
        start = clock();
        structure->addAtRandom(operationArgument);
        end = clock();
    } else if (operationType == "removeAtStart") {
        start = clock();
        structure->removeAtStart();
        end = clock();
    } else if (operationType == "removeAtEnd") {
        start = clock();
        structure->removeAtEnd();
        end = clock();
    } else if (operationType == "removeAtRandom") {
        start = clock();
        structure->removeAt(removeOperationArgument);
        end = clock();
    } else if (operationType == "find") {
        start = clock();
        structure->find(findOperationArgument);
        end = clock();
    }

    std::string iterationS = std::to_string(iteration);
    
    double time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    output << iterationS << ";" << structureName << ";" << size << ";" << operationType << ";" << time << "\n";
}

template<typename Structure>
void performTests(std::ofstream& output, std::string structureName,
        int size, const std::string& operation, int toAdd,
        int removeOperationArgument, int findOperationArgument) {
    for (int i = 1; i <= 10; i++) {
        std::string fileName = "list_" + std::to_string(size) + ".txt";
        Structure* structure = new Structure(fileName.c_str());
        testOperation(structure, operation, toAdd, removeOperationArgument,
        findOperationArgument, i, size, output, structureName);
        delete structure;
        std::cout << "Iteration " << i << " - " << operation << " on structure " << structureName << " - " << size << " elements has ended." << std::endl;
    }
}

void testStructures(MENU *main_menu) {
    endwin();
    clock_t start, end;
    std::cout << "Performing structures tests..." << std::endl;
    std::ofstream output("results.csv");
    output << "iteration;type;size;action;timeMs\n";
    int line = 0;

    std::string operations[] = {"addAtStart", "addAtEnd", "addAtRandom", "removeAtStart", "removeAtEnd", "removeAtRandom", "find"};
    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000};

    start = clock();

    for (const std::string& operation : operations) {
        for (int size : sizes) {
            int removeOperationArgument = rand() % size + 1;
            int addOperationArgument = rand() % size + 1;
            int findOperationArgument = rand() % 10000;
            performTests<ArrayList<int>>(output, "ArrayList", size, operation, addOperationArgument, removeOperationArgument, findOperationArgument);
            performTests<SinglyLinkedHeadList<int>>(output, "SinglyLinkedHeadList", size, operation, addOperationArgument, removeOperationArgument, findOperationArgument);
            performTests<SinglyLinkedHeadTailList<int>>(output, "SinglyLinkedHeadTailList", size, operation, addOperationArgument, removeOperationArgument, findOperationArgument);
            performTests<DoublyLinkedList<int>>(output, "DoublyLinkedList", size, operation, addOperationArgument, removeOperationArgument, findOperationArgument); 
        }
    }
       
    end = clock();

    output.close();

    refresh();
    clear();

    mvprintw(line++, 0, "Tests have ended. Results saved to results.csv");
    mvprintw(line++, 0, "Time elapsed: %f seconds", ((double)(end - start) / CLOCKS_PER_SEC));
    mvprintw(line++, 0, "Press any key to return to main menu");
    refresh();
    getch();
    clear();
    printIntro();
    post_menu(main_menu);
    mvprintw(LINES - 2, 0, "F1 to Exit");
    refresh();
}

int main() {

    const char *choices[] = {
        "Array List",
        "Singly Linked List - Head",
        "Singly Linked List - Head & Tail",
        "Doubly Linked List",
        "Perform Structures Tests"
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
                if (strcmp(item_name(current_item(my_menu)), "Perform Structures Tests") == 0) {
                    unpost_menu(my_menu);
                    clear();
                    testStructures(my_menu);
                    refresh();
                } else {
                    ITEM *cur_item = current_item(my_menu);
                    unpost_menu(my_menu);  // Odpięcie menu przed przejściem do sub-menu
                    clear();  // Wyczyszczenie ekranu przed przejściem do sub-menu
                    printIntro();

                    if (strcmp(item_name(cur_item), "Array List") == 0) {
                        displaySubChoices(item_name(cur_item), my_menu, arrayList);
                    } else if (strcmp(item_name(cur_item), "Singly Linked List - Head") == 0) {
                        displaySubChoices(item_name(cur_item), my_menu, singlyLinkedHeadList);
                    } else if (strcmp(item_name(cur_item), "Singly Linked List - Head & Tail") == 0) {
                        displaySubChoices(item_name(cur_item), my_menu, singlyLinkedHeadTailList);
                    } else if (strcmp(item_name(cur_item), "Doubly Linked List") == 0) {
                        displaySubChoices(item_name(cur_item), my_menu, doublyLinkedList);
                    }

                    refresh();
                }
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