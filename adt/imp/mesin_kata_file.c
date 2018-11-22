/**
 * Engi's Kitchen Expansion
 * Mesin Kata abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file mesin_kata_file.c
 */



#include "../mesin_kata_file.h"

boolean EndKata;
Kata CKata;

void MKF_Ignore_Blank() {
    while(GetFCC() == MKF_BLANK && (GetFCC() != MARK)) {
        ADVFILE();
    }
}

void MKF_STARTKATA(char *string) {
    STARTFILE(string);
    MKF_Ignore_Blank();

    if(IsEOPF()) {
        EndKata = true;
    } else {
        EndKata = false;
        MKF_SalinKata();
    }
}

void MKF_ADVKATA() {
    MKF_Ignore_Blank();
    if(IsEOPF()) {
        EndKata = true;
    } else {
        MKF_SalinKata();
    }
}

void MKF_SalinKata() {
    int i = 1;
    while(1) {
        CKata.TabKata[i] = GetFCC();
        ADVFILE();
        if(IsEOPF() || GetFCC() == MKF_BLANK) {
            break;
        } else {
            i++;
        }
    }
    CKata.Length = i;
}