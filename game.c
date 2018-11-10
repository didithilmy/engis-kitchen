/**
 * Engi's Kitchen Expansion
 * Game manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file game.h
 */

#include "game.h"

int M = 9;
int N = 9;

FIELD *field[2];
FORM  *commandForm;
WINDOW **mapWindows;
WINDOW *nameWindow, *moneyWindow, *lifeWindow, *timeWindow;
WINDOW *waitingCustWindow, *orderWindow, *foodStackWindow;

void startGame() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    buildGameScreen(N, M);
    updateName("Engi Suengi");
    updateTime(1000);
    updateLife(3);
    updateMoney(2000);

    // Move cursor to beginning of field
    form_driver(commandForm, REQ_BEG_FIELD);

    /* Loop through to get user requests */
    int ch;
    while((ch = getch()) != KEY_F(1)) {
        driver(commandForm, field, ch);
        refresh();
    }

    /* Un post form and free the memory */
    unpost_form(commandForm);
    free_form(commandForm);
    free_field(field[0]);

    endwin();
}

/**
 * Logical form driver
 * When a case goes unhandled, it calls the ui_driver
 */
void driver(FORM *form, FIELD **fields, int ch) {
    int i;
    char *command;

    switch (ch) {
        case KEY_ENTER:
        case 10:
            // TODO do something on enter
            form_driver(form, REQ_BEG_FIELD);

            command = field_buffer(fields[0], 0);
            updateName(command);
        default:
            ui_driver(form, fields, ch);
            break;
    }
}