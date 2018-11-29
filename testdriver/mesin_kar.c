/**
 * Engi's Kitchen Expansion
 * Mesin Kar test driver
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */
#include "../adt/mesin_kar.h"

char CC;

int main() {
    char buf[50];
    int i;

    // Acquire Kata
    printf("Masukkan pita karakter: ");
    scanf("%[^\n]s", buf);
    START(buf);

    // Reprint Kar
    do {
        printf("%c\n", GetCC());
        ADV();
    } while (!IsEOP());
}