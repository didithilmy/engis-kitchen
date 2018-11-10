/**
 * Engi's Kitchen Expansion
 * Game manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file game.h
 */
#ifndef ENGIS_KITCHEN_GAME_H
#define ENGIS_KITCHEN_GAME_H

#include "game.h"
#include "ins_set.h"
#include "game_display.h"
#include "adt/mesin_kata.h"

void startGame();
boolean driver(FORM *form, FIELD **fields, int ch);

#endif //ENGIS_KITCHEN_GAME_H
