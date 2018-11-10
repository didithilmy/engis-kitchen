/**
 * Engi's Kitchen Expansion
 * Intro display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file display.c
 */

#include "../intro_display.h"

WINDOW *window;

FIELD *intro_field[2];
FORM  *nameForm;

void buildIntroScreen() {
    // Build command input
    intro_field[0] = new_field(1, 50, 23, 16, 0, 0);
    field_opts_off(intro_field[0], O_AUTOSKIP);
    nameForm = new_form(intro_field);
    post_form(nameForm);
    mvprintw(23, 3, "%s", "Player Name: ");
    printBorder(22, 24, 1, 70);

    refresh();

    window = newwin(21, 100, 1, 1);
    refresh();

    wprintw(window, "\n  ______             _ _       _  ___ _       _                 \n"
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

    wprintw(window, "\n\nWelcome to Engi's Kitchen Expansion! It's been a year since I last saw you.");
    wprintw(window, "\nPress one of the keys of the menu below.");
    wrefresh(window);

    printBorder(19, 21, 1, 17);
    mvprintw(20, 3, "New Game (F1)");

    printBorder(19, 21, 19, 37);
    mvprintw(20, 21, "Start Game (F2)");

    printBorder(19, 21, 39, 56);
    mvprintw(20, 41, "Load Game (F3)");

    printBorder(19, 21, 58, 70);
    mvprintw(20, 60, "Exit (F4)");
}