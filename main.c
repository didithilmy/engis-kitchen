/**
 * Engi's Kitchen Expansion
 * Entrypoint
 *
 * This file serves as an entrypoint to the program, as well as the UI layer.
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#include <stdlib.h>
#include <stdio.h>
#include "game.h"

void printIntro();

char *command;

int main() {
    printIntro();
    startGame();
}

void printIntro() {
    printf("  ______             _ _       _  ___ _       _                 \n"
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
                   "             |_|                                                \n");
    printf("\nWelcome to Engi\'s Kitchen Expansion! It\'s been a year since I see you.\n");
    printf("> ");

}