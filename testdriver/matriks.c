/**
 * Engi's Kitchen Expansion
 * Matrix test driver
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include <stdio.h>
#include "../adt/matriks.h"
#include "../adt/headers.h"

int main () { 
	MATRIKS matrix;
	int bx, by, i, j;

	printf("Matrix size: ");
	scanf("%d %d", &bx, &by);

	MakeMATRIKS(by, bx, &matrix);
	printf("Created Matrix with size of (%d, %d)\n", GetLastIdxBrs(matrix), GetFirstIdxKol(matrix));
	printf("Col first index: %d\n", GetFirstIdxKol(matrix));
	printf("Col last index: %d\n", GetLastIdxKol(matrix));
	printf("Row first index: %d\n", GetFirstIdxBrs(matrix));
	printf("Row last index: %d\n", GetLastIdxBrs(matrix));

	printf("Iterating all columns, setting odd-numbered row to have isPhysical = true\n");
	for(i = GetFirstIdxBrs(matrix); i <= GetLastIdxBrs(matrix); i++) {
		for(j = GetFirstIdxKol(matrix); j <= GetLastIdxKol(matrix); j++) {
			EditMATRIKS(i, j, &matrix, M_KOSONG, Nil, Nil, i % 2 == 1);
			printf("Element (%d, %d): isPhysical = %s\n", j, i, ElmtIsPhysical(matrix, i, j) ? "True" : "False");
		}
	}

	return 0;
} 
