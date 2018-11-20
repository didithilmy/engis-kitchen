/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#include "../matriks.h"
#include <stdio.h>
    
/* *** Konstruktor membentuk MATRIKS *** */

void MakeMATRIKS (int NB, int NK, MATRIKS * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M)=NB;
	NKolEff(*M)=NK;
	for (i=GetFirstIdxBrs(*M);i<=GetLastIdxBrs(*M);i++) {
		for (j=GetFirstIdxKol(*M);j<=GetLastIdxKol(*M);j++){
			ElmtFood(*M,i,j) = NULL;
			ElmtMeja(*M,i,j) = NULL;
			ElmtIsPhysical(*M,i,j) = false;
			ElmtType(*M,i,j) = M_KOSONG;
			}
	}
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terkecil M */
	return(BrsMin);
}

indeks GetFirstIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terkecil M */
	return(KolMin);
}

indeks GetLastIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terbesar M */
	return(BrsMin+NBrsEff(M)-1);
}
indeks GetLastIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terbesar M */
	return(KolMin+NKolEff(M)-1);
}

/* ********** KELOMPOK BACA/TULIS ********** */ 
void EditMATRIKS (int i, int j, MATRIKS * M, MatriksType TipeMatriks, Food * food, Meja * meja , boolean IsPhysical){
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
			ElmtFood(*M,i,j) = food;
			ElmtMeja(*M,i,j) = meja;
			ElmtIsPhysical(*M,i,j) = true;
			ElmtType(*M,i,j) = TipeMatriks;
}