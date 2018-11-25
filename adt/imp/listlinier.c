/**
 * Order list abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @author Muhammad Yanza Hattari, NIM 18217043
 */


/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

#include "../listlinier.h"
#include <stdlib.h>
#include <stdio.h>

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last, maka Next(Last)=Nil */

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
bool IsEmpty (List L)
/* Mengirim true jika list kosong */
{
	return (First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
	First(*L) = Nil;
    Last(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	/* KAMUS */
	address P;
	
	/* ALGORITMA */
	P = (address) malloc (sizeof(ElmtList));
	if (P != Nil){
		Info(P) = X;
		Next(P) = Nil;
	}
	return P;
}
void Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
//address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
/*{
	// KAMUS
	address P;
	bool Found;
	
	// ALGORITMA
	P = First(L);
	Found = false;
	while ((P != Nil) && (!Found)){
		if (Info(P) == X){
			Found = true;
		} else{
			P = Next(P);
		}
	}
	if (Found){
		return P;
	} else{
		return Nil;
	}
}*/

bool FSearch (List L, address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
	/* KAMUS */
	address P1;
	bool Found;
	
	/* ALGORITMA */
	P1 = First(L);
	Found = false;
	while ((P1 != Nil) && (!Found)) {
		if (P == P1) {
			Found = true;
		} else {
			P1 = Next(P1);
		}
	}
	return(Found);	
}

//address SearchPrec (List L, infotype X)
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
/*{
	// KAMUS
	address Prec, P;
	bool Found;
	
	// ALGORITMA
	P = First(L);
	Found = false;
	if (Info(P)==X){
		return (Nil);
	} else {
		while ((Next(P)!=Nil)&&(!Found)) {
			Prec = P;
			P = Next(P);
			if (Info(P)==X) {
				Found = true;
			}
		}
		if (Found) {
			return (Prec);
		} else {
			return (Nil);
		}
	}				
}*/


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	/* KAMUS */
	address P;
	
	/* ALGORTIMA */
	P = Alokasi(X);
	if (P != Nil){
		InsertFirst(L, P);
	}
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	/* KAMUS */
	address P;
	/* ALGORTIMA */
	P = Alokasi(X);
	if (P != Nil){
		InsertLast(L, P);
	}
}
	
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	/* KAMUS */
	address P;

	/* ALGORITMA */
	DelFirst(L, &P);
	*X = Info(P);
	Dealokasi(&P);
}
void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    // TODO cek dong pls -didit
	/* KAMUS */
	//address Last, PrecLast;
	/* ALGORITMA */
	/*Last = First(*L);
	PrecLast = Nil;
	while (Next(Last) != Nil){
		PrecLast = Last;
		Last = Next(Last);
	}
	*X = Info(Last);
	if (PrecLast == Nil){
		First(*L) = Nil;
	} else{
		Next(PrecLast) = Nil;
	}*/

    address P;
    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	Next(P) = First(*L);
	First(*L) = P;

    // Check if Next(P) is Nil. If it is, P must be the last element
    if(Next(P) == Nil) {
        Last(*L) = P;
    }
}
void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next(P) = Next(Prec);
	Next(Prec) = P;

    // Check if Next(P) is Nil. If it is, P must be the last element
    if(Next(P) == Nil) {
        Last(*L) = P;
    }
}
void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	/* KAMUS */
	address Last;
	/* ALGORITMA */
	if (IsEmpty(*L)){
		InsertFirst(L, P);
	} else{
		InsertAfter(L, P, Last(*L));
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P = First(*L);
	First(*L) = Next(First(*L));
	Next(*P) = Nil;

    // Check if First(*L) is Nil. If it is, L must be empty
    if(First(*L) == Nil) {
        Last(*L) = Nil;
    }
}
//void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
/*{
	// KAMUS
	address P, Prec;
	// ALGORITMA
	if (X == Info(First(*L))){
		P = First(*L);
		DelFirst(L, &P);
	} else{
		Prec = First(*L);
		while ((Next(Prec) != Nil) && (Info(Next(Prec)) != X)){
			Prec = Next(Prec);
		}
		if (Next(Prec) != Nil){
			P = Next(Prec);
			Next(Prec) = Next(Next(Prec));
			Next(P) = Nil;
			Dealokasi(&P);
		}
	}
}	*/
void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
	/* KAMUS */
	address Last, PrecLast;
	/* ALGORRITMA */
	Last = First(*L);
	PrecLast = Nil;
	while (Next(Last) != Nil){
		PrecLast = Last;
		Last = Next(Last);
	}
	*P = Last;
	if (PrecLast == Nil){
		First(*L) = Nil;
        Last(*L) = Nil;
	} else{
		Next(PrecLast) = Nil;
        Last(*L) = PrecLast;
	}
}
void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel = Next(Prec);
	Next(Prec) = Next(Next(Prec));
	Next(*Pdel) = Nil;

    // Check if Next(Prec) is Nil. If it is, Prec must be the last element
    if(Next(Prec) == Nil) {
        Last(*L) = Prec;
    }
}

int NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
	/* KAMUS */
	address P;
	int count;
	
	/* ALGORITMA */
	P = First(L);
	count = 0;
	while (P != Nil){
		count = count + 1;
		P = Next(P);
	}
	return count;
}