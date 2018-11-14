/**
 * Engi's Kitchen Expansion
 * Map manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file map.c
 */

#include "../map.h"
#include "../../eventbus/eventbus.h"

int MAP_WIDTH, MAP_HEIGHT;

DataType get_map_width();
DataType get_map_height();

/**
 * Initiate module
 */
void map_manager_init() {
    // TODO load map files
    MAP_WIDTH = 9;
    MAP_HEIGHT = 9;

    listen_getval_event(GET_MAP_WIDTH, &get_map_width);
    listen_getval_event(GET_MAP_HEIGHT, &get_map_height);

    // TODO listen for GET_MAP_MATRIX
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