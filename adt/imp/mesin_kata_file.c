/**
 * Engi's Kitchen Expansion
 * Mesin Kata abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file mesin_kata_file.c
 */



#include "../mesin_kata_file.h"

boolean MKF_EndKata;
Kata MKF_CKata;

void MKF_Ignore_Blank() {
    while(GetFCC() == BLANK && (GetFCC() != MARK)) {
        ADVFILE();
    }
}

void MKF_STARTKATA(char *string) {
    STARTFILE(string);
    MKF_Ignore_Blank();

    if(IsEOPF()) {
        MKF_EndKata = true;
    } else {
        MKF_EndKata = false;
        MKF_SalinKata();
    }
}

void MKF_ADVKATA() {
    MKF_Ignore_Blank();
    if(IsEOPF()) {
        MKF_EndKata = true;
    } else {
        MKF_SalinKata();
    }
}

void MKF_SalinKata() {
    int i = 1;
    while(1) {
        MKF_CKata.TabKata[i] = GetFCC();
        ADVFILE();
        if(IsEOPF() || GetFCC() == BLANK) {
            break;
        } else {
            i++;
        }
    }
    MKF_CKata.Length = i;
}