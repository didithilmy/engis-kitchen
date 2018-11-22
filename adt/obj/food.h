/**
 * Food adt
 */
 
#define MAX_FOOD 20

#ifndef ENGIS_KITCHEN_FOOD_H
#define ENGIS_KITCHEN_FOOD_H

#include "../mesin_kata.h"
#include "../point.h"

typedef struct {
	POINT coordinate;
    Kata name;
} Food;

typedef struct {
    Food T[MAX_FOOD + 1];
    int N;
} TabFood;

Food *AddFood(TabFood *TF, Food F);
//I.S adalah Tabel Food sembarang 
//F.S adalah makanan ditambahkan dalam tabel makanan 

Food CreateFood(POINT coord, Kata nama); 
//Fungsi pada awal loading file untuk menambahkan makanan dengan koordinatnya

void InitTabFood(TabFood *T);

#endif //ENGIS_KITCHEN_FOOD_H
