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


/*{ Mengabaikan satu atau beberapa BLANK }
    { I.S. : CC sembarang }
    { F.S. : CC = BLANK atau CC = MARK }*/
void Ignore_Blank() {

    while(GetCC() == BLANK && (GetCC() != MARK)) {
        ADV();
    }
}

/*{ I.S. : CC sembarang, filename merupakan string nama file pita kata yang akan dibaca }
{ F.S. : EndKata = true, dan CC = Mark; }
{        atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
         CC karakter pertama sesudah karakter terakhir kata }*/
void STARTKATA(char *string) {

    START(string);
    Ignore_Blank();

    if(IsEOP()) {
        EndKata = true;
        CKata.Length = 0;   // This line is required to clear the CKata buffer if the ribbon is empty
    } else {
        EndKata = false;
        SalinKata();
    }
}

/*{ I.S. : EndKata = false; CC adalah karakter sesudah karakter terakhir
         dari kata yg sudah diakuisisi }
{ F.S. : Jika CC = MARK, maka EndKata = true
         atau EndKata = false, CKata adalah kata terakhir yang sudah diakuisisi;
         CC karakter pertama sesudah karakter terakhir kata }*/
void ADVKATA() {
    Ignore_Blank();
    if(IsEOP()) {
        EndKata = true;
    } else {
        SalinKata();
    }
}

/*{ Mengakuisisi kata, menyimpan dalam CKata }
{ I.S. : CC adalah karakter pertama dari kata }
{ F.S. : CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
         NMax, sisa "kata" dibuang; CC = BLANK atau CC = MARK; CC adalah
         karakter sesudah karakter terakhir yang diakuisisi }*/
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


/**
 * Build Kata from string
 * @param str string
 * @return Kata
 */
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


/**
 * Convert Kata to integer
 */
int KataToInt (Kata kata) {
    int i;
    int total = 0;

    for (i=1;i<=kata.Length;i++) {
        total *= 10;
        total += kata.TabKata[i]-'0';
    }
    return total;
}