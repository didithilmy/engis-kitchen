//
// Created by Muhammad Aditya Hilmy on 12/11/18.
//

#ifndef ENGIS_KITCHEN_EVENTS_H
#define ENGIS_KITCHEN_EVENTS_H

typedef enum {
    LOAD_GAME, START_GAME, SAVE_GAME, EXIT_GAME,
    SET_NAME, SET_LIFE, SET_TIME, SET_MONEY,
    GET_MAP_WIDTH, GET_MAP_HEIGHT, GET_MAP_MATRIX,
    COMMAND,
    LAST
} Event;

#define NO_OF_EVENTS LAST

typedef enum {
    CMD_GU, CMD_GD, CMD_GL, CMD_GR, CMD_LOAD, CMD_SAVE
} Commands;

#endif //ENGIS_KITCHEN_EVENTS_H
