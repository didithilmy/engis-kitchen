/**
 * Meja abstract data type
 */

#ifndef ENGIS_KITCHEN_MEJA_H
#define ENGIS_KITCHEN_MEJA_H

#include "../point.h"
#include "customer.h"

typedef struct {
    POINT coordinate;
    int capacity;
    int tableNo;
    Customer *custAddress;
} Meja;


#endif //ENGIS_KITCHEN_MEJA_H
