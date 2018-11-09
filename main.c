/**
 * Engi's Kitchen Expansion
 * Entrypoint
 *
 * This file serves as an entrypoint to the program, as well as the UI layer.
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <form.h>
#include <panel.h>
#include <string.h>
#include <ctype.h>

#define MAP_GRID_LINE 3
#define MAP_GRID_COL 7
#define MAP_LEFT_OFFSET_COL 21
#define MAP_TOP_OFFSET_LINE 3
#define PANEL_WIDTH_LEFT 20

int M = 9;
int N = 9;

void printBorder(int y1, int y2, int x1, int x2);
void driver(FORM *form, FIELD **fields, int ch);
void buildGameScreen();
void updateMoney(int money);
void updateLife(int life);
void updateTime(int time);
void updateName(char *name);

FIELD *field[2];
FORM  *commandForm;
WINDOW **mapWindows;
WINDOW *nameWindow, *moneyWindow, *lifeWindow, *timeWindow;
WINDOW *waitingCustWindow, *orderWindow, *foodStackWindow;

int main() {
    WINDOW *mapWin[(M*N) + 1];
    mapWindows = mapWin;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    buildGameScreen(N, M);

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

void buildGameScreen(int HORZ, int VERT) {
    int i, j, n;

    int HEIGHT = VERT * MAP_GRID_LINE;
    int WIDTH = (HORZ * MAP_GRID_COL) + (2 * MAP_LEFT_OFFSET_COL);
    int MAP_WIDTH = (HORZ * MAP_GRID_COL);

    // Build command input
    field[0] = new_field(1, 50, MAP_TOP_OFFSET_LINE + HEIGHT+2, 12, 0, 0);
    field_opts_off(field[0], O_AUTOSKIP);
    commandForm = new_form(field);
    post_form(commandForm);
    mvprintw(MAP_TOP_OFFSET_LINE + HEIGHT+2, 1, "%s", "Command: ");
    printBorder(MAP_TOP_OFFSET_LINE + HEIGHT + 1, MAP_TOP_OFFSET_LINE + HEIGHT+3, 0, WIDTH);

    // Initiate name panel
    printBorder(0, 2, 0, PANEL_WIDTH_LEFT);
    nameWindow = newwin(1, PANEL_WIDTH_LEFT - 2, 1, 1);
    refresh();
    updateName("Engi Suengi");

    // Initiate queue panel
    printBorder(3, 3 + (HEIGHT/2), 0, PANEL_WIDTH_LEFT);
    mvprintw(4, 1, "%s", "Waiting Cust.");

    // Initiate order panel
    printBorder((HEIGHT/2) + 1 + 3, HEIGHT + 3, 0, PANEL_WIDTH_LEFT);
    mvprintw((HEIGHT/2) + 2 + 3, 1, "%s", "Order");

    // Initiate food stack panel
    printBorder(3, 3 + (HEIGHT), WIDTH - PANEL_WIDTH_LEFT, WIDTH);
    mvprintw(4, WIDTH - PANEL_WIDTH_LEFT + 1, "%s", "Food Stack");

    // Remaining width
    int remWidth = WIDTH - MAP_LEFT_OFFSET_COL;

    // Initiate money panel
    int moneyX1 = MAP_LEFT_OFFSET_COL;
    int moneyX2 = WIDTH - (remWidth/2);
    printBorder(0, 2, moneyX1, moneyX2);
    moneyWindow = newwin(1, moneyX2 - moneyX1 - 2, 1, moneyX1 + 1);
    refresh();
    updateMoney(0);

    // Initiate life panel
    int lifeX1 = moneyX2 + 1;
    int lifeX2 = WIDTH - (remWidth/4);
    printBorder(0, 2, lifeX1, lifeX2);
    lifeWindow = newwin(1, lifeX2 - lifeX1 - 2, 1, lifeX1 + 1);
    refresh();
    updateLife(3);

    // Initiate time panel
    int timeX1 = lifeX2 + 1;
    int timeX2 = WIDTH;
    printBorder(0, 2, timeX1, timeX2);
    timeWindow = newwin(1, timeX2 - timeX1 - 2, 1, timeX1 + 1);
    refresh();
    updateTime(1000);

    // Initiate MAP boxes
    n = 0;
    for(i = 0; i < VERT; i++) {
        for(j = 0; j < HORZ; j++) {
            n++;
            printBorder(MAP_TOP_OFFSET_LINE + (i*MAP_GRID_LINE), MAP_TOP_OFFSET_LINE + ((i+1)*MAP_GRID_LINE), MAP_LEFT_OFFSET_COL + (j*MAP_GRID_COL), MAP_LEFT_OFFSET_COL + ((j+1)*MAP_GRID_COL));
            mapWindows[n] = newwin(MAP_GRID_LINE - 2, MAP_GRID_COL - 2, MAP_TOP_OFFSET_LINE + (i*MAP_GRID_LINE) + 1, MAP_LEFT_OFFSET_COL + (j*MAP_GRID_COL) + 1);
            refresh();
        }
    }
}

void updateMoney(int money) {
    wclear(moneyWindow);
    wprintw(moneyWindow, "Money: %d", money);
    wrefresh(moneyWindow);
}

void updateLife(int life) {
    wclear(lifeWindow);
    wprintw(lifeWindow, "Life: %d", life);
    wrefresh(lifeWindow);
}

void updateTime(int time) {
    wclear(timeWindow);
    wprintw(timeWindow, "Time: %d", time);
    wrefresh(timeWindow);
}

void updateName(char *name) {
    wclear(nameWindow);
    wprintw(nameWindow, "%s", name);
    wrefresh(nameWindow);
}

/**
 * Source: https://gist.github.com/alan-mushi/c8a6f34d1df18574f643
 * @param ch cursor
 */
void driver(FORM *form, FIELD **fields, int ch) {
    int i;

    switch (ch) {
        case KEY_DOWN:
            form_driver(form, REQ_NEXT_FIELD);
            form_driver(form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(form, REQ_PREV_FIELD);
            form_driver(form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(form, REQ_NEXT_CHAR);
            break;

            // Delete the char before cursor
        case KEY_BACKSPACE:
        case 127:
            form_driver(form, REQ_DEL_PREV);
            break;

            // Delete the char under the cursor
        case KEY_DC:
            form_driver(form, REQ_DEL_CHAR);
            break;

        case KEY_ENTER:
        case 10:
            form_driver(form, REQ_CLR_FIELD);
            // TODO do something on enter
            break;

        default:
            form_driver(form, ch);
            break;
    }
}

void printBorder(int y1, int y2, int x1, int x2) {
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}