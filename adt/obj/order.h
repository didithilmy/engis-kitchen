/**
 * Engi's Kitchen Expansion
 * Order abstract data type
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */


#ifndef ENGIS_KITCHEN_ORDER_H
#define ENGIS_KITCHEN_ORDER_H

#include "../mesin_kata.h"
#include "food.h"
#include "meja.h"


typedef struct tOrder {
    struct tFood *food;
    struct tMeja *meja;
} Order;

void OrderAllocate (Order **order, Food *food, struct tMeja *meja);
void OrderDeallocate(Order *order);
/*Fungsi untuk melakukan order*/

#endif //ENGIS_KITCHEN_ORDER_H
