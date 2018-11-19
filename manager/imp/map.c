/**
 * Engi's Kitchen Expansion
 * Map manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
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

/**
 * Initiate module
 */
void map_manager_init() {
    // TODO load map files
    MAP_WIDTH = 9;
    MAP_HEIGHT = 9;

    // TODO load TabMeja
    AddMeja(&tabMeja, CreateMeja(MakePOINT(3, 3), 2, 1));
    AddMeja(&tabMeja, CreateMeja(MakePOINT(7, 3), 4, 2));
    AddMeja(&tabMeja, CreateMeja(MakePOINT(3, 7), 2, 3));
    AddMeja(&tabMeja, CreateMeja(MakePOINT(7, 7), 4, 4));

    listen_getval_event(GET_MAP_WIDTH, &get_map_width);
    listen_getval_event(GET_MAP_HEIGHT, &get_map_height);
    listen_getval_event(GET_MAP_ARRAY, &get_map_array);
    listen_event(LOAD_GAME, &onLoadGame);

    // TODO listen for GET_MAP_ARRAY
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