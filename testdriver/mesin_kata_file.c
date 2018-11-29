/**
 * Engi's Kitchen Expansion
 * Mesin Kata file test driver
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/mesin_kata_file.h"

Kata MKF_CKata;

int main() {
    int i;

    // Acquire Kata
    STARTFILE("test.dat");

    // Acquire first Kata
    if(!IsEOPF()) {
        for(i = 1; i <= MKF_CKata.Length; i++) {
            printf("%c", MKF_CKata.TabKata[i]);
        }
        printf("\n");
    }

    // Reprint Kata
    while (!IsEOPF()) {
        MKF_ADVKATA();
        for(i = 1; i <= MKF_CKata.Length; i++) {
            printf("%c", MKF_CKata.TabKata[i]);
        }
        printf("\n");
    }
}