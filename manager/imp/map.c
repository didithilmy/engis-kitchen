/**
 * Engi's Kitchen Expansion
 * Map manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @author Zalikha Adiera Gambetta, NIM 18217027
 * @author Muhammad Yanza Hattari NIM 18217043
 * @file map.c
 */

#include <stdlib.h>
#include "../map.h"
#include "../../eventbus/eventbus.h"
#include "../../adt/headers.h"
#include "../../adt/point.h"


DataType get_map_width();
DataType get_map_height();
DataType get_tab_meja();
DataType get_tab_food();
DataType get_resto_matrix();
DataType get_kitchen_matrix();
void onLoadGame();
void registerMeja(Meja meja);
void registerFood(Food food);
boolean isFoodPointerLegal(int x, int y);

int MAP_WIDTH, MAP_HEIGHT;

TabMeja tabMeja;
TabFood tabFood;
MATRIKS restoMatrix, kitchenMatix;

/**
 * Initiate module
 */
void map_manager_init() {
    // TODO load map files
    
    // DIT GATAU YA BENER APA GA COMPILE SUCCESS TAPI HAHA

    // kamus
    int xdr, ydr, xm, ym, nm, km, xdd, ydd, xf, yf;
    char filename[30] = "map.dat";
    Kata nf;
    
    //algoritma
    STARTFILE(filename);
    while (!IsEOPF())
    {
		if (GetFCC() != ';')
		{
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
			if (GetFCC() == '(')
			{
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
				registerMeja(CreateMeja(MakePOINT(xm, ym), nm, km)); // TODO ADD MEJA
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
		ADVFILE();
		if (GetFCC() != ';')
		{
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
		
		while (GetFCC() != MARK)
		{
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
				nf = CKata;
				// TODO ADD FOOD	
			}
			ADVFILE();
			if (GetFCC() == ')')
			{
				ADVFILE();
			}
		}
	}

	
    MAP_WIDTH = 9;
    MAP_HEIGHT = 9;

    // Initialize arrays and variables
    InitTabFood(&tabFood);
    InitTabMeja(&tabMeja);
    MakeMATRIKS(MAP_HEIGHT, MAP_WIDTH, &restoMatrix);
    MakeMATRIKS(MAP_HEIGHT, MAP_WIDTH, &kitchenMatix);

    // TODO load TabMeja
    registerMeja(CreateMeja(MakePOINT(3, 3), 2, 1));
    registerMeja(CreateMeja(MakePOINT(7, 3), 4, 2));
    registerMeja(CreateMeja(MakePOINT(3, 7), 2, 3));
    registerMeja(CreateMeja(MakePOINT(7, 7), 4, 4));

    // TODO load TabFood
    registerFood(CreateFood(MakePOINT(4, 1), BuildKata("Bebek")));
    registerFood(CreateFood(MakePOINT(4, 2), BuildKata("Sapi")));
    registerFood(CreateFood(MakePOINT(4, 3), BuildKata("Ayam")));

    listen_getval_event(GET_MAP_WIDTH, &get_map_width);
    listen_getval_event(GET_MAP_HEIGHT, &get_map_height);
    listen_getval_event(GET_TAB_MEJA, &get_tab_meja);
    listen_getval_event(GET_TAB_FOOD, &get_tab_food);
    listen_getval_event(GET_RESTO_MATRIX, &get_resto_matrix);
    listen_getval_event(GET_KITCHEN_MATRIX, &get_kitchen_matrix);
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
DataType get_tab_meja() {
    DataType dt;
    dt.tabMeja = tabMeja;

    return dt;
}


/**
 * Returns array of food
 * @return rows
 */
DataType get_tab_food() {
    DataType dt;
    dt.tabFood = tabFood;

    return dt;
}

/**
 * Returns resto matrix
 * @return rows
 */
DataType get_resto_matrix() {
    DataType dt;
    dt.matriks = restoMatrix;

    return dt;
}

/**
 * Returns kitchen matrix
 * @return rows
 */
DataType get_kitchen_matrix() {
    DataType dt;
    dt.matriks = kitchenMatix;

    return dt;
}

/**
 * Called when the game is loaded
 */
void onLoadGame() {
    // TODO load map data and render tables
}

/**
 * Declare new Meja
 * @param meja meja
 */
void registerMeja(Meja meja) {
    // Check if Meja is NOT in the edge of the map
    if(meja.coordinate.X > 1 && meja.coordinate.Y > 1 && meja.coordinate.X < MAP_WIDTH && meja.coordinate.Y < MAP_HEIGHT) {

        // Add Meja to TabMeja
        Meja *ptr_meja = AddMeja(&tabMeja, meja);

        // Create Matrix elements
        // Centerpiece of Meja
        EditMATRIKS(meja.coordinate.Y, meja.coordinate.X, &restoMatrix, M_MEJA, Nil, ptr_meja, true);

        // Left and right chairs of Meja
        EditMATRIKS(meja.coordinate.Y, meja.coordinate.X-1, &restoMatrix, M_MEJA, Nil, ptr_meja, true);
        EditMATRIKS(meja.coordinate.Y, meja.coordinate.X+1, &restoMatrix, M_MEJA, Nil, ptr_meja, true);

        // Left side of the Left chair and the right side of the right chair
        if(meja.coordinate.X > 2) EditMATRIKS(meja.coordinate.Y, meja.coordinate.X-2, &restoMatrix, M_MEJA, Nil, ptr_meja, false);
        if(meja.coordinate.X < MAP_WIDTH - 1) EditMATRIKS(meja.coordinate.Y, meja.coordinate.X+2, &restoMatrix, M_MEJA, Nil, ptr_meja, false);

        // Above the left and right chairs
        EditMATRIKS(meja.coordinate.Y-1, meja.coordinate.X-1, &restoMatrix, M_MEJA, Nil, ptr_meja, false);
        EditMATRIKS(meja.coordinate.Y-1, meja.coordinate.X+1, &restoMatrix, M_MEJA, Nil, ptr_meja, false);

        // Below the left and right chairs
        EditMATRIKS(meja.coordinate.Y+1, meja.coordinate.X-1, &restoMatrix, M_MEJA, Nil, ptr_meja, false);
        EditMATRIKS(meja.coordinate.Y+1, meja.coordinate.X+1, &restoMatrix, M_MEJA, Nil, ptr_meja, false);

        // If the capacity is 4, add top and bottom chairs as well
        if(meja.capacity == 4) {
            EditMATRIKS(meja.coordinate.Y+1, meja.coordinate.X, &restoMatrix, M_MEJA, Nil, ptr_meja, true);
            EditMATRIKS(meja.coordinate.Y-1, meja.coordinate.X, &restoMatrix, M_MEJA, Nil, ptr_meja, true);

            // Above and below the top and bottom chairs
            if(meja.coordinate.Y > 2) EditMATRIKS(meja.coordinate.Y-2, meja.coordinate.X, &restoMatrix, M_MEJA, Nil, ptr_meja, false);
            if(meja.coordinate.Y < MAP_HEIGHT - 1) EditMATRIKS(meja.coordinate.Y+2, meja.coordinate.X, &restoMatrix, M_MEJA, Nil, ptr_meja, false);
        } else {
            // Above and below the table
            EditMATRIKS(meja.coordinate.Y+1, meja.coordinate.X, &restoMatrix, M_MEJA, Nil, ptr_meja, false);
            EditMATRIKS(meja.coordinate.Y-1, meja.coordinate.X, &restoMatrix, M_MEJA, Nil, ptr_meja, false);
        }
    }
}

/**
 * Declare a new Food
 * @param food food
 */
void registerFood(Food food) {
    Food *ptr_food = AddFood(&tabFood, food);

    // Create Matrix element
    // Centerpiece of Food
    EditMATRIKS(food.coordinate.Y, food.coordinate.X, &kitchenMatix, M_FOOD, ptr_food, Nil, true);

    // Left side of Food
    if(food.coordinate.X > 1)
        if(!ElmtIsPhysical(kitchenMatix, food.coordinate.Y, food.coordinate.X-1))
            EditMATRIKS(food.coordinate.Y, food.coordinate.X-1, &kitchenMatix, M_FOOD, ptr_food, Nil, false);

    // Right side of Food
    if(food.coordinate.X < MAP_WIDTH)
        if(!ElmtIsPhysical(kitchenMatix, food.coordinate.Y, food.coordinate.X+1))
            EditMATRIKS(food.coordinate.Y, food.coordinate.X+1, &kitchenMatix, M_FOOD, ptr_food, Nil, false);

    // Top side of Food
    if(food.coordinate.Y > 1)
        if(!ElmtIsPhysical(kitchenMatix, food.coordinate.Y-1, food.coordinate.X))
            EditMATRIKS(food.coordinate.Y-1, food.coordinate.X, &kitchenMatix, M_FOOD, ptr_food, Nil, false);

    // Bottom side of Food
    if(food.coordinate.Y < MAP_HEIGHT)
        if(!ElmtIsPhysical(kitchenMatix, food.coordinate.Y+1, food.coordinate.X))
            EditMATRIKS(food.coordinate.Y+1, food.coordinate.X, &kitchenMatix, M_FOOD, ptr_food, Nil, false);


    // Diagonals
    // For diagonals, check if the overwritten cell is a pointer adjacent to the pointed food
    // Upper-Left side of Food
    if(food.coordinate.X > 1 && food.coordinate.Y > 1)
        if(isFoodPointerLegal(food.coordinate.X-1, food.coordinate.Y-1))
            EditMATRIKS(food.coordinate.Y-1, food.coordinate.X-1, &kitchenMatix, M_FOOD, ptr_food, Nil, false);

    // Upper-Right side of Food
    if(food.coordinate.X < MAP_WIDTH && food.coordinate.Y > 1)
        if(isFoodPointerLegal(food.coordinate.X+1, food.coordinate.Y-1))
            EditMATRIKS(food.coordinate.Y-1, food.coordinate.X+1, &kitchenMatix, M_FOOD, ptr_food, Nil, false);

    // Lower-Left side of Food
    if(food.coordinate.X > 1 && food.coordinate.Y < MAP_HEIGHT)
        if(isFoodPointerLegal(food.coordinate.X-1, food.coordinate.Y+1))
            EditMATRIKS(food.coordinate.Y+1, food.coordinate.X-1, &kitchenMatix, M_FOOD, ptr_food, Nil, false);

    // Lower-Right side of Food
    if(food.coordinate.X < MAP_WIDTH && food.coordinate.Y < MAP_HEIGHT)
        if(isFoodPointerLegal(food.coordinate.X+1, food.coordinate.Y+1))
            EditMATRIKS(food.coordinate.Y+1, food.coordinate.X+1, &kitchenMatix, M_FOOD, ptr_food, Nil, false);
}

/**
 * Check if the coordinate can be placed by a food pointer
 */
boolean isFoodPointerLegal(int x, int y) {
    if(ElmtIsPhysical(kitchenMatix, y, x)) {
        return false;
    } else {
        if (ElmtType(kitchenMatix, y, x) == M_FOOD) {
            POINT food_coord = ElmtFood(kitchenMatix, y, x)->coordinate;
            return !((abs(x - food_coord.X) == 1 && abs(y - food_coord.Y) == 0) || (abs(y - food_coord.Y) == 1 && abs(x - food_coord.X) == 0));
        } else {
            return true;
        }
    }
}