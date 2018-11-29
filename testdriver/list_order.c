#include order_list.h
#include order.h

int main() {
	List L;
	Order X,Y;
	
	CreateEmpty(&L);
	InsOrderFirst(&L,&X);
	InsOrderLast (&L,&Y);
	
	return 0;
}

