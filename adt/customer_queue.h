/**
 * Customer queue abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#ifndef ENGIS_KITCHEN_CUSTOMER_QUEUE_H
#define ENGIS_KITCHEN_CUSTOMER_QUEUE_H

#include "listlinier.h"

#define CustomerInfo(P) *((Info(P)).custAddress)
#define CustomerAddress(P) Info(P).custAddress
#define CustomerInfoHead(Q) CustomerInfo(Head(Q))
#define CustomerInfoTail(Q) CustomerInfo(Tail(Q))

typedef List Queue;

void Add (Queue *Q, Customer *X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Del(Queue *Q, Customer **X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */


#endif //ENGIS_KITCHEN_CUSTOMER_QUEUE_H
