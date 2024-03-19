#include <cstdlib>
#include <ncurses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

const char *choices[] = {
    "Build from file",
    "Remove",
    "Add",
    "Find",
    "Create randomly",
    "Display",
    "Exit",
};

int main() {
    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices = ARRAY_SIZE(choices);
    ITEM *cur_item;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    int startx = 0; /* Możesz ustawić na środek ekranu za pomocą (80 - szerokość_menu) / 2 */
    int starty = 7; /* Pozycja startowa dla menu (po sztuce ASCII i informacjach projektu) */


    // Print ASCII art and project info
    mvprintw(0, 0, " _____  _    _  _____ ");
    mvprintw(1, 0, "|  __ \\| |  | ||  __ \\");
    mvprintw(2, 0, "| |__) | |/\\| || |__) |");
    mvprintw(3, 0, "|  ___/|      ||  _  / ");
    mvprintw(4, 0, "| |    |  /\\  || | \\ \\ ");
    mvprintw(5, 0, "|_|    |_/  \\_||_|  \\_\\");
    mvprintw(6, 0, "Project 1 - Data Structures | Adrian Goral 272545 | Paulina Szulc 272592");

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
                cur_item = current_item(my_menu);
                // Here you can add your code to handle each option
                // For example:
                // if (strcmp(item_name(cur_item), "Build from file") == 0) {
                //     // Code to build from file
                // }
                break;
        }
    }

    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);
    endwin();
}