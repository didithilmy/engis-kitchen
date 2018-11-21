/**
 * Order adt
 */

#ifndef ENGIS_KITCHEN_ORDER_H
#define ENGIS_KITCHEN_ORDER_H

#include "../mesin_kata.h"
#include "meja.h"
#include "food.h" 


typedef struct tOrder {
    Food *food;
    Meja *meja;
} Order;

Order CreateOrder (Food *FoodName , Meja *meja);
/*Fungsi untuk melakukan order*/

#endif //ENGIS_KITCHEN_ORDER_H
