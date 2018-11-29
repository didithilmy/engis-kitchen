/**
 * Order list abstraction
 *
 * Header file template provided by ITB, with modifications
 */


#ifndef ENGIS_KITCHEN_ORDER_LIST_H
#define ENGIS_KITCHEN_ORDER_LIST_H

#include "listlinier.h"

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
address InsOrderFirst (List *L, Order *X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
address InsOrderLast (List *L, Order *X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelOrderFirst (List *L, Order **X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelOrderLast (List *L, Order **X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

address SearchOrderPrec (List L, Order *order);


#endif //ENGIS_KITCHEN_ORDER_LIST_H
