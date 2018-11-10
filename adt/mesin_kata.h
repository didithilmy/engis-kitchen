#ifndef PROJECT_MESIN_KATA_H
#define PROJECT_MESIN_KATA_H

#include "mesin_kar.h"

#define NMax 50
#define BLANK ' '
#define MARK 0

typedef struct {
    char TabKata[NMax+1];
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

//{ ***** Primitif-Primitif Mesin Kata ***** }
void Ignore_Blank();
/*{ Mengabaikan satu atau beberapa BLANK }
{ I.S. : CC sembarang }
{ F.S. : CC ? BLANK atau CC = MARK }*/
void STARTKATA(char* string);
/*{ I.S. : CC sembarang, filename merupakan string nama file pita kata yang akan dibaca }
{ F.S. : EndKata = true, dan CC = Mark; }
{        atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
         CC karakter pertama sesudah karakter terakhir kata }*/
void ADVKATA();
/*{ I.S. : EndKata = false; CC adalah karakter sesudah karakter terakhir
         dari kata yg sudah diakuisisi }
{ F.S. : Jika CC = MARK, maka EndKata = true
         atau EndKata = false, CKata adalah kata terakhir yang sudah diakuisisi;
         CC karakter pertama sesudah karakter terakhir kata }*/
void SalinKata();
/*{ Mengakuisisi kata, menyimpan dalam CKata }
{ I.S. : CC adalah karakter pertama dari kata }
{ F.S. : CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
         NMax, sisa "kata" dibuang; CC = BLANK atau CC = MARK; CC adalah
         karakter sesudah karakter terakhir yang diakuisisi }*/

/**
 * Build Kata from string
 * @param str string
 * @return Kata
 */
Kata BuildKata(char *str);

/**
 * Compares two Katas
 * @param k1 first Kata
 * @param k2 second Kata
 * @return is kata identical
 */
boolean CompareKata(Kata k1, Kata k2, boolean caseSensitive);

#endif