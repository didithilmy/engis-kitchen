/**
 * Engi's Kitchen Expansion
 * User Interface Commons
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file ui_commons.h
 */
#ifndef ENGIS_KITCHEN_DISPLAY_COMMONS_H
#define ENGIS_KITCHEN_DISPLAY_COMMONS_H

#include "../adt/headers.h"
#include "../eventbus/eventbus.h"
#include <ncurses.h>
#include <form.h>
#include <panel.h>
#include <string.h>
#include <ctype.h>

void printBorder(int y1, int y2, int x1, int x2);
void wPrintBorder(WINDOW *win, int y1, int y2, int x1, int x2);
void ui_driver(FORM *form, FIELD **fields, int ch);
void resizeTerminalWindow(int width, int height);

#endif //ENGIS_KITCHEN_DISPLAY_COMMONS_H
