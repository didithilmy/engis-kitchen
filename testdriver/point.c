/**
 * Engi's Kitchen Expansion
 * Point test driver
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include <stdio.h>
#include "../adt/point.h"

int main () { 
	POINT point;
	int bx, by;

	scanf("%d %d", &bx, &by);
	while(bx != -99 && by != -99) {
		point = MakePOINT(bx, by);
		// Print point
		printf("Point: %d, %d\n", point.X, point.Y);

		scanf("%d %d", &bx, &by);
	}

	return 0;
} 
