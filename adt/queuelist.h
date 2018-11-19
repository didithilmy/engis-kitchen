/* File : queuelist.h */
#ifndef _QUEUELIST_H
#define _QUEUELIST_H
#include "boolean.h"
#include <stdlib.h>
#define Nil NULL

/* Deklarasi infotype */
typedef int infotype;
/* List dengan representasi berkait dengan pointer */
typedef struct tElmtList * address;
typedef struct tElmtList {
	infotype Info;
	address Next;
} ElmtList;
typedef struct {
	address HEAD; 
	address TAIL;
} List;

#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).HEAD->Info
#define InfoTail(Q) (Q).TAIL->Info
#define Next(P) (P)->Next
#define Info(P) (P)->Info

/* Prototype manajemen memori */
void Alokasi (address *P, infotype X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan Next(P)=Nil */
/* P=Nil jika alokasi gagal */

void Dealokasi (address *P);
/* I.S. P adalah hasil alokasi, P <> Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */

/* Selektor */
boolean IsEmpty (List Q);
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
int NBElmt(List Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */

/*** Kreator ***/
void CreateEmpty(List * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void Add (List * Q, infotype X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Del(List * Q, infotype * X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */

#endif