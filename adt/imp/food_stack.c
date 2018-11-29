/**
 * Engi's Kitchen Expansion
 * Food stack abstraction for linear list
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#include "../food_stack.h"

// Operator Dasar Stack
void Push (Stack *S, Food *X) {
    infotype data;
    data.food = X;

    InsVFirst(S, data);
}
// Menambahkan X sebagai elemen Stack S.
// I.S. S mungkin kosong
// F.S. X menjadi TOP yang baru, jika alokasi elemen baru berhasil.
// Jika alokasi gagal, S tetap.

void Pop (Stack *S, Food **X) {
    infotype data;
    DelVFirst(S, &data);

    *X = data.food;
}
// Menghapus X dari Stack S.
// I.S. S tidak kosong
// F.S. X adalah nilai elemen TOP yang lama, elemen top yang lama didealokasi,
// TOP(S) = Next(TOP(S)).