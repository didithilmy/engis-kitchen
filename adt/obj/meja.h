/**
 * Engi's Kitchen Expansion
 * Meja abstract data type
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */


#ifndef ENGIS_KITCHEN_MEJA_H
#define ENGIS_KITCHEN_MEJA_H

#define MAX_MEJA 10

#include "../point.h"
#include "customer.h"

typedef struct tMeja {
    POINT coordinate;
    int capacity;
    int tableNo;
    struct tCustomer *custAddress;
} Meja;

typedef struct {
    Meja T[MAX_MEJA + 1];
    int N;
} TabMeja;

void InitTabMeja(TabMeja *T);
Meja *AddMeja(TabMeja *T, Meja M);
Meja CreateMeja(POINT coord, int capacity, int tableNo);

#endif //ENGIS_KITCHEN_MEJA_H
