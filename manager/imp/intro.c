/**
 * Engi's Kitchen Expansion
 * Intro abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file game.h
 */

#include "../intro.h"
#include "../../ui/game_display.h"

int showIntro() {
    int retval = 0;
    boolean keep_requesting = true;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    buildIntroScreen();

    form_driver(nameForm, REQ_BEG_FIELD);


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
            default:
                ui_driver(nameForm, intro_field, ch);

        }
        if(keep_requesting)
            ch = getch();
    }

    // Free form
    unpost_form(nameForm);
    free_form(nameForm);
    free_field(intro_field[0]);

    endwin();

    return retval;
}