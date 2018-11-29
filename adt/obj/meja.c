/**
 * Engi's Kitchen Expansion
 * Meja abstract data type
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#include <stddef.h>
#include "meja.h"

/**
 * Add Meja to TabMeja
 * @param T TabMeja
 * @param M Meja
 * @return pointer to Meja
 */
Meja *AddMeja(TabMeja *T, Meja M) {
    if(T->N < MAX_MEJA) {
        T->N++;
        T->T[T->N] = M;
        return &(T->T[T->N]);
    } else {
        return NULL;
    }
}

/**
 * Builds new Meja object
 * @param coord coordinate
 * @param capacity capacity (2 or 4)
 * @param tableNo table number
 * @return Meja object
 */
Meja CreateMeja(POINT coord, int capacity, int tableNo) {
    Meja meja;

    meja.coordinate = coord;
    meja.capacity = capacity;
    meja.tableNo = tableNo;
    meja.custAddress = NULL;

    return meja;
}

/**
 * Initialize array of Meja
 * @param T array of meja
 */
void InitTabMeja(TabMeja *T) {
    T->N = 0;
}