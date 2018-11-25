/**
 * Engi's Kitchen Expansion
 * Game manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @author Muhammad Yanza Hattari, NIM 18217043
 * @file game.c
 */

#include <stdlib.h>
#include "../game.h"
#include "../../eventbus/eventbus.h"
#include "../../adt/headers.h"


void load_game();
void save_game();
void start_game();
void do_command(DataType command);
void new_game(DataType name);
void customer_arrive();
void decrease_customer_patience();
void decrement_life();

// Variables of game parameters
GameState currentGame;
Stack FoodStack; 
List OrderList;
Queue CustomerQueue;

int timeToCustomerArrival;

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
	CreateEmpty(&OrderList);
    CreateEmpty(&CustomerQueue);
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

    // Randomize time to cust arrival
    timeToCustomerArrival = (rand() % 20) + 10;
}

void do_command(DataType command) {
    Commands cmd = command.cmd;

    // TODO keeps track of command, if necessary
    switch (cmd) {
        case CMD_GU:
        case CMD_GD:
        case CMD_GR:
        case CMD_GL:
            break;
        case CMD_CLEARTRAY:
            clear_tray();
        default:
            break;
    }

    currentGame.time++;

    DataType dt;
    dt.integer = currentGame.time;
    publish_1p_event(UI_SET_TIME, dt);

    customer_arrive();
    decrease_customer_patience();
}

/**
 * New game
 * @param name player's name
 */
void new_game(DataType name) {
    // TODO initialize default values
    currentGame.time = 0;
    currentGame.life = 5;
    currentGame.money = 0;
    currentGame.player_name = name.kata;
}

/**
 * Clears stack
 * @author Claudia Renata, NIM 18217048
 */
void clear_tray() {
    Food *P;
    while(!IsEmpty(FoodStack)) {
        Pop(&FoodStack, &P);
    }

    // Publish to UI
    DataType dt;
    dt.list = FoodStack;
    publish_1p_event(UI_SET_FOODSTACK, dt);
}

void TakeOrder (Food * food, Meja * meja) {
	Order *order;
	
	address P = InsOrderLast (&OrderList, CreateOrder(food, meja));
	order = &(Info(P).order);

    meja->custAddress->order = order;
	
	// Publish to UI
    DataType dt;
    dt.list = OrderList;
    publish_1p_event(UI_SET_ORDERLIST, dt);
}

/**
 * Randomize customer arrival
 */
void customer_arrive() {
    Customer *custAddress;

    timeToCustomerArrival--;
    if(timeToCustomerArrival == 0) {
        // Allocate customer
        MakeCustomer(&custAddress);
        Add(&CustomerQueue, custAddress);

        // TODO publish to customer

        // Re set the customer arrival
        timeToCustomerArrival = (rand() % 20) + 10;

        DataType dt;
        dt.list = CustomerQueue;
        publish_1p_event(UI_SET_CUSTQUEUE, dt);
    }
}

/**
 * Decrease customer patience by 1. If the customer patience is 0, remove and deallocate
 */
void decrease_customer_patience() {
    address P, Prec, Pdel;

    // Iterate Queue
    Prec = Nil;
    P = First(CustomerQueue);
    while(P != Nil) {
        Info(P).custAddress->patience--;

        // Deallocate if patience is 0
        if(Info(P).custAddress->patience == 0) {
            if(Prec == Nil) {
                // First element
                DelFirst(&CustomerQueue, &Pdel);
            } else {
                // Not first element
                DelAfter(&CustomerQueue, &Pdel, P);
            }
            Dealokasi(&Pdel);
            decrement_life();
        }
        Prec = P;
        P = Next(P);
    }

    // Iterate TabMeja
    TabMeja tabMeja = publish_getval_event(GET_TAB_MEJA).tabMeja;
    int i;
    for(i = 1; i <= tabMeja.N; i++) {
        if(tabMeja.T[i].custAddress != Nil) {
            tabMeja.T[i].custAddress->patience--;

            // Deallocate if patience is 0
            if (tabMeja.T[i].custAddress->patience == 0) {
                CustomerDeallocate(tabMeja.T[i].custAddress);
                tabMeja.T[i].custAddress = Nil;

                decrement_life();
            }
        }
    }

    // Invoke UI update
    //publish_event(UI_REFRESH_MAP);

    DataType dt;
    dt.list = CustomerQueue;
    publish_1p_event(UI_SET_CUSTQUEUE, dt);
}

/**
 * Decrement life. If 0, publish Game over event
 */
void decrement_life() {
    DataType dt;
    currentGame.life--;

    dt.integer = currentGame.life;
    publish_1p_event(UI_SET_LIFE, dt);
    if(currentGame.life == 0) {
        publish_event(GAME_OVER);
    }
}