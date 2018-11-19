#include "../queuelist.h"

void Alokasi (address *P, infotype X)
// I.S. P Sembarang, X terdefinisi 
// F.S. Alamat P dialokasi, jika berhasil maka Info(P) = X dan Next(P) = Nil 
// P = Nil jika alokasi gagal 
{
	/* ALGORITMA */
	(*P) = (address) malloc (sizeof(ElmtList));
	if ((*P) != Nil){
		Info(*P) = X;
		Next(*P) = Nil;
	}
}

void Dealokasi (address *P)
// I.S. P adalah hasil alokasi, P != Nil 
// F.S. Alamat P didealokasi, dikembalikan ke sistem 
{
	free(*P);
}

boolean IsEmpty (List Q)
{
	return(Head(Q)==Nil && Tail(Q)==Nil);
}

int NBElmt(List Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
{
	/* KAMUS */
	address P;
	int count;
	
	/* ALGORITMA */
	if (IsEmpty(Q)) {
		return 0;
	}
	else {
		P = Head(Q);
		count = 0;
		while (P != Nil){
			count = count + 1;
			P = Next(P);
		}
		return count;
	}
		
}

void CreateEmpty(List * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
{
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}

void Add (List * Q, infotype X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q jika alokasi berhasil; jika alokasi gagal Q tetap */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{ 	/* Kamus Lokal */
	address P;
	
	/* Algoritma */
	Alokasi(&P,X);
	if (P!=Nil) {
		if (IsEmpty(*Q)) {
			Head(*Q) = P;
			Tail(*Q) = P;
		} 
		else {
			Next(Tail(*Q)) = P;
			Tail(*Q) = P;
		}
	} /* else: alokasi gagal, Q tetap */
}

void Del(List * Q, infotype * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi elemen HEAD */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{ 	/* Kamus Lokal */
	address P;

	/* Algoritma */
	*X = InfoHead(*Q);
	P = Head(*Q);
	Head(*Q) = Next(Head(*Q));
	if (Head(*Q)==Nil) {
		Tail(*Q) = Nil;
	}
	Dealokasi(&P);
}