/**
 * Engi's Kitchen Expansion
 * Game over display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file gameover_ui.h
 */


#ifndef ENGIS_KITCHEN_GMOVER_DISPLAY_H
#define ENGIS_KITCHEN_GMOVER_DISPLAY_H

#include <ncurses.h>
#include <form.h>
#include <panel.h>
#include <string.h>
#include <ctype.h>

#include "ui_commons.h"

void buildGameOverScreen();
void showGameOver();


#endif //ENGIS_KITCHEN_GMOVER_DISPLAY_H
