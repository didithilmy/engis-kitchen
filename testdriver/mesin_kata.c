/**
 * Mesin Kata test driver
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/mesin_kata.h"

Kata CKata;

int main() {
    char buf[50];
    int i;

    // Acquire Kata
    printf("Masukkan pita karakter: ");
    scanf("%[^\n]s", buf);
    STARTKATA(buf);

    // Acquire first Kata
    if(!IsEOP()) {
        for(i = 1; i <= CKata.Length; i++) {
            printf("%c", CKata.TabKata[i]);
        }
        printf("\n");
    }

    // Reprint Kata
    while (!IsEOP()) {
        ADVKATA();
        for(i = 1; i <= CKata.Length; i++) {
            printf("%c", CKata.TabKata[i]);
        }
        printf("\n");
    }
}