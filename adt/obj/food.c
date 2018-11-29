/**
 * Engi's Kitchen Expansion
 * Food abstract data type
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */


#include "food.h"

/**
 * Add Food to TabFood
 * @param TF TabFood
 * @param F Food
 * @return pointer to food
 */

Food *AddFood(TabFood *TF, Food F) {
    if(TF->N < MAX_FOOD) {
        TF->N++;
        TF->T[TF->N] = F;

        return &(TF->T[TF->N]);
    } else {
        return NULL;
    }
}

/**
 * Builds new Food object
 * @param coord coordinate
 * @param name food name
 * @return food object
 */
Food CreateFood(POINT coord, Kata name, int price) {
    Food food;

    food.coordinate = coord;
    food.name = name;
    food.price = price;

    return food;
}

/**
 * Initialize array of Food
 * @param T array of Food
 */
void InitTabFood(TabFood *T) {
    T->N = 0;
}