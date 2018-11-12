/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#include "matriks.h"
#include <stdio.h>
    
/* *** Konstruktor membentuk MATRIKS *** */

void MakeMATRIKS (int NB, int NK, MATRIKS * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M)=NB;
	NKolEff(*M)=NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
	return(i<=BrsMax && i>=BrsMin && j>=KolMin && j<=KolMax);
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
boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
	return(i>=GetFirstIdxBrs(M)&&i<=GetLastIdxBrs(M)&&j>=GetFirstIdxKol(M)&&j<=GetLastIdxKol(M));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i){
/* Mengirimkan elemen M(i,i) */
	return(Elmt(M,i,i));
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
/* Melakukan assignment MHsl  MIn */
	indeks i,j;
	MakeMATRIKS(NBrsEff(MIn),NKolEff(MIn),MHsl);
	for (i=GetFirstIdxBrs(MIn);i<=GetLastIdxBrs(MIn);i++)
		for (j=GetFirstIdxKol(MIn);j<=GetLastIdxKol(MIn);j++)
			Elmt(*MHsl,i,j)=Elmt(MIn,i,j);
}	

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK){
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
	indeks i,j;
	MakeMATRIKS(NB,NK,M);
	for (i=GetFirstIdxBrs(*M);i<=GetLastIdxBrs(*M);i++)
		for (j=GetFirstIdxKol(*M);j<=GetLastIdxKol(*M);j++){
			scanf("%d",&Elmt(*M,i,j));
			}
}
void TulisMATRIKS (MATRIKS M){
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
	indeks i,j;
	for (i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++){
		for (j=GetFirstIdxKol(M);j<GetLastIdxKol(M);j++)
			printf("%d ",Elmt(M,i,j));
		printf("%d",Elmt(M,i,j));
		if (i<GetLastIdxBrs(M))
			printf("\n");
	}
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
	indeks i,j;
	MATRIKS temp;
	MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&temp);
	for (i=GetFirstIdxBrs(M1);i<=GetLastIdxBrs(M1);i++)
		for (j=GetFirstIdxKol(M1);j<=GetLastIdxKol(M1);j++)
			Elmt(temp,i,j)=Elmt(M1,i,j)+Elmt(M2,i,j);
	return temp;
}

MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : M berukuran sama dengan M */
	indeks i,j;
	MATRIKS temp;
	MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&temp);
	for (i=GetFirstIdxBrs(M1);i<=GetLastIdxBrs(M1);i++)
		for (j=GetFirstIdxKol(M1);j<=GetLastIdxKol(M1);j++)
			Elmt(temp,i,j)=Elmt(M1,i,j)-Elmt(M2,i,j);
	return temp;
}
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
	indeks i,j,y;
	ElType count;
	MATRIKS temp;
	MakeMATRIKS(NBrsEff(M1),NKolEff(M2),&temp);
	for (i=GetFirstIdxBrs(temp);i<=GetLastIdxBrs(temp);i++)
		for (j=GetFirstIdxKol(temp);j<=GetLastIdxKol(temp);j++){
			count=0;
			for (y=GetFirstIdxKol(temp);y<=GetLastIdxKol(M1);y++)
				count+=Elmt(M1,i,y)*Elmt(M2,y,j);
			Elmt(temp,i,j)=count;
		}
	return temp;
}
MATRIKS KaliKons (MATRIKS M, ElType X){
/* Mengirim hasil perkalian setiap elemen M dengan X */
	indeks i,j;
	MATRIKS temp;
	MakeMATRIKS(NBrsEff(M),NKolEff(M),&temp);
	for (i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++)
		for (j=GetFirstIdxKol(M);j<=GetLastIdxKol(M);j++)
			Elmt(temp,i,j)=Elmt(M,i,j)*X;
	return temp;
}
void PKaliKons (MATRIKS * M, ElType K){
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
	*M = KaliKons(*M,K);
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
	indeks i,j;
	if (EQSize(M1,M2)){
		i= GetFirstIdxBrs(M1);j=GetFirstIdxKol(M1);
		while (Elmt(M1,i,j)==Elmt(M2,i,j) && i<=GetLastIdxBrs(M1)){
			j=GetFirstIdxKol(M1);
			while (Elmt(M1,i,j)==Elmt(M2,i,j) && j<=GetLastIdxKol(M1))
				j=j+1;
			if (Elmt(M1,i,j)==Elmt(M2,i,j))
				i=i+1;
		}
		return (i>GetLastIdxBrs(M1)&&j>GetLastIdxKol(M1));
	}
	else
		return false;
}
boolean NEQ (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika M1 tidak sama dengan M2 */
	return (!EQ(M1,M2));
}
boolean EQSize (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
	return(NBrsEff(M1)==NBrsEff(M2)&&NKolEff(M1)==NKolEff(M2));
}
/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M){
/* Mengirimkan banyaknya elemen M */
	return(NBrsEff(M)*NKolEff(M));
}