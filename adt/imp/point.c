/**
 * Engi's Kitchen Expansion
 * Point abstraction
 *
 * @author Claudia Renata Maharani D., NIM 18217048
 * @file point.c
 */


#include "../point.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y){
/* Membentuk sebuah POINT dari komponen-komponennya */
	POINT temp;
	Absis(temp)=X;
	Ordinat(temp)=Y;
	return temp;
}