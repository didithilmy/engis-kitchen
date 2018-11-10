//
// Created by Muhammad Aditya Hilmy on 10/11/18.
//

#include <stdlib.h>
#include "../display_commons.h"


/**
 * Source: https://gist.github.com/alan-mushi/c8a6f34d1df18574f643
 * @param ch cursor
 */
void ui_driver(FORM *form, FIELD **fields, int ch) {
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

void wPrintBorder(WINDOW *win, int y1, int y2, int x1, int x2) {
    mvwhline(win, y1, x1, 0, x2-x1);
    mvwhline(win, y2, x1, 0, x2-x1);
    mvwvline(win, y1, x1, 0, y2-y1);
    mvwvline(win, y1, x2, 0, y2-y1);
    mvwaddch(win, y1, x1, ACS_ULCORNER);
    mvwaddch(win, y2, x1, ACS_LLCORNER);
    mvwaddch(win, y1, x2, ACS_URCORNER);
    mvwaddch(win, y2, x2, ACS_LRCORNER);
}

void resizeTerminalWindow(int width, int height) {
    char buf[48];

    sprintf(buf, "printf '\\e[8;%d;%dt'", height, width);
    system(buf);
}