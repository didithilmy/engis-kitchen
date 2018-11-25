/**
 * Customer abstract data type
 *
 * @author TODO ISI AUTHORNYA YANG BENER PLS
 */

#include "customer.h"

/**
 * Customer allocate
 * @return address of customer
 *
 * I.S. undefined
 * F.S. Customer is allocated in the memory, and CustAddress is not Nil
 */
Customer *CustomerAllocate() {
    return (Customer *) malloc(sizeof(Customer));
}

/**
 * Customer deallocate
 * @param custAddress the address of customer to deallocate
 *
 * I.S. custAddress is not Nil
 * F.S. custAddress is deallocated from memory
 */
void CustomerDeallocate(Customer *custAddress) {
    free(custAddress);
}

/**
 * Make a new customer object
 * @param custAddress address of the customer object
 *
 * I.S. undefined
 * F.S. custAddress is the address of the allocated Customer, and CustomerPatience(P) is CUSTOMER_INITIAL_PATIENCE, ans CustomerPersons(P) is a random value 2 or 4
 */
void MakeCustomer(Customer **custAddress) {
    *custAddress = CustomerAllocate();
    (*custAddress)->patience = CUSTOMER_INITIAL_PATIENCE;
    (*custAddress)->N  = (rand() % 3 > 1) ? 2 : 4;
}