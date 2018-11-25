//
// Created by Muhammad Aditya Hilmy on 18/11/18.
//

#include "order.h"

Order CreateOrder (Food *FoodName, Meja *meja) {
	
	//Kamus Lokal
	Order order; 
	
	//ALGORITMA 
	order.food = FoodName ; 
	order.meja = meja; 
	
	return order; 
	
}


