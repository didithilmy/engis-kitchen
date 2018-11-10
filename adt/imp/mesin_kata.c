/**
 * Engi's Kitchen Expansion
 * Mesin Kata abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file mesin_kata.c
 */



#include "../mesin_kata.h"

boolean EndKata;
Kata CKata;

void Ignore_Blank() {
    while(GetCC() == BLANK && (GetCC() != MARK)) {
        ADV();
    }
}

void STARTKATA(char *string) {
    START(string);
    Ignore_Blank();

    if(IsEOP()) {
        EndKata = true;
    } else {
        EndKata = false;
        SalinKata();
    }
}

void ADVKATA() {
    Ignore_Blank();
    if(IsEOP()) {
        EndKata = true;
    } else {
        SalinKata();
    }
}

void SalinKata() {
    int i = 1;
    while(1) {
        CKata.TabKata[i] = GetCC();
        ADV();
        if(IsEOP() || GetCC() == BLANK) {
            break;
        } else {
            i++;
        }
    }
    CKata.Length = i;
}

Kata BuildKata(char *str) {
    int i;

    i = 0;
    Kata kata;
    while(str[i] != MARK) {
        kata.TabKata[i+1] = str[i];
        i++;
    }

    kata.Length = i;

    return kata;
}

/**
 * Compares two Katas
 * @param k1 first Kata
 * @param k2 second Kata
 * @return is kata identical
 */
boolean CompareKata(Kata k1, Kata k2, boolean caseSensitive) {
    // Local variables
    int i;
    boolean isEqual;

    // Algorithm
    if(k1.Length != k2.Length) {
        return false;
    } else {
        i = 1;
        isEqual = true;
        while(isEqual && i <= k1.Length) {
            isEqual = caseSensitive ? k1.TabKata[i] == k2.TabKata[i] : ToUpper(k1.TabKata[i]) == ToUpper(k2.TabKata[i]);
            i++;
        }

        return isEqual;
    }
}