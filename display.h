/**
 * Engi's Kitchen Expansion
 * Game display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file display.h
 */

#ifndef ENGIS_KITCHEN_DISPLAY_H
#define ENGIS_KITCHEN_DISPLAY_H

#include <ncurses.h>
#include <form.h>
#include <panel.h>
#include <string.h>
#include <ctype.h>

#define MAP_GRID_LINE 3
#define MAP_GRID_COL 7
#define MAP_TOP_OFFSET_LINE 3
#define SIDE_PANEL_WIDTH 20

extern FIELD *field[2];
extern FORM  *commandForm;
extern WINDOW **mapWindows;
extern WINDOW *nameWindow, *moneyWindow, *lifeWindow, *timeWindow;
extern WINDOW *waitingCustWindow, *orderWindow, *foodStackWindow;

void printBorder(int y1, int y2, int x1, int x2);
void ui_driver(FORM *form, FIELD **fields, int ch);
void buildGameScreen();

void updateMoney(int money);
void updateLife(int life);
void updateTime(int time);
void updateName(char *name);

#endif //ENGIS_KITCHEN_DISPLAY_H
