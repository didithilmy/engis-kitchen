/**
 * Engi's Kitchen Expansion
 * Customer queue abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#include "../customer_queue.h"

void Add (Queue *Q, Customer *X) {
    infotype data;
    data.custAddress = X;

    InsVLast(Q, data);
}
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Del(Queue *Q, Customer **X) {
    infotype data;
    DelVFirst(Q, &data);

    *X = data.custAddress;
}
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */