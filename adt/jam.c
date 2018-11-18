/* File: jam.h */

/* Definisi ADT JAM */
#include <stdio.h>
#include "jam.h"
/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S){
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
	return (H<24 && H>=0 && M < 60 && M>=0 && S<60 && S>=0);
	}
/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS){
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
	JAM temp;
	Hour(temp) = HH;
	Minute(temp) = MM;
	Second(temp) = SS;
	return (temp);
}
/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J){
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
   int a,b,c;
   do{
	scanf("%d %d %d",&a,&b,&c);
	if (IsJAMValid(a,b,c)==false)
		printf("Jam tidak valid\n");
   }while (IsJAMValid(a,b,c)==false);
   *J = MakeJAM(a,b,c);
  }
void TulisJAM (JAM J){
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
   printf("%d:%d:%d",Hour(J),Minute(J),Second(J));
}
/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J){
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
	return(3600*Hour(J)+60*Minute(J)+Second(J));
}
JAM DetikToJAM (long N){
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */
	long N1;
	N1 = N % 86400;
	return (MakeJAM((N1 / 3600),((N1 % 3600) /60),((N1%3600) %60)));
   }
/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2){
/* Mengirimkan true jika J1=J2, false jika tidak */
	return (JAMToDetik(J1)==JAMToDetik(J2));
}
boolean JNEQ (JAM J1, JAM J2){
/* Mengirimkan true jika J1 tidak sama dengan J2 */
	return(!(JEQ(J1,J2)));
}
boolean JLT (JAM J1, JAM J2){
/* Mengirimkan true jika J1<J2, false jika tidak */
	return(JAMToDetik(J1)<JAMToDetik(J2));
}
boolean JGT (JAM J1, JAM J2){
/* Mengirimkan true jika J1>J2, false jika tidak */
	return(JAMToDetik(J1)>JAMToDetik(J2));
}
/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J){
/* Mengirim 1 detik setelah J dalam bentuk JAM */
	return (DetikToJAM(JAMToDetik(J)+1));
}
JAM NextNDetik (JAM J, int N){
/* Mengirim N detik setelah J dalam bentuk JAM */
	return (DetikToJAM(JAMToDetik(J)+N));
}
JAM PrevDetik (JAM J){
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
	long temp;
	temp=JAMToDetik(J);
	if (temp>(1-1))
		return(DetikToJAM(temp-1));
	else
		return(DetikToJAM(temp-1+86400));
}
JAM PrevNDetik (JAM J, int N){
/* Mengirim N detik sebelum J dalam bentuk JAM */
		long temp,tempn;
	temp=JAMToDetik(J);
	tempn=N%86400;
	if (temp>(N-1))
		return(DetikToJAM(temp-N));
	else
		return(DetikToJAM(temp-N+86400));
}
/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh){
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
	long temp;
	temp =JAMToDetik(JAkh);
	if (JAMToDetik(JAw) > temp)
		temp += 86400;
	return(temp-JAMToDetik(JAw));
}
