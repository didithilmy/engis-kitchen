
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

char * stack[10]; 

typedef struct {
		int capacity;
		int isi;
		int patience;
		Kata * makanan;
	} typemeja;
	
typemeja meja[10]; 

int i ; 

int main () { 
	
	STARTFILE("fileeks.txt"); 
	while (!IsEOPF())
    {
        if (GetFCC() != ';')
        {
			if (GetFCC() == '(') {
			ADVFILE(); 
			MKF_SalinKata();
			nama = MKF_CKata; 
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
			stack[i]= katatoint(MKF_CKata);
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
			}
			ADVFILE(); 
			if (GetFCC() != ')'){
			MKF_SalinKata();  
			meja[i].isi = katatoint(MKF_CKata);
			}
			ADVFILE(); 
			if (GetFCC() != ')') {
			MKF_SalinKata(); 
			meja[i].makanan = &MKF_CKata;  
			}
            ADVFILE(); 
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
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
