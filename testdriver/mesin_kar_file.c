/**
 * Engi's Kitchen Expansion
 * Mesin Kar file test driver
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/mesin_kar_file.h"

char CC;

int main() {
    int i;

    // Acquire Kata
    STARTFILE("test.dat");

    // Reprint kar
    do {
        printf("%c\n", GetFCC());
        ADVFILE();
    } while (!IsEOPF());
}