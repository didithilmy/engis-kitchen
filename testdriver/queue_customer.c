/**
 * Engi's Kitchen Expansion
 * Customer queue test driver
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/customer_queue.h"

int main () { 
	Queue queue;
	Customer *customer;
	int buf, buf2;

	// Initialize queue
	CreateEmpty(&queue);

	scanf("%d", &buf);
	while(buf != -999) {
		// Acquire patience
		scanf("%d", &buf2);

		// Create customer
		customer = CustomerAllocate();
		customer->N = buf;
		customer->patience = buf2;
		customer->order = Nil;

		// Place Customer to list
		Add(&queue, customer);

		// Acquire cust N
		scanf("%d", &buf);
	}

	// Print all customer data
	printf("Dumping customer data..\n");
	while(!IsEmpty(queue)) {
		Del(&queue, &customer);

		// Show customer data
		printf("Customer %p: N = %d, patience = %d\n", customer, customer->N, customer->patience);

		// Deallocate
		CustomerDeallocate(customer);
	}
	
	return 0;
} 
