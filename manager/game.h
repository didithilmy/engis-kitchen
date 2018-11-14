/**
 * Engi's Kitchen Expansion
 * Game manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file game.h
 */
#ifndef ENGIS_KITCHEN_GAME_H
#define ENGIS_KITCHEN_GAME_H

#include "../ins_set.h"
#include "../ui/game_ui.h"
#include "../adt/mesin_kata.h"

void game_manager_init();
boolean driver(FORM *form, FIELD **fields, int ch);

#endif //ENGIS_KITCHEN_GAME_H
