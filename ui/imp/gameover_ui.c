/**
 * Engi's Kitchen Expansion
 * Game over display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file gameover_ui.c
 */

#include "../gameover_ui.h"

void showGameOver() {
    buildGameOverScreen();
    getch();
}

void buildGameOverScreen() {
    clear();
    curs_set(0);

    mvprintw(1, 1, "   _____                         ____                 _ \n"
            "  / ____|                       / __ \\               | |\n"
            " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __| |\n"
            " | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__| |\n"
            " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |  |_|\n"
            "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|  (_)\n"
            "                                                        \n"
            "                                                        ");

    mvprintw(8, 1, "Game over! You have spent all your Life.");
    mvprintw(9, 1, "Press any key to continue..");

    mvprintw(12, 1, "Engi's Kitchen Expansion is made with passion by:\n");
    mvprintw(14, 1, "Muhammad Aditya Hilmy, NIM 18217025\n");
    mvprintw(15, 1, "Zalikha Adiera Gambetta, NIM 18217027\n");
    mvprintw(16, 1, "Muhammad Yanza Hattari, NIM 18217043\n");
    mvprintw(17, 1, "Claudia Renata Maharani Danardono, NIM 18217048\n");
    refresh();
}