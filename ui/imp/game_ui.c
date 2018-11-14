/**
 * Engi's Kitchen Expansion
 * Game display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file display.c
 */

#include "../game_ui.h"
#include "../../adt/mesin_kata.h"
#include "../../ins_set.h"

boolean driver(FORM *form, FIELD **fields, int ch);
void onStartGame();

int M = 9, N = 9;

/**
 * Game UI initialization procedure
 */
void game_ui_init() {
    // Subscribe to events
    listen_event(START_GAME, &onStartGame);
}

void onStartGame() {
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

void buildGameScreen(int HORZ, int VERT) {
    int i, j, n;

    int HEIGHT = VERT * MAP_GRID_LINE;
    int WIDTH = (HORZ * MAP_GRID_COL) + (2 * (SIDE_PANEL_WIDTH + 1));

    curs_set(1);

    resizeTerminalWindow(WIDTH + 2, HEIGHT + MAP_TOP_OFFSET_LINE + MAP_TOP_OFFSET_LINE + 1);

    // TODO add delay to allow the window size to stabilize

    WINDOW *mapWin[(HORZ*VERT) + 1];
    mapWindows = mapWin;

    // Build command input
    field[0] = new_field(1, 50, MAP_TOP_OFFSET_LINE + HEIGHT+2, 11, 0, 0);
    field_opts_off(field[0], O_AUTOSKIP);
    commandForm = new_form(field);
    post_form(commandForm);
    mvprintw(MAP_TOP_OFFSET_LINE + HEIGHT+2, 1, "%s", "Command: ");
    printBorder(MAP_TOP_OFFSET_LINE + HEIGHT + 1, MAP_TOP_OFFSET_LINE + HEIGHT+3, 0, WIDTH);

    // Initiate name panel
    printBorder(0, 2, 0, SIDE_PANEL_WIDTH);
    nameWindow = newwin(1, SIDE_PANEL_WIDTH - 2, 1, 1);
    refresh();

    // Initiate queue panel
    printBorder(3, 3 + (HEIGHT/2), 0, SIDE_PANEL_WIDTH);
    mvprintw(4, 1, "%s", "Waiting Cust.");

    // Initiate order panel
    printBorder((HEIGHT/2) + 1 + 3, HEIGHT + 3, 0, SIDE_PANEL_WIDTH);
    mvprintw((HEIGHT/2) + 2 + 3, 1, "%s", "Order");

    // Initiate food stack panel
    printBorder(3, 3 + (HEIGHT), WIDTH - SIDE_PANEL_WIDTH, WIDTH);
    mvprintw(4, WIDTH - SIDE_PANEL_WIDTH + 1, "%s", "Food Stack");

    // Remaining width
    int remWidth = WIDTH - (SIDE_PANEL_WIDTH + 1);

    // Initiate money panel
    int moneyX1 = (SIDE_PANEL_WIDTH + 1);
    int moneyX2 = WIDTH - (remWidth/2);
    printBorder(0, 2, moneyX1, moneyX2);
    moneyWindow = newwin(1, moneyX2 - moneyX1 - 2, 1, moneyX1 + 1);
    refresh();

    // Initiate life panel
    int lifeX1 = moneyX2 + 1;
    int lifeX2 = WIDTH - (remWidth/4);
    printBorder(0, 2, lifeX1, lifeX2);
    lifeWindow = newwin(1, lifeX2 - lifeX1 - 2, 1, lifeX1 + 1);
    refresh();

    // Initiate time panel
    int timeX1 = lifeX2 + 1;
    int timeX2 = WIDTH;
    printBorder(0, 2, timeX1, timeX2);
    timeWindow = newwin(1, timeX2 - timeX1 - 2, 1, timeX1 + 1);
    refresh();

    // Initiate MAP boxes
    n = 0;
    for(i = 0; i < VERT; i++) {
        for(j = 0; j < HORZ; j++) {
            n++;
            printBorder(MAP_TOP_OFFSET_LINE + (i*MAP_GRID_LINE), MAP_TOP_OFFSET_LINE + ((i+1)*MAP_GRID_LINE), (SIDE_PANEL_WIDTH + 1) + (j*MAP_GRID_COL), (SIDE_PANEL_WIDTH + 1) + ((j+1)*MAP_GRID_COL));
            mapWindows[n] = newwin(MAP_GRID_LINE - 2, MAP_GRID_COL - 2, MAP_TOP_OFFSET_LINE + (i*MAP_GRID_LINE) + 1, (SIDE_PANEL_WIDTH + 1) + (j*MAP_GRID_COL) + 1);
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
