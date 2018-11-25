/**
 * Order list abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @author Muhammad Yanza Hattari, NIM 18217043
 */


#include "../order_list.h"

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
address InsOrderFirst (List *L, Order X) {
    infotype data;
    data.order = X;
	address add = Alokasi(data);
    InsertFirst(L, add);
	return add;
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */


address InsOrderLast (List *L, Order X) {
    infotype data;
    data.order = X;

	address add = Alokasi(data);
	InsertLast(L,add);
	return add;
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */


/*** PENGHAPUSAN ELEMEN ***/
void DelOrderFirst (List *L, Order *X) {
    infotype data;
    DelVFirst(L, &data);

    *X = data.order;
}
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void DelOrderLast (List *L, Order *X) {
    infotype data;
    DelVLast(L, &data);

    *X = data.order;
}
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

