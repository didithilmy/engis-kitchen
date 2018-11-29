/**
 * Engi's Kitchen Expansion
 * Order abstract data type
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */


#include "order.h"

/**
 * Allocate Order
 * @param order Order output
 * @param food Pointer to food
 * @param meja Pointer to Meja
 *
 * I.S. Food is defined, Meja is defined
 * F.S. order is the address of the newly-allocated Order
 */
void OrderAllocate (Order **order, Food *food, struct tMeja *meja) {
	*order = (Order *) malloc(sizeof(Order));
	(*order)->meja = meja;
	(*order)->food = food;
}

/**
 * Deallocate Order object
 * @param order
 */
void OrderDeallocate(Order *order) {
	free(order);
}