#include "stacklist.h"

//Konstruktor/Kreator 
void CreateEmpty (Stack *S)
// I.S. Sembarang 
// F.S. Membuat sebuah stack S yang kosong 
// Ciri stack kosong : Top bernilai Nil 
{
	Top(*S) = Nil;
}

// Prototype manajemen memori
void Alokasi (address *P, infotype X)
// I.S. P Sembarang, X terdefinisi 
// F.S. Alamat P dialokasi, jika berhasil maka Info(P) = X dan Next(P) = Nil 
// P = Nil jika alokasi gagal 
{
	/* ALGORITMA */
	(*P) = (address) malloc (sizeof(ElmtStack));
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

// Predikat Untuk test keadaan KOLEKSI
boolean IsEmpty (Stack S)
// Mengirim true jika Stack kosong
{
	return (Top(S) == Nil);
}

// Operator Dasar Stack
void Push (Stack *S, infotype X)
// Menambahkan X sebagai elemen Stack S. 
// I.S. S mungkin kosong
// F.S. X menjadi Top yang baru, jika alokasi elemen baru berhasil. 
// Jika alokasi gagal, S tetap. 
{
	/* KAMUS */
	address P;
	/*Algoritma*/
	
	Alokasi(&P,X);
	if (P != Nil){
		Next(P) = Top(*S);
		Top(*S) = P;
	}
}

void Pop (Stack *S, infotype *X)
// Menghapus X dari Stack S. 
// I.S. S tidak kosong 
// F.S. X adalah nilai elemen Top yang lama, elemen Top yang lama didealokasi, 
// Top(S) = Next(Top(S)). 
{
	/* KAMUS */
	address P;
	/* ALGORITMA */
	P = Top(*S);
	Top(*S) = Next(Top(*S));
	Next(P) = Nil;
	*X = Info(P);
	Dealokasi(&P);
}