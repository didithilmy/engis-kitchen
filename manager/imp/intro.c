/**
 * Engi's Kitchen Expansion
 * Intro abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file game.h
 */

#include "../intro.h"

int showIntro() {
    int retval = 0;
    boolean keep_requesting = true;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    buildIntroScreen();

    /* Loop through to get user requests */
    int ch = getch();
    while(keep_requesting) {
        switch (ch) {
            case KEY_F(1):
                // Do get name
                break;

            case KEY_F(2):
                // Do get name
                keep_requesting = false;
                retval = 1;
                break;
            case KEY_F(3):
                // Do load game
                break;
            case KEY_F(4):
                // Exit
                keep_requesting = false;
                retval = 0;
                break;
        }
        if(keep_requesting)
            ch = getch();
    }

    endwin();

    return retval;
}