/**
 * Meja abstract data type
 */

#ifndef ENGIS_KITCHEN_MEJA_H
#define ENGIS_KITCHEN_MEJA_H

#define MAX_MEJA 10

#include "../point.h"
#include "customer.h"

typedef struct {
    POINT coordinate;
    int capacity;
    int tableNo;
    Customer *custAddress;
} Meja;

typedef struct {
    Meja T[MAX_MEJA + 1];
    int N;
} TabMeja;

void AddMeja(TabMeja *T, Meja M);
Meja CreateMeja(POINT coord, int capacity, int tableNo);

#endif //ENGIS_KITCHEN_MEJA_H
