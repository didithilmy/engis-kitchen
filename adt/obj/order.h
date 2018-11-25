/**
 * Order adt
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

Order CreateOrder (Food *FoodName, struct tMeja *meja);
/*Fungsi untuk melakukan order*/

#endif //ENGIS_KITCHEN_ORDER_H
