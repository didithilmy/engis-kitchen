/**
 * Engi's Kitchen Expansion
 * place command
 * @author Zalikha Adiera Gambetta, NIM 18217027
 */

#include "../../adt/obj/customer.h"
#include "../../adt/obj/meja.h"
#include "../../adt/customer_queue.h"

void place_customer (Meja * meja, Queue * Q)
{
	// kamus lokal
	Customer *customer;
	int x;

	// algoritma
	while (!IsEmpty(Q))
	{
		while (SearchCust(Q,x))
		{
			if ((meja.capacity == 2) && (SearchQ(Q,2))
			{
				Del(&Q,&C);
				Customer.patience = 30;
				
				customer->custAddress->meja = meja;
				
				// TODO ke UI "meja = meja sudah terisi"
			}
			else if ((meja.capacity == 4) && (SearchQ(Q,4))
			{
				Del(&Q,&C);
				Customer.patience = 30;
				
				customer->custAddress->meja = meja;
				
				// TODO ke UI "meja = meja sudah terisi"
			}
		}
	}
}

// procedure search 
void SearchCust (Queue Q, int X)
{
	Customer customer;
	int i;
	boolean found;
	
	found = false;
	i = Head(Q);
	while ((i<=Tail(Q)) && !found)
	{
		if (customer.N == X)
		{
			found = true;
		}
		i++;
	}
	return(found);
}
