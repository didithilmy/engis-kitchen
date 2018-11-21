//
// Created by Muhammad Aditya Hilmy on 18/11/18.
//

#include "food.h"

/**
 * Add Food to TabFood
 * @param TF TabFood
 * @param F Food
 */

void AddFood(TabFood *TF, Food F) {
    if(TF->N < MAX_FOOD) {
        TF->N++;
        TF->T[TF->N] = F;
    }
}

Food CreateFood(POINT coord, Kata name) {
    Food food;

    food.coordinate = coord;
    food.name = name;

    return food;
}

