/**
 * Engi's Kitchen Expansion
 * Array ADT test driver
 * Array ADT is represented by TabFood and TabMeja
 * TabFood will be the test object
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/obj/food.h"

int main () {
	int i, j;
	TabFood tabFood;
	InitTabFood(&tabFood);

	AddFood(&tabFood, CreateFood(MakePOINT(0, 0), BuildKata("Ayam"), 200));
	AddFood(&tabFood, CreateFood(MakePOINT(0, 1), BuildKata("Nasi"), 250));
	AddFood(&tabFood, CreateFood(MakePOINT(0, 2), BuildKata("Mentega"), 300));
	AddFood(&tabFood, CreateFood(MakePOINT(0, 3), BuildKata("Sate"), 350));
	AddFood(&tabFood, CreateFood(MakePOINT(0, 4), BuildKata("Nasjep"), 400));

	// Iterate TabFood
	for(i = 1; i <= tabFood.N; i++) {
		printf("Food %d: price = %d, coord = (%d, %d), name = ", i, tabFood.T[i].price, tabFood.T[i].coordinate.X, tabFood.T[i].coordinate.Y);

		// Print food name
		for(j = 1; j <= tabFood.T[i].name.Length; j++) {
			printf("%c", tabFood.T[i].name.TabKata[j]);
		}

		printf("\n");
	}

	return 0;
} 
