//
// Created by didit on 23/11/2018.
//

#include "../adt/mesin_kata_file.h"
int MAP_WIDTH, MAP_HEIGHT;

int main() {
    // kamus
    int xdr, ydr, xm, ym, nm, km, xdd, ydd, xf, yf;
    char filename[30] = "map.dat";
    Kata nf;

    //algoritma
    STARTFILE(filename);
    while (!IsEOPF())
    {
        printf("Char1 %c", GetFCC());

        if (GetFCC() != ';')
        {
            printf("Char2 %c", GetFCC());
            MAP_WIDTH = GetFCC(); // M
            ADVFILE();
            MKF_Ignore_Blank();
            MAP_HEIGHT = GetFCC(); // N
            ADVFILE();
        }
        else {
            ADVFILE();
        }
        ADVFILE();
        if (GetFCC() != ';')
        {
            printf("Char3 %c", GetFCC());

            xdr = GetFCC(); // lokasi x pintu restoran
            ADVFILE();
            MKF_Ignore_Blank();
            ydr = GetFCC(); // lokasi y pintu restoran
            // TODO MATRIKS DOOR RESTORAN
            ADVFILE();
        }
        else {
            ADVFILE();
        }
        ADVFILE();
        while (GetFCC() != ';')
        {
            printf("Char4 %c", GetFCC());

            if (GetFCC() == '(')
            {
                printf("Char5 %c", GetFCC());

                ADVFILE();
                xm = GetFCC(); // lokasi x meja ke-n
                ADVFILE();
                MKF_Ignore_Blank();
                ym = GetFCC(); // lokasi y meja ke-n
                ADVFILE();
                MKF_Ignore_Blank();
                nm = GetFCC(); // nomor meja
                ADVFILE();
                MKF_Ignore_Blank();
                km = GetFCC(); // isi per meja 2/4 orang
                //registerMeja(CreateMeja(MakePOINT(xm, ym), nm, km)); // TODO ADD MEJA
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                printf("Char6 %c", GetFCC());

                ADVFILE();
            }
        }
        ADVFILE();
        if (GetFCC() != ';')
        {
            printf("Char7 %c", GetFCC());

            xdd = GetFCC(); // lokasi x pintu dapur
            ADVFILE();
            MKF_Ignore_Blank();
            ydd = GetFCC(); // lokasi y pintu dapur
            // TODO MATRIKS DOOR DAPUR
            ADVFILE();
        }
        else {
            ADVFILE();
        }
        ADVFILE();

        while (GetFCC() != MKF_MARK)
        {
            printf("Char8 %c", GetFCC());

            if (GetFCC() == '(')
            {
                ADVFILE();
                xf = GetFCC(); // lokasi x makanan
                ADVFILE();
                MKF_Ignore_Blank();
                yf = GetFCC(); // lokasi y makanan
                ADVFILE();
                MKF_Ignore_Blank();
                MKF_SalinKata();
                nf = MKF_CKata;
                // TODO ADD FOOD
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
    }

}