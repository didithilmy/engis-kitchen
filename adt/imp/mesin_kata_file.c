/**
 * Engi's Kitchen Expansion
 * Mesin Kata file abstraction
 *
 * @author Muhammad Yanza Hattari, NIM 18217043
 * @file mesin_kata_file.c
 */

#include "../mesin_kata_file.h"

boolean MKF_EndKata;
Kata MKF_CKata;

/*{ Mengabaikan satu atau beberapa BLANK }
{ I.S. : FCC sembarang }
{ F.S. : FCC = BLANK atau FCC = MARK }*/
void MKF_Ignore_Blank() {
    while(GetFCC() == BLANK && (GetFCC() != MKF_MARK)) {
        ADVFILE();
    }
}

/*{ I.S. : FCC sembarang, filename merupakan string nama file pita kata yang akan dibaca }
{ F.S. : EndKata = true, dan FCC = Mark; }
{        atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
         FCC karakter pertama sesudah karakter terakhir kata }*/
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

/*{ I.S. : EndKata = false; FCC adalah karakter sesudah karakter terakhir
         dari kata yg sudah diakuisisi }
{ F.S. : Jika FCC = MARK, maka EndKata = true
         atau EndKata = false, MKF_CKata adalah kata terakhir yang sudah diakuisisi;
         FCC karakter pertama sesudah karakter terakhir kata }*/
void MKF_ADVKATA() {
    MKF_Ignore_Blank();
    if(IsEOPF()) {
        MKF_EndKata = true;
    } else {
        MKF_SalinKata();
    }
}

/*{ Mengakuisisi kata, menyimpan dalam MKF_CKata }
{ I.S. : FCC adalah karakter pertama dari kata }
{ F.S. : MKF_CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
         NMax, sisa "kata" dibuang; FCC = BLANK atau FCC = MARK; FCC adalah
         karakter sesudah karakter terakhir yang diakuisisi }*/
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