/**
 * Engi's Kitchen Expansion
 * Mesin Karakter file abstraction
 *
 * Header file template provided by ITB
 * @file mesin_kar_file.c
 */

#ifndef __MESIN_KAR_FILE__
#define __MESIN_KAR_FILE__

#include "boolean.h"
#include <stdio.h>
#define MKF_MARK '.'

/* State Mesin */
extern char FCC;
extern boolean EOPF;

/*
  pada implementasi (mesin_kar.c), perlu ditambahkan variabel static 
  global yang menyimpan pembacaan file pita.
*/

void STARTFILE(char* filename);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
Karakter pertama yang ada pada pita posisinya adalah pada jendela.
filename merupakan nama file yang berisi pita karakter
I.S. : sembarang
F.S. : CC adalah karakter pertama pada pita

Jika CC != MARK maka EOP akan padam (false)
Jika CC = MARK maka EOP akan menyala (true) */

void ADVFILE();
/* Pita dimajukan satu karakter.
I.S. : Karakter pada jendela = CC, CC != MARK
F.S. : CC adalah karakter berikutnya dari CC yang lama,

CC mungkin = MARK
Jika CC = MARK maka EOP akan menyala (true) */

char GetFCC();
/* Mengembalikan karakter yang sedang terbaca di jendela.
I.S. : Karakter pada jendela = CC, CC != MARK
F.S. : mengembalikan karakter yang sedang terbaca di jendela
*/

boolean IsEOPF();
/* Mengecek apakah pita telah selesai dibaca
I.S. : Pita telah terbaca
F.S. : Menegmbalikan true jika pita telah selesai terbaca, false jika sebaliknya
*/

#endif
