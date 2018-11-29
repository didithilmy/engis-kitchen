/**
 * Mesin Kar test driver
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/mesin_kar.h"
#include <stdio.h>

char CC;

int main() {
    char buf[50];
    int i;

    // Acquire Kata
    printf("Masukkan pita karakter: ");
    scanf("%[^\n]s", buf);
    START(buf);

    // Reprint Kata
    do {
        printf("%d ", GetCC());
        ADV();
    } while (!IsEOP());
}