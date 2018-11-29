/**
 * Engi's Kitchen Expansion
 * Intro display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file intro_ui.h
 */

#ifndef ENGIS_KITCHEN_GMOVER_DISPLAY_H
#define ENGIS_KITCHEN_GMOVER_DISPLAY_H

#include <ncurses.h>
#include <form.h>
#include <panel.h>
#include <string.h>
#include <ctype.h>

#include "ui_commons.h"
#include "../ins_set.h"

extern FIELD *intro_field[2];
extern FORM  *nameForm;

FIELD *intro_field[2];
FORM  *nameForm;

void intro_ui_init();
void buildIntroScreen();
int showIntro();


#endif //ENGIS_KITCHEN_GMOVER_DISPLAY_H
