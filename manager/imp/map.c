/**
 * Engi's Kitchen Expansion
 * Map manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @author Zalikha Adiera Gambetta, NIM 18217027
 * @file map.c
 */

#include "../map.h"
#include "../../eventbus/eventbus.h"
#include "../../adt/obj/meja.h"

int MAP_WIDTH, MAP_HEIGHT;

DataType get_map_width();
DataType get_map_height();
DataType get_map_array();
void onLoadGame();

TabMeja tabMeja;

FILE * filename;

/**
 * Initiate module
 */
void map_manager_init() {
    // TODO load map files
    
    // DIT GATAU YA BENER APA GA COMPILE SUCCESS TAPI HAHA

    // kamus
    int xdr, ydr, xm, ym, nm, km, xdd, ydd, xf, yf;
    char filename[30];
    Kata nf;
    
    // algoritma
    scanf("%s", filename);
    STARTFILE(filename);
    while (!IsEOPF())
    {
		if (GetFCC() != ';')
		{
			MAP_WIDTH = GetFCC(); // M
			ADVFILE();
			Ignore_Blank();
			MAP_HEIGHT = GetFCC(); // N
			ADVFILE();
		}
		if (GetFCC() != ';')
		{
			xdr = GetFCC(); // lokasi x pintu restoran
			ADVFILE();
			Ignore_Blank();
			ydr = GetFCC(); // lokasi y pintu restoran
			// TODO MATRIKS DOOR RESTORAN
			ADVFILE();
		}
		if (GetFCC() != ';')
		{
			if (GetFCC() == '(')
			{
				ADVFILE();
				xm = GetFCC(); // lokasi x meja ke-n
				ADVFILE();
				Ignore_Blank();
				ym = GetFCC(); // lokasi y meja ke-n
				ADVFILE();
				Ignore_Blank();
				nm = GetFCC(); // nomor meja
				ADVFILE();
				Ignore_Blank();
				km = GetFCC(); // isi per meja 2/4 orang
				AddMeja(&tabMeja, CreateMeja(MakePOINT(xm, ym), nm, km)); // TODO ADD MEJA
			}
			else if (GetFCC() == ')')
			{
				ADVFILE();
			}
			ADVFILE();
		}
		if (GetFCC() != ';')
		{
			xdd = GetFCC(); // lokasi x pintu dapur
			ADVFILE();
			Ignore_Blank();
			ydd = GetFCC(); // lokasi y pintu dapur
			// TODO MATRIKS DOOR DAPUR
			ADVFILE();
		}
		if (GetFCC() != ';')
		{
			if (GetFCC() == '(')
			{
				xf = GetFCC(); // lokasi x makanan
				ADVFILE();
				Ignore_Blank();
				yf = GetFCC(); // lokasi y makanan
				ADVFILE();
				Ignore_Blank();
				while (!EndKata)
				{
					// TODO BACA KATA HEHE BELOM :)
					nf = CKata;
					ADVKATA();
				}	
				// TODO ADD FOOD	
			}
			else if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
	}

	
    // TODO load TabMeja
    //AddMeja(&tabMeja, CreateMeja(MakePOINT(3, 3), 2, 1));
    //AddMeja(&tabMeja, CreateMeja(MakePOINT(7, 3), 4, 2));
    //AddMeja(&tabMeja, CreateMeja(MakePOINT(3, 7), 2, 3));
    //AddMeja(&tabMeja, CreateMeja(MakePOINT(7, 7), 4, 4));

    listen_getval_event(GET_MAP_WIDTH, &get_map_width);
    listen_getval_event(GET_MAP_HEIGHT, &get_map_height);
    listen_getval_event(GET_MAP_ARRAY, &get_map_array);
    listen_event(LOAD_GAME, &onLoadGame);

}

/**
 * Returns map width (cols)
 * @return cols
 */
DataType get_map_width() {
    DataType dt;
    dt.integer = MAP_WIDTH;

    return dt;
}

/**
 * Returns map height (rows)
 * @return rows
 */
DataType get_map_height() {
    DataType dt;
    dt.integer = MAP_HEIGHT;

    return dt;
}

/**
 * Returns array of map
 * @return rows
 */
DataType get_map_array() {
    DataType dt;
    dt.tabMeja = tabMeja;

    return dt;
}

/**
 * Called when the game is loaded
 */
void onLoadGame() {
    // TODO load map data and render tables
}
