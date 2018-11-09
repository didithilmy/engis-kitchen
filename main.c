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

#define MAP_GRID_LINE 3
#define MAP_GRID_COL 7
#define MAP_LEFT_OFFSET_COL 21
#define MAP_TOP_OFFSET_LINE 3
#define PANEL_WIDTH_LEFT 20

int HORZ = 9;
int VERT = 9;

void printBorder(int y1, int y2, int x1, int x2);

int main() {
    int i, j, n;

    int HEIGHT = VERT * MAP_GRID_LINE;
    int WIDTH = (HORZ * MAP_GRID_COL) + (2 * MAP_LEFT_OFFSET_COL);
    int MAP_WIDTH = (HORZ * MAP_GRID_COL);

    FIELD *field[2];
    FORM  *commandForm;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Build command input
    field[0] = new_field(1, 50, MAP_TOP_OFFSET_LINE + HEIGHT+2, 12, 0, 0);
    field_opts_off(field[0], O_AUTOSKIP);
    commandForm = new_form(field);
    post_form(commandForm);
    mvprintw(MAP_TOP_OFFSET_LINE + HEIGHT+2, 1, "%s", "Command: ");
    printBorder(MAP_TOP_OFFSET_LINE + HEIGHT + 1, MAP_TOP_OFFSET_LINE + HEIGHT+3, 0, WIDTH);

    // Initiate name panel
    printBorder(0, 2, 0, PANEL_WIDTH_LEFT);
    mvprintw(1, 1, "%s", "Engi");

    // Initiate queue panel
    printBorder(3, 3 + (HEIGHT/2), 0, PANEL_WIDTH_LEFT);
    mvprintw(4, 1, "%s", "Waiting Cust.");

    // Initiate order panel
    printBorder((HEIGHT/2) + 1 + 3, HEIGHT + 3, 0, PANEL_WIDTH_LEFT);
    mvprintw((HEIGHT/2) + 2 + 3, 1, "%s", "Order");

    // Initiate food stack panel
    printBorder(3, 3 + (HEIGHT), WIDTH - PANEL_WIDTH_LEFT, WIDTH);
    mvprintw(4, WIDTH - PANEL_WIDTH_LEFT + 1, "%s", "Food Stack");

    int remWidth = WIDTH - MAP_LEFT_OFFSET_COL;

    // Initiate money panel
    int moneyX1 = MAP_LEFT_OFFSET_COL;
    int moneyX2 = WIDTH - (remWidth/2);
    printBorder(0, 2, moneyX1, moneyX2);
    mvprintw(1, moneyX1 + 1, "Money: %d", 300);

    // Initiate life panel
    int lifeX1 = moneyX2 + 1;
    int lifeX2 = WIDTH - (remWidth/4);
    printBorder(0, 2, lifeX1, lifeX2);
    mvprintw(1, lifeX1 + 1, "Life: %d", 3);

    // Initiate time panel
    int timeX1 = lifeX2 + 1;
    int timeX2 = WIDTH;
    printBorder(0, 2, timeX1, timeX2);
    mvprintw(1, timeX1 + 1, "Time: %d", 1000);


    // Initiate MAP boxes
    n = 0;
    for(i = 0; i < VERT; i++) {
        for(j = 0; j < HORZ; j++) {
            n++;
            printBorder(MAP_TOP_OFFSET_LINE + (i*MAP_GRID_LINE), MAP_TOP_OFFSET_LINE + ((i+1)*MAP_GRID_LINE), MAP_LEFT_OFFSET_COL + (j*MAP_GRID_COL), MAP_LEFT_OFFSET_COL + ((j+1)*MAP_GRID_COL));
            refresh();
        }
    }

    /* Loop through to get user requests */
    int ch;
    while((ch = getch()) != KEY_F(1))
    {	switch(ch)
        {	case KEY_DOWN:
                /* Go to next field */
                form_driver(commandForm, REQ_NEXT_FIELD);
                /* Go to the end of the present buffer */
                /* Leaves nicely at the last character */
                form_driver(commandForm, REQ_END_LINE);
                break;
            case KEY_UP:
                /* Go to previous field */
                form_driver(commandForm, REQ_PREV_FIELD);
                form_driver(commandForm, REQ_END_LINE);
                break;
            default:
                /* If this is a normal character, it gets */
                /* Printed				  */
                form_driver(commandForm, ch);
                break;
        }
    }

    /* Un post form and free the memory */
    unpost_form(commandForm);
    free_form(commandForm);
    free_field(field[0]);

    endwin();
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