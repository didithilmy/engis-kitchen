/**
 * Engi's Kitchen Expansion
 * Mesin Karakter file abstraction
 *
 * @author Muhammad Yanza Hattari, NIM 18217043
 * @file mesin_kar_file.c
 */

#include "../mesin_kar_file.h"

char FCC;
boolean EOPF;

static FILE *pita;
static int retval;

void STARTFILE(char* filename)
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
Karakter pertama yang ada pada pita posisinya adalah pada jendela.
filename merupakan nama file yang berisi pita karakter
I.S. : sembarang
F.S. : CC adalah karakter pertama pada pita

Jika CC != MARK maka EOP akan padam (false)
Jika CC = MARK maka EOP akan menyala (true) */
{
pita = fopen(filename,"r");
ADVFILE();
}

void ADVFILE()
/* Pita dimajukan satu karakter.
I.S. : Karakter pada jendela = CC, CC != MARK
F.S. : CC adalah karakter berikutnya dari CC yang lama,

CC mungkin = MARK
Jika CC = MARK maka EOP akan menyala (true) */
{
retval = fscanf(pita,"%c",&FCC);
if (IsEOPF())
	{
	fclose(pita);
	}
}

char GetFCC()
/* Mengembalikan karakter yang sedang terbaca di jendela.
I.S. : Karakter pada jendela = CC, CC != MARK
F.S. : mengembalikan karakter yang sedang terbaca di jendela
*/
{
	return (FCC);
}


boolean IsEOPF()
/* Mengecek apakah pita telah selesai dibaca
I.S. : Pita telah terbaca
F.S. : Menegmbalikan true jika pita telah selesai terbaca, false jika sebaliknya
*/
{
	return(FCC==MKF_MARK);
}
	