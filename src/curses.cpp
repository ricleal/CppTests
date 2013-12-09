#include <curses.h>
#include <unistd.h>


// Compile as:
// gcc curses.cpp -o curses -lcurses


void spinner(int spin_seconds) {
    static char const spin_chars[] = "/-\\|";
    unsigned long i, num_iterations = (spin_seconds * 10);
    for (i=0; i<num_iterations; ++i) {
        mvaddch(0, 0, spin_chars[i & 3]);
        refresh();
        usleep(100000);
    }
}

int main_curses() {
    initscr();    /* initializes curses */
    spinner(10);  /* spin for 10 seconds */
    endwin();     /* cleanup curses */
    return 0;
}

