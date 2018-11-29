/**
 * Engi's Kitchen Expansion
 * User Interface Commons
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#include <stdlib.h>
#include "../ui_commons.h"

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
    int ch;
    int cch;

    mvhline(y1, x1+1, 0, x2-x1-1);
    mvhline(y2, x1+1, 0, x2-x1-1);
    mvvline(y1+1, x1, 0, y2-y1-1);
    mvvline(y1+1, x2, 0, y2-y1-1);

    // Handle upper-left corner
    cch = mvinch(y1, x1);
    if(cch == ACS_LRCORNER || cch == ACS_BTEE || cch == ACS_RTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_LLCORNER) {
        ch = ACS_LTEE;
    } else if(cch == ACS_URCORNER) {
        ch = ACS_TTEE;
    } else if(cch == ACS_LTEE || cch == ACS_TTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_ULCORNER;
    }

    mvaddch(y1, x1, ch);

    // Handle lower-left corner
    cch = mvinch(y2, x1);
    if(cch == ACS_URCORNER || cch == ACS_TTEE || cch == ACS_RTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_LRCORNER) {
        ch = ACS_BTEE;
    } else if(cch == ACS_ULCORNER) {
        ch = ACS_LTEE;
    } else if(cch == ACS_BTEE || cch == ACS_LTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_LLCORNER;
    }
    mvaddch(y2, x1, ch);

    // Handle upper-right corner
    cch = mvinch(y1, x2);
    if(cch == ACS_LLCORNER || cch == ACS_BTEE || cch == ACS_LTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_ULCORNER) {
        ch = ACS_TTEE;
    } else if(cch == ACS_LRCORNER) {
        ch = ACS_RTEE;
    } else if(cch == ACS_TTEE || cch == ACS_RTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_URCORNER;
    }
    mvaddch(y1, x2, ch);

    // Handle lower-right corner
    cch = mvinch(y2, x2);
    if(cch == ACS_ULCORNER || cch == ACS_TTEE || cch == ACS_LTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_LLCORNER) {
        ch = ACS_BTEE;
    } else if(cch == ACS_URCORNER) {
        ch = ACS_RTEE;
    } else if(cch == ACS_BTEE || cch == ACS_RTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_LRCORNER;
    }
    mvaddch(y2, x2, ch);
}

void wPrintBorder(WINDOW *win, int y1, int y2, int x1, int x2) {
    chtype ch;
    chtype cch;

    mvwhline(win, y1, x1, 0, x2-x1);
    mvwhline(win, y2, x1, 0, x2-x1);
    mvwvline(win, y1, x1, 0, y2-y1);
    mvwvline(win, y1, x2, 0, y2-y1);
    mvwaddch(win, y1, x1, ACS_ULCORNER);
    mvwaddch(win, y2, x1, ACS_LLCORNER);
    mvwaddch(win, y1, x2, ACS_URCORNER);
    mvwaddch(win, y2, x2, ACS_LRCORNER);

    // Handle upper-left corner
    cch = mvwinch(win, y1, x1);
    if(cch == ACS_LRCORNER || cch == ACS_BTEE || cch == ACS_RTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_LLCORNER) {
        ch = ACS_LTEE;
    } else if(cch == ACS_URCORNER) {
        ch = ACS_TTEE;
    } else if(cch == ACS_LTEE || cch == ACS_TTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_ULCORNER;
    }

    mvwaddch(win, y1, x1, ch);

    // Handle lower-left corner
    cch = mvwinch(win, y2, x1);
    if(cch == ACS_URCORNER || cch == ACS_TTEE || cch == ACS_RTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_LRCORNER) {
        ch = ACS_BTEE;
    } else if(cch == ACS_ULCORNER) {
        ch = ACS_LTEE;
    } else if(cch == ACS_BTEE || cch == ACS_LTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_LLCORNER;
    }
    mvwaddch(win, y2, x1, ch);

    // Handle upper-right corner
    cch = mvwinch(win, y1, x2);
    if(cch == ACS_LLCORNER || cch == ACS_BTEE || cch == ACS_LTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_ULCORNER) {
        ch = ACS_TTEE;
    } else if(cch == ACS_LRCORNER) {
        ch = ACS_RTEE;
    } else if(cch == ACS_TTEE || cch == ACS_RTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_URCORNER;
    }
    mvwaddch(win, y1, x2, ch);

    // Handle lower-right corner
    cch = mvwinch(win, y2, x2);
    if(cch == ACS_ULCORNER || cch == ACS_TTEE || cch == ACS_LTEE) {
        ch = ACS_PLUS;
    } else if(cch == ACS_LLCORNER) {
        ch = ACS_BTEE;
    } else if(cch == ACS_URCORNER) {
        ch = ACS_RTEE;
    } else if(cch == ACS_BTEE || cch == ACS_RTEE || cch == ACS_PLUS) {
        ch = cch;
    } else {
        ch = ACS_LRCORNER;
    }
    mvwaddch(win, y2, x2, ch);
}

void resizeTerminalWindow(int width, int height) {
    char buf[48];

    sprintf(buf, "printf '\\e[8;%d;%dt'", height, width);
    system(buf);
}