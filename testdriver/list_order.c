/**
 * Engi's Kitchen Expansion
 * Order list test driver
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/order_list.h"

int main () { 
	List list;
	Order *order;
	int i;

	// Initialize list
	CreateEmpty(&list);

	// Allocate fictional Food
	Food food1 = CreateFood(MakePOINT(0, 0), BuildKata("Daging"), 200);
	Food food2 = CreateFood(MakePOINT(0, 1), BuildKata("Ayam"), 250);
	Food food3 = CreateFood(MakePOINT(0, 2), BuildKata("Cabe"), 300);

	// Create fictional Meja
	Meja meja1 = CreateMeja(MakePOINT(0, 1), 2, 1);
	Meja meja2 = CreateMeja(MakePOINT(0, 2), 2, 2);
	Meja meja3 = CreateMeja(MakePOINT(0, 3), 2, 3);

	// Create Order
	Order *o1, *o2, *o3;
	OrderAllocate(&o1, &food1, &meja1);
	OrderAllocate(&o2, &food2, &meja2);
	OrderAllocate(&o3, &food3, &meja3);

	// Add to List
	InsOrderLast(&list, o1);
	InsOrderFirst(&list, o2);
	InsOrderLast(&list, o3);

	// Show details
	printf("List has %d elements.\n", NbElmt(list));
	printf("Is list empty = %s\n", IsEmpty(list) ? "True" : "False");

	// Iterate 'till I die
	while(!IsEmpty(list)) {
		DelOrderFirst(&list, &order);

		// Print order
		printf("Order %p: \n", order);
		printf("   Meja %p: coord = (%d, %d), capacity = %d, tableNo = %d\n", order->meja, order->meja->coordinate.X, order->meja->coordinate.Y, order->meja->capacity, order->meja->tableNo);
		printf("   Food %p: name = ", order->food);

		// Print food
		for(i=1; i <= order->food->name.Length; i++) {
			printf("%c", order->food->name.TabKata[i]);
		}
		printf("\n");

		// Deallocate order
		OrderDeallocate(order);
	}

	printf("Is list empty = %s\n", IsEmpty(list) ? "True" : "False");

	return 0;
} 
