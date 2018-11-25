/**
 * Food stack abstraction for linear list
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#ifndef ENGIS_KITCHEN_FOOD_STACK_H
#define ENGIS_KITCHEN_FOOD_STACK_H

#include "listlinier.h"

typedef List Stack;

/*****************************************************
TOP(S) = Nil adalah stack dengan elemen kosong
Definisi stack dengan representasi berkait :
  Jika S adalah Stack maka akses elemen :
    TOP(S) adalah alamat elemen TOP
    Info(P) untuk mengakses elemen info dengan alamat P
    Next(P) untuk mengakses elemen next dengan alamat P
******************************************************/

#define FoodInfo(P) (Info(P)).food

/***************/
/*  Prototype  */
/***************/

//Konstruktor/Kreator

// Operator Dasar Stack
void Push (Stack *S, Food *X);
// Menambahkan X sebagai elemen Stack S.
// I.S. S mungkin kosong
// F.S. X menjadi TOP yang baru, jika alokasi elemen baru berhasil.
// Jika alokasi gagal, S tetap.

void Pop (Stack *S, Food **X);
// Menghapus X dari Stack S.
// I.S. S tidak kosong
// F.S. X adalah nilai elemen TOP yang lama, elemen top yang lama didealokasi,
// TOP(S) = Next(TOP(S)).


#endif //ENGIS_KITCHEN_FOOD_STACK_H
