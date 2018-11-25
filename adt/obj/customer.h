/**
 * Customer abstract data type
 */

#ifndef ENGIS_KITCHEN_CUSTOMER_H
#define ENGIS_KITCHEN_CUSTOMER_H

#include <stdlib.h>
#include "order.h"

#define CUSTOMER_INITIAL_PATIENCE 30

typedef struct tCustomer {
    int N;  // No of people
    int patience;   // Patience level
	struct tOrder *order;
} Customer;

#define CustomerPersons(P) (P).N
#define CustomerPatience(P) (P).patience

/**
 * Customer allocate
 * @return address of customer
 *
 * I.S. undefined
 * F.S. Customer is allocated in the memory, and CustAddress is not Nil
 */
Customer *CustomerAllocate();

/**
 * Customer deallocate
 * @param custAddress the address of customer to deallocate
 *
 * I.S. custAddress is not Nil
 * F.S. custAddress is deallocated from memory
 */
void CustomerDeallocate(Customer *custAddress);

/**
 * Make a new customer object
 * @param custAddress address of the customer object
 *
 * I.S. undefined
 * F.S. custAddress is the address of the allocated Customer, and CustomerPatience(P) is CUSTOMER_INITIAL_PATIENCE
 */
void MakeCustomer(Customer **custAddress);


#endif //ENGIS_KITCHEN_CUSTOMER_H
