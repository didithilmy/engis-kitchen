/**
 * Engi's Kitchen Expansion
 * Intro display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file display.c
 */

#include "../intro_display.h"

WINDOW *window;

void buildIntroScreen() {
    curs_set(0);

    window = newwin(22, 100, 1, 1);

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

    wPrintBorder(window, 19, 21, 0, 16);
    mvwprintw(window, 20, 2, "New Game (F1)");

    wPrintBorder(window, 19, 21, 18, 36);
    mvwprintw(window, 20, 20, "Start Game (F2)");

    wPrintBorder(window, 19, 21, 38, 55);
    mvwprintw(window, 20, 40, "Load Game (F3)");

    wPrintBorder(window, 19, 21, 57, 69);
    mvwprintw(window, 20, 59, "Exit (F4)");

    wrefresh(window);
}