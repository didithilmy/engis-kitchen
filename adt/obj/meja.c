//
// Created by Muhammad Aditya Hilmy on 18/11/18.
//

#include <stddef.h>
#include "meja.h"

/**
 * Add Meja to TabMeja
 * @param T TabMeja
 * @param M Meja
 */
void AddMeja(TabMeja *T, Meja M) {
    if(T->N < MAX_MEJA) {
        T->N++;
        T->T[T->N] = M;
    }
}

Meja CreateMeja(POINT coord, int capacity, int tableNo) {
    Meja meja;

    meja.coordinate = coord;
    meja.capacity = capacity;
    meja.tableNo = tableNo;
    meja.custAddress = NULL;

    return meja;
}