/**
 * Engi's Kitchen Expansion
 * Intro display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file display.c
 */

#include "../intro_ui.h"
#include "../../ins_set.h"
#include "../../eventbus/eventbus.h"

void intro_driver(FORM *form, FIELD **fields, int ch);
void Intro_ExecuteCommands();
void promptName();
void setName();

boolean keep_requesting = true;
boolean is_prompting_name;
int retval = 0;

void intro_ui_init() {

}

int showIntro() {
    keep_requesting = true;
    is_prompting_name = false;
    retval = 0;

    buildIntroScreen();

    /* Loop through to get user requests */
    int ch = getch();
    while(keep_requesting) {
        intro_driver(nameForm, intro_field, ch);
        if(keep_requesting)
            ch = getch();
    }

    return retval;
}


/**
 * Logical form driver
 * When a case goes unhandled, it calls the ui_driver
 * @return should exit program
 */
void intro_driver(FORM *form, FIELD **fields, int ch) {
    char *command;

    switch (ch) {
        case KEY_ENTER:
        case 10:
            form_driver(form, REQ_BEG_FIELD);

            command = field_buffer(fields[0], 0);
            STARTKATA(command);

            if(!is_prompting_name) {
                Intro_ExecuteCommands();
            } else {
                setName();
            }
        default:
            ui_driver(form, fields, ch);
    }
}


/**
 * Execute command stored in CKata
 */
void Intro_ExecuteCommands() {
    DataType dt;

    if(CompareKata(CKata, INS_EXIT, false)) {
        keep_requesting = false;
    } else if(CompareKata(CKata, INS_START, false)) {
        // Check if game exists
        if(publish_getval_event(IS_GAME_EXISTS).integer) {
            keep_requesting = false;
            retval = 1;
        } else {
            promptName();
        }
    } else if(CompareKata(CKata, INS_NEW, false)) {
        promptName();
    } else if(CompareKata(CKata, INS_LOAD, false)) {
        publish_event(LOAD_GAME);
        keep_requesting = false;
        retval = 1;
    }
}

/**
 * Prompt name
 */
void promptName() {
    is_prompting_name = true;
    mvprintw(20, 1, "%10s", "Name: ");
    refresh();
}

/**
 * Set name
 */
void setName() {
    DataType dt;
    dt.kata = CKata;
    is_prompting_name = false;
    mvprintw(20, 1, "%10s", "Command: ");
    publish_1p_event(NEW_GAME, dt);

    keep_requesting = false;
    retval = 1;
}


void buildIntroScreen() {
    curs_set(1);

    // Build command input
    intro_field[0] = new_field(1, 50, 20, 11, 0, 0);
    field_opts_off(intro_field[0], O_AUTOSKIP);
    nameForm = new_form(intro_field);
    post_form(nameForm);
    mvprintw(20, 1, "%10s", "Command: ");

    refresh();
    printBorder(19, 21, 0, 80);

    //window = newwin(18, 100, 1, 1);

    refresh();

    mvprintw(1, 1, "\n  ______             _ _       _  ___ _       _                 \n"
                   " |  ____|           (_| )     | |/ (_) |     | |                \n"
                   " | |__   _ __   __ _ _|/ ___  | ' / _| |_ ___| |__   ___ _ __   \n"
                   " |  __| | '_ \\ / _` | | / __| |  < | | __/ __| '_ \\ / _ \\ '_ \\  \n"
                   " | |____| | | | (_| | | \\__ \\ | . \\| | || (__| | | |  __/ | | | \n"
                   " |______|_| |_|\\__, |_| |___/ |_|\\_\\_|\\__\\___|_| |_|\\___|_| |_| \n"
                   " |  ____|       __/ |              (_)                          \n"
                   " | |__  __  ___|___/ __ _ _ __  ___ _  ___  _ __                \n"
                   " |  __| \\ \\/ / '_ \\ / _` | '_ \\/ __| |/ _ \\| '_ \\               \n"
                   " | |____ >  <| |_) | (_| | | | \\__ \\ | (_) | | | |              \n"
                   " |______/_/\\_\\ .__/ \\__,_|_| |_|___/_|\\___/|_| |_|              \n"
                   "             | |                                                \n"
                   "             |_|                                                ");

    mvprintw(16, 1, "Welcome to Engi's Kitchen Expansion! It's been a year since I last saw you.");
    mvprintw(17, 1, "Type in one of these commands: NEW, START, LOAD, EXIT");
    refresh();

    form_driver(nameForm, REQ_BEG_FIELD);

    /*mvwprintw(window, 20, 2, "New Game (F1)");

    wPrintBorder(window, 19, 21, 18, 36);
    mvwprintw(window, 20, 20, "Start Game (F2)");

    wPrintBorder(window, 19, 21, 38, 55);
    mvwprintw(window, 20, 40, "Load Game (F3)");

    wPrintBorder(window, 19, 21, 57, 69);
    mvwprintw(window, 20, 59, "Exit (F4)");*/

    //wrefresh(window);
}