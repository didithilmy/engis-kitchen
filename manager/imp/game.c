/**
 * Engi's Kitchen Expansion
 * Game manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file game.h
 */

#include "../game.h"

int M = 9;
int N = 9;

boolean ExecuteCommands();

FIELD *field[2];
FORM  *commandForm;
WINDOW **mapWindows;
WINDOW *nameWindow, *moneyWindow, *lifeWindow, *timeWindow;
WINDOW *waitingCustWindow, *orderWindow, *foodStackWindow;

Kata CKata;
boolean EOP;

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
        if(driver(commandForm, field, ch)) {
            break;
        } else {
            refresh();
        }
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
 * @return should exit program
 */
boolean driver(FORM *form, FIELD **fields, int ch) {
    int i;
    char *command;

    switch (ch) {
        case KEY_ENTER:
        case 10:
            form_driver(form, REQ_BEG_FIELD);

            command = field_buffer(fields[0], 0);
            STARTKATA(command);

            // If execute command returns true, should exit program
            if(ExecuteCommands()) return true;
        default:
            ui_driver(form, fields, ch);
            return false;
    }
}

/**
 * Execute command stored in CKata
 * @return should exit program
 */
boolean ExecuteCommands() {
    if(CompareKata(CKata, INS_EXIT, false)) {
        return true;
    }

    return false;
}