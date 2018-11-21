/**
 * Engi's Kitchen Expansion
 * Game manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file game.c
 */

#include "../game.h"

void load_game();
void save_game();
void do_command(DataType command);

// Variables of game parameters
int current_time;

void game_manager_init() {
    listen_event(LOAD_GAME, &load_game);
    listen_event(SAVE_GAME, &save_game);
    listen_event(COMMAND, &do_command);
}

/**
 * Loads game from file
 * Called when a load game instruction is requested
 */
void load_game() {
    // TODO read files and load
    DataType name, time, life, money;

    current_time = 0;

    name.string = "Riza Satria P.";
    time.integer = current_time;
    life.integer = 0;
    money.integer = 1000;

    //publish_1p_event(SET_NAME, name);
    publish_1p_event(SET_TIME, time);
    publish_1p_event(SET_LIFE, life);
    publish_1p_event(SET_MONEY, money);
}


/**
 * Saves game to file
 * Called when a save game instruction is requested
 */
void save_game() {
    // TODO write file
}

void do_command(DataType command) {
    Commands cmd = command.cmd;

    // TODO keeps track of command, if necessary
    switch (cmd) {
        case CMD_GU:
        case CMD_GD:
        case CMD_GR:
        case CMD_GL:
            current_time++;

            DataType dt;
            dt.integer = current_time;
            publish_1p_event(SET_TIME, dt);

            break;
        default:
            break;
    }
}