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

#include "ui_commons.h"
#include "../adt/headers.h"

#define MAP_GRID_LINE 3
#define MAP_GRID_COL 6
#define MAP_TOP_OFFSET_LINE 3
#define SIDE_PANEL_WIDTH 25

extern FIELD *field[2];
extern FORM  *commandForm;
extern WINDOW **mapWindows;
extern WINDOW *nameWindow, *moneyWindow, *lifeWindow, *timeWindow;
extern WINDOW *waitingCustWindow, *orderWindow, *foodStackWindow;

FIELD *field[2];
FORM  *commandForm;
WINDOW **mapWindows;
WINDOW *nameWindow, *moneyWindow, *lifeWindow, *timeWindow;
WINDOW *waitingCustWindow, *orderWindow, *foodStackWindow;


void game_ui_init();

void buildGameScreen(int HORZ, int VERT);
void loadRestaurantLayout(TabMeja T, POINT door);
void loadKitchenLayout(TabFood T, POINT door);

#endif //ENGIS_KITCHEN_DISPLAY_H
