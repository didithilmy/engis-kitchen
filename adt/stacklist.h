#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

/* MODUL STACK */
/* Deklarasi stack yang diimplementasi dengan list linier dengan representasi fisik pointer */

#define Nil NULL

/*  Definisi Type Stack  */
typedef char infotype;
typedef struct tElmtStack * address;
typedef struct tElmtStack {
	infotype Info;
	address Next;
} ElmtStack;
typedef struct {
	address TOP;
} Stack;

/***************************************************** 
TOP(S) = Nil adalah stack dengan elemen kosong
Definisi stack dengan representasi berkait :
  Jika S adalah Stack maka akses elemen :
    TOP(S) adalah alamat elemen TOP
    Info(P) untuk mengakses elemen info dengan alamat P 
    Next(P) untuk mengakses elemen next dengan alamat P 
******************************************************/
#define Top(S) (S).TOP
#define Next(P) (P)->Next
#define Info(P) (P)->Info

/***************/
/*  Prototype  */
/***************/

//Konstruktor/Kreator 
void CreateEmpty (Stack *S);
// I.S. Sembarang 
// F.S. Membuat sebuah stack S yang kosong 
// Ciri stack kosong : TOP bernilai Nil 

// Prototype manajemen memori
void Alokasi (address *P, infotype X);
// I.S. P Sembarang, X terdefinisi 
// F.S. Alamat P dialokasi, jika berhasil maka Info(P) = X dan Next(P) = Nil 
// P = Nil jika alokasi gagal 
void Dealokasi (address *P);
// I.S. P adalah hasil alokasi, P != Nil 
// F.S. Alamat P didealokasi, dikembalikan ke sistem 

// Predikat Untuk test keadaan KOLEKSI
boolean IsEmpty (Stack S);
// Mengirim true jika Stack kosong

// Operator Dasar Stack
void Push (Stack *S, infotype X);
// Menambahkan X sebagai elemen Stack S. 
// I.S. S mungkin kosong
// F.S. X menjadi TOP yang baru, jika alokasi elemen baru berhasil. 
// Jika alokasi gagal, S tetap. 
void Pop (Stack *S, infotype *X);
// Menghapus X dari Stack S. 
// I.S. S tidak kosong 
// F.S. X adalah nilai elemen TOP yang lama, elemen top yang lama didealokasi, 
// TOP(S) = Next(TOP(S)). 

#endif