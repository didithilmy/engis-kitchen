
#include "headers.h"
#include <stdlib.h>
#include <stdio.h>

int katatoint (Kata kata);

Kata nama;
int money, life, time;

typedef struct {
	int capacity;
	int patience;
} typequeue;

typequeue queue[10] ;

Kata stack[10];

typedef struct {
	int capacity;
	int isi;
	int patience;
	int nomeja;
	Kata * makanan;
} typemeja;

typemeja meja[10];

int i ;
void PrintKata(Kata kata);

int main () {

	STARTFILE("game.dat");
	while (!IsEOPF())
	{
		if (GetFCC() != ';')
		{
			if (GetFCC() == '(') {
				ADVFILE();
				MKF_SalinKata();
				nama = MKF_CKata;
				PrintKata(nama);
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
		ADVFILE();
		if (GetFCC() != ';') {
			if (GetFCC() == '(') {
				ADVFILE();
				MKF_SalinKata();
				money = katatoint(MKF_CKata);
				printf("money %d\n", money);
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
		ADVFILE();
		if (GetFCC() != ';') {
			if (GetFCC() == '(') {
				ADVFILE();
				MKF_SalinKata();
				life = katatoint(MKF_CKata);
				printf("life %d\n", life);
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
		ADVFILE();
		if (GetFCC() != ';') {
			if (GetFCC() == '(') {
				ADVFILE();
				MKF_SalinKata();
				time = katatoint(MKF_CKata);
				printf("time %d\n", time);
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
		ADVFILE();
		i=1;
		while (GetFCC() != ';') {
			if (GetFCC() == '(') {
				ADVFILE();
				MKF_SalinKata();
				queue[i].capacity= katatoint(MKF_CKata);
				MKF_ADVKATA();
				queue[i].patience = katatoint(MKF_CKata);

				printf("Queue %d: cap %d patience %d\n", i, queue[i].capacity, queue[i].patience);


				i++;
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
		ADVFILE();
		i=1;
		while (GetFCC() != ';') {
			if (GetFCC() == '(') {
				ADVFILE();
				MKF_SalinKata();
				stack[i] = (MKF_CKata);
				printf("Stack %d: ", i);
				PrintKata(stack[i]);
				i++;
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
		ADVFILE();
		i=1;
		while (GetFCC() != '.') {
			if (GetFCC() == '(') {
				ADVFILE();
				MKF_SalinKata();
				meja[i].capacity= katatoint(MKF_CKata);

				printf("Meja %d cap %d\n", i, meja[i].capacity);

                MKF_ADVKATA();
                meja[i].nomeja = katatoint(MKF_CKata);
                printf("Meja %d no meja %d\n", i, meja[i].nomeja);

            }

            ADVFILE();
            if (GetFCC() != ')'){
                MKF_SalinKata();
                meja[i].isi = katatoint(MKF_CKata);
                printf("Meja %d isi %d\n", i, meja[i].isi);

                MKF_ADVKATA();
                meja[i].patience = katatoint(MKF_CKata);
                printf("Meja %d patience %d\n", i, meja[i].patience);

                ADVFILE();
            }

			if (GetFCC() != ')') {
				MKF_SalinKata();
				meja[i].makanan = &MKF_CKata;

				printf("Meja %d order: ", i);
				PrintKata(MKF_CKata);
                ADVFILE();
            }

			if (GetFCC() == ')')
			{
				ADVFILE();
			}
			//printf("Meja %d: cap %d patience %d", i, meja[i].capacity, queue[i].patience);

			i++;
		}
	}

}



/**
 * Convert Kata to integer
 */
int katatoint (Kata kata) {
	int i;
	int total = 0;

	for (i=1;i<=kata.Length;i++) {
		total *= 10;
		total += kata.TabKata[i]-'0';
	}
	return total;
}


void PrintKata(Kata kata) {
	int i;
	for(i=1; i<=kata.Length; i++) {
		printf("%c", kata.TabKata[i]);
	}
	printf("\n");
}