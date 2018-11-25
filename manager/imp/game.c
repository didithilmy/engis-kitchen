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
void start_game();
void do_command(DataType command);
void new_game(DataType name);

// Variables of game parameters
GameState currentGame;
Stack FoodStack; 


//variable global yang tipenya foodstack 
// create empty stacknya di init 

//bikin lagi prosedur clear_tray isinya while not empty pop dealokasi
void game_manager_init() {
    listen_event(NEW_GAME, &new_game);
    listen_event(LOAD_GAME, &load_game);
    listen_event(SAVE_GAME, &save_game);

    listen_event(START_GAME, &start_game);

    listen_1p_event(COMMAND, &do_command);
    listen_1p_event(NEW_GAME, &new_game);
    CreateEmpty(&FoodStack);
}

/**
 * Loads game from file
 * Called when a load game instruction is requested
 */
void load_game() {
    // TODO read files and load
    currentGame.time = 0;
    currentGame.life = 0;
    currentGame.money = 1000;
    currentGame.player_name = BuildKata("Player Lolz");
}

/**
 * Saves game to file
 * Called when a save game instruction is requested
 */
void save_game() {
    // TODO write file
}

/**
 * Starts game
 * Called when a start game instruction is requested
 */
void start_game() {
    // TODO read files and load
    DataType name, time, life, money;

    name.kata = currentGame.player_name;
    time.integer = currentGame.time;
    life.integer = currentGame.life;
    money.integer = currentGame.money;

    publish_1p_event(UI_SET_NAME, name);
    publish_1p_event(UI_SET_TIME, time);
    publish_1p_event(UI_SET_LIFE, life);
    publish_1p_event(UI_SET_MONEY, money);
}

void do_command(DataType command) {
    Commands cmd = command.cmd;

    // TODO keeps track of command, if necessary
    switch (cmd) {
        case CMD_GU:
        case CMD_GD:
        case CMD_GR:
        case CMD_GL:
            currentGame.time++;

            DataType dt;
            dt.integer = currentGame.time;
            publish_1p_event(UI_SET_TIME, dt);

            break;
        default:
            break;
    }
}

/**
 * New game
 * @param name player's name
 */
void new_game(DataType name) {
    // TODO initialize default values
    currentGame.time = 0;
    currentGame.life = 0;
    currentGame.money = 1000;
    currentGame.player_name = name.kata;
}

/**
 * Clears stack
 * @author Claudia Renata, NIM 18217048
 */
void clear_tray() {
    Food X;
    while(!IsEmpty(FoodStack)) {
        Pop(&FoodStack, &X);
    }

    // TODO publish to UI
}
