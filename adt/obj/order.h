/**
 * Order adt
 */

#ifndef ENGIS_KITCHEN_ORDER_H
#define ENGIS_KITCHEN_ORDER_H

#include "../mesin_kata.h"
#include "meja.h"

typedef struct tOrder {
    Kata foodName;
    Meja *meja;
} Order;

#endif //ENGIS_KITCHEN_ORDER_H
