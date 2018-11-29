/**
 * Engi's Kitchen Expansion
 * Game manager abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @author Zalikha Adiera Gambetta, NIM 18217027
 * @author Muhammad Yanza Hattari, NIM 18217043
 * @author Claudia Renata M.D. NIM 18217048
 *
 * @file game.c
 */

#include <stdlib.h>
#include "../game.h"

void load_game();
void save_game();
void start_game();
void game_over();
void do_command(DataType command);
void new_game(DataType name);
void customer_arrive();
void decrease_customer_patience();
void decrement_life();
boolean place_customer();
void time_tick();
void clear_tray();
boolean TakeOrder();
boolean TakeFood();
boolean GiveFood();
DataType is_game_exists();
Food * getFoodAddrByFoodName(Kata foodName);
Meja * getMejaAddrByTableNo(int tableNo);
void clear_game_data();

// Variables of game parameters
GameState currentGame;
Stack FoodStack; 
List OrderList;
Queue CustomerQueue;
boolean GameExists;

int timeToCustomerArrival;

//variable global yang tipenya foodstack 
// create empty stacknya di init 

//bikin lagi prosedur clear_tray isinya while not empty pop dealokasi
void game_manager_init() {
    listen_event(NEW_GAME, &new_game);
    listen_event(LOAD_GAME, &load_game);
    listen_event(START_GAME, &start_game);
    listen_event(GAME_OVER, &game_over);

    listen_1p_event(COMMAND, &do_command);
    listen_1p_event(NEW_GAME, &new_game);

    listen_getval_event(IS_GAME_EXISTS, &is_game_exists);
    CreateEmpty(&FoodStack);
	CreateEmpty(&OrderList);
    CreateEmpty(&CustomerQueue);

    GameExists = false;
}

/**
 * Loads game from file
 * Called when a load game instruction is requested
 */
void load_game() {
    int capacity, patience, N, tableNo;
    Customer *customer;
    Order *order;
    Food *food;
    Meja *meja;
    infotype data;
    DataType dt;

    // Clear game data
    clear_game_data();

    STARTFILE("game.dat");
    while (!IsEOPF())
    {
        if (GetFCC() != ';')
        {
            if (GetFCC() == '(') {
                ADVFILE();
                char d = GetFCC();
                ADVFILE();
                ADVFILE();
                MKF_SalinKata();
                int X = KataToInt(MKF_CKata);
                MKF_ADVKATA();
                int Y = KataToInt(MKF_CKata);

                dt.integer = d == 'R';
                publish_1p_event(UI_SET_ROOM, dt);

                dt.point = MakePOINT(X, Y);
                publish_1p_event(UI_SET_POSITION, dt);
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
            if (GetFCC() == '(') {
                ADVFILE();
                MKF_SalinKata();

                // Set player name
                currentGame.player_name = MKF_CKata;
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
        ADVFILE();
        if (GetFCC() != ';') {
            if (GetFCC() == '(') {
                ADVFILE();
                MKF_SalinKata();
                currentGame.money = KataToInt(MKF_CKata);
                //printf("money %d\n", money);
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
        ADVFILE();
        if (GetFCC() != ';') {
            if (GetFCC() == '(') {
                ADVFILE();
                MKF_SalinKata();
                currentGame.life = KataToInt(MKF_CKata);
                //printf("life %d\n", life);
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
        ADVFILE();
        if (GetFCC() != ';') {
            if (GetFCC() == '(') {
                ADVFILE();
                MKF_SalinKata();
                currentGame.time = KataToInt(MKF_CKata);
                //printf("time %d\n", time);
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
        ADVFILE();

        // Acquire Queue
        while (GetFCC() != ';') {
            if (GetFCC() == '(') {
                ADVFILE();
                MKF_SalinKata();
                capacity = KataToInt(MKF_CKata);
                MKF_ADVKATA();
                patience = KataToInt(MKF_CKata);

                MakeCustomer(&customer);
                customer->patience = patience;
                customer->N = capacity;
                customer->order = Nil;

                data.custAddress = customer;
                InsVLast(&CustomerQueue, data);
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
        ADVFILE();

        // Acquire Stack
        while (GetFCC() != ';') {
            if (GetFCC() == '(') {
                ADVFILE();
                MKF_SalinKata();

                food = getFoodAddrByFoodName(MKF_CKata);
                data.food = food;
                InsVLast(&FoodStack, data);
            }
            ADVFILE();
            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
        ADVFILE();

        // Acquire Meja
        while (GetFCC() != '.') {
            meja = Nil;

            // Acquire Meja primary data
            if (GetFCC() == '(') {
                ADVFILE();
                MKF_SalinKata();

                capacity = KataToInt(MKF_CKata);

                MKF_ADVKATA();
                tableNo = KataToInt(MKF_CKata);

                meja = getMejaAddrByTableNo(tableNo);
                meja->capacity = capacity;
            }

            // Acquire Meja customer
            ADVFILE();
            if (GetFCC() != ')'){
                MKF_SalinKata();
                N = KataToInt(MKF_CKata);

                MKF_ADVKATA();
                patience = KataToInt(MKF_CKata);

                ADVFILE();

                MakeCustomer(&customer);
                customer->patience = patience;
                customer->N = N;

                meja->custAddress = customer;
            }

            // Acquire ordered Food
            if (GetFCC() != ')') {
                MKF_SalinKata();
                ADVFILE();

                // Find food address
                food = getFoodAddrByFoodName(MKF_CKata);

                // If food exists, proceed
                if(food != Nil) {
                    // Create order
                    // Meja must be initialized
                    OrderAllocate(&order, food, meja);

                    // Add Order to Customer
                    meja->custAddress->order = order;

                    // Add order to list
                    InsOrderLast(&OrderList, order);
                }
            }

            if (GetFCC() == ')')
            {
                ADVFILE();
            }
        }
    }

    GameExists = true;

    // Refresh UI
    publish_event(UI_REFRESH_MAP);

    dt.list = FoodStack;
    publish_1p_event(UI_SET_FOODSTACK, dt);
    dt.list = CustomerQueue;
    publish_1p_event(UI_SET_CUSTQUEUE, dt);
    dt.list = OrderList;
    publish_1p_event(UI_SET_ORDERLIST, dt);
}

/**
 * Saves game to file
 * Called when a save game instruction is requested
 */
void save_game() {
    int i;
    address P;
    Kata foodName;

    TabMeja *tabMeja = publish_getval_event(GET_TAB_MEJA).tabMeja;

    FILE *f = fopen("game.dat","w");

    Kata nama = currentGame.player_name;
    int money = currentGame.money;
    int life = currentGame.life;
    int time = currentGame.time;

    // Write player position
    fprintf(f, "(%c %d %d );",
            publish_getval_event(UI_GET_ROOM).integer ? 'R' : 'K',
            publish_getval_event(UI_GET_POSITION).point.X,
            publish_getval_event(UI_GET_POSITION).point.Y);

    // Write name
    fprintf(f,"(");
    // Iterate nama
    for(i = 1; i <= nama.Length; i++) {
        fprintf(f,"%c", nama.TabKata[i]);
    }
    fprintf(f," );");

    fprintf(f, "(%d );", money);
    fprintf(f, "(%d );", life);
    fprintf(f, "(%d );",time);

    // Iterate Queue
    P = First(CustomerQueue);
    while(P != Nil) {
        fprintf(f, "(%d %d )", P->info.custAddress->N, P->info.custAddress->patience);
        P = Next(P);
    }

    fprintf(f,";"); //untuk ngasi ';'

    // Iterate Stack
    P = First(FoodStack);
    while(P != Nil) {
        fprintf(f, "(");
        foodName = P->info.food->name;
        for(i = 1; i <= foodName.Length; i++) {
            fprintf(f, "%c", foodName.TabKata[i]);
        }
        fprintf(f, " )");
        P = Next(P);
    }
    fprintf(f,";"); //untuk ngasi

    // Iterate Meja
    for(i = 1; i <= tabMeja->N; i++) {
        fprintf (f,"(%d %d ", tabMeja->T[i].capacity, tabMeja->T[i].tableNo);

        // Check if Meja has an associated customer
        if(tabMeja->T[i].custAddress != Nil) {
            // If any, print patience and no of customer
            fprintf(f, "%d %d ", tabMeja->T[i].custAddress->N, tabMeja->T[i].custAddress->patience);

            // Print foodName, if an order exists
            if(tabMeja->T[i].custAddress->order != Nil) {
                foodName = tabMeja->T[i].custAddress->order->food->name;
                for (i = 1; i <= foodName.Length; i++) {
                    fprintf(f, "%c", foodName.TabKata[i]);
                }
                fprintf(f, " ");    // Prints space (BLANK)
            }
        }
        fprintf(f, ")");
    }

    // Print MARK
    fprintf(f,".");

    fclose(f);
}

/**
 * Starts game
 * Called when a start game instruction is requested
 */
void start_game() {
    DataType name, time, life, money;
    DataType dt;

    name.kata = currentGame.player_name;
    time.integer = currentGame.time;
    life.integer = currentGame.life;
    money.integer = currentGame.money;

    publish_1p_event(UI_SET_NAME, name);
    publish_1p_event(UI_SET_TIME, time);
    publish_1p_event(UI_SET_LIFE, life);
    publish_1p_event(UI_SET_MONEY, money);

    dt.list = OrderList;
    publish_1p_event(UI_SET_ORDERLIST, dt);

    dt.list = FoodStack;
    publish_1p_event(UI_SET_FOODSTACK, dt);

    dt.list = CustomerQueue;
    publish_1p_event(UI_SET_CUSTQUEUE, dt);

    publish_event(UI_REFRESH_MAP);

    // Randomize time to cust arrival
    timeToCustomerArrival = (rand() % 20) + 10;
}

/**
 * Returns is game exists
 * @return
 */
DataType is_game_exists() {
    DataType dt;
    dt.integer = GameExists;

    return dt;
}

void do_command(DataType command) {
    Commands cmd = command.cmd;

    // TODO keeps track of command, if necessary
    switch (cmd) {
        case CMD_GU:
        case CMD_GD:
        case CMD_GR:
        case CMD_GL:
            time_tick();
            break;
        case CMD_CLEARTRAY:
            clear_tray();
            time_tick();
            break;
        case CMD_PLACE:
            if (place_customer()) time_tick();
            break;
        case CMD_ORDER:
            if (TakeOrder()) time_tick();
            break;
        case CMD_TAKE:
            if (TakeFood()) time_tick();
            break;
        case CMD_GIVE:
            if (GiveFood()) time_tick();
            break;
        case CMD_SAVE:
            save_game();
            break;
        default:
            break;
    }
}

/**
 * Do action when the time tticks
 */
void time_tick() {
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
    int i;
    address Pdel;

    currentGame.time = 0;
    currentGame.life = 5;
    currentGame.money = 0;
    currentGame.player_name = name.kata;

    clear_game_data();

    GameExists = true;
}

/**
 * Called when game is over
 */
void game_over() {
    GameExists = false;
}

/**
 * Clear game data
 */
void clear_game_data() {
    address Pdel;
    int i;

    // Deallocate customer queue
    while(!IsEmpty(CustomerQueue)) {
        DelFirst(&CustomerQueue, &Pdel);
        CustomerDeallocate(Pdel->info.custAddress);
        Dealokasi(&Pdel);
    }

    // Deallocate Order List
    while(!IsEmpty(OrderList)) {
        DelFirst(&OrderList, &Pdel);
        OrderDeallocate(Pdel->info.order);
        Dealokasi(&Pdel);
    }

    // Deallocate food stack
    DelAll(&FoodStack);

    // Iterate TabMeja and deallocate Customer, if any
    TabMeja *tabMeja = publish_getval_event(GET_TAB_MEJA).tabMeja;
    for(i = 1; i <= tabMeja->N; i++) {
        if(tabMeja->T[i].custAddress != Nil) {
            CustomerDeallocate(tabMeja->T[i].custAddress);
            tabMeja->T[i].custAddress = Nil;
        }
    }

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

/**
 * Take order of a Meja
 * @author Muhammad Yanza Hattari, NIM TODO ISI NIM WOE
 */
boolean TakeOrder() {
	Order *order;
    Food *food;
    TabFood *tabFood;
    int randInd;

    Meja *meja = publish_getval_event(UI_GET_POINTED_MEJA).ptrMeja;

    if(meja != Nil) {
        if(meja->custAddress != Nil) {
            if(meja->custAddress->order == Nil) {
                // Get random Food from TabFood
                tabFood = publish_getval_event(GET_TAB_FOOD).tabFood;
                randInd = rand() % tabFood->N;   // Generate random int from 0 to N
                // Abolish 0
                if (randInd == 0) randInd = 1;
                food = &(tabFood->T[randInd]);

                // Create Order
                OrderAllocate(&order, food, meja);
                InsOrderLast(&OrderList, order);

                // Assign customer order to point the newly-made Order
                meja->custAddress->order = order;

                // Publish to UI
                DataType dt;
                dt.list = OrderList;
                publish_1p_event(UI_SET_ORDERLIST, dt);
                return true;
            }
        }
    }
    return false;
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
    TabMeja *tabMeja = publish_getval_event(GET_TAB_MEJA).tabMeja;
    int i;
    for(i = 1; i <= tabMeja->N; i++) {
        if(tabMeja->T[i].custAddress != Nil) {
            tabMeja->T[i].custAddress->patience--;

            // Deallocate if patience is 0
            if (tabMeja->T[i].custAddress->patience == 0) {
                // Remove associated Order, if any
                if(tabMeja->T[i].custAddress->order != Nil) {
                    Prec = SearchOrderPrec(OrderList, tabMeja->T[i].custAddress->order);

                    if (Prec == Nil) {
                        DelFirst(&OrderList, &Pdel);
                    } else {
                        DelAfter(&OrderList, &Pdel, Prec);
                    }

                    OrderDeallocate(tabMeja->T[i].custAddress->order);
                }

                // Deallocate memory space
                CustomerDeallocate(tabMeja->T[i].custAddress);

                // Empty the Meja
                tabMeja->T[i].custAddress = Nil;

                decrement_life();
            }
        }
    }

    // Invoke UI update
    publish_event(UI_REFRESH_MAP);

    DataType dt;
    dt.list = CustomerQueue;
    publish_1p_event(UI_SET_CUSTQUEUE, dt);

    dt.list = OrderList;
    publish_1p_event(UI_SET_ORDERLIST, dt);
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

/**
 * Place customer onto table
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @author Zalikha Adiera Gambetta, NIM 18217027
 * @return customer placement successful
 */
boolean place_customer()
{
    // kamus lokal
    boolean found;
    address P, Prec, Pdel;
    Meja *meja = publish_getval_event(UI_GET_POINTED_MEJA).ptrMeja;

    // algoritma
    if(meja != Nil) {
        if(meja->custAddress == Nil) {
            if(!IsEmpty(CustomerQueue)) {
                found = false;
                Prec = Nil;
                P = First(CustomerQueue);
                while(P != Nil && !found) {
                    found = Info(P).custAddress->N <= meja->capacity;
                    if(!found) {
                        Prec = P;
                        P = Next(P);
                    }
                }

                if(found) {
                    // If Precursor is Nil, it is the first element
                    if(Prec == Nil) {
                        DelFirst(&CustomerQueue, &Pdel);
                    } else {
                        DelAfter(&CustomerQueue, &Pdel, Prec);
                    }

                    // Place Customer to Meja
                    meja->custAddress = Info(Pdel).custAddress;

                    // Randomize patience
                    meja->custAddress->patience = 20 + (rand() % 10);

                    // Deallocate list element
                    Dealokasi(&Pdel);

                    // Publish to UI
                    DataType dt;
                    dt.list = CustomerQueue;
                    publish_1p_event(UI_SET_CUSTQUEUE, dt);
                    publish_event(UI_REFRESH_MAP);

                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * Take food
 * Adds Food to Stack
 * @return is operation successful
 */
boolean TakeFood() {
    Food *food = publish_getval_event(UI_GET_POINTED_FOOD).ptrFood;
    if(food != Nil) {
        if(NbElmt(FoodStack) < MAX_FOOD_STACK_ELMT) {
            Push(&FoodStack, food);
            DataType dt;
            dt.list = FoodStack;
            publish_1p_event(UI_SET_FOODSTACK, dt);

            return true;
        }
    }
    return false;
}

/**
 * Give food
 * Give the food at the top of the stack to customer in a table, and deallocate the customer, order, and set the table customer pointer to Nil
 * @return is operation successful
 */
boolean GiveFood() {
    Meja *meja = publish_getval_event(UI_GET_POINTED_MEJA).ptrMeja;
    Food *fdel;
    address P, Prec, Pdel;

    if(meja != Nil) {
        // Check if Meja has customer
        if(meja->custAddress != Nil) {
            // Check if Customer has an Order
            if(meja->custAddress->order != Nil) {
                // Check if Food Stack is not empty
                if(!IsEmpty(FoodStack)) {
                    // Check if Food at the top of the stack matches the ordered food
                    if(meja->custAddress->order->food == First(FoodStack)->info.food) {
                        // Operation valid
                        // Pop the stack
                        Pop(&FoodStack, &fdel);

                        // Remove the customer's order
                        Prec = SearchOrderPrec(OrderList, meja->custAddress->order);

                        if (Prec == Nil) {
                            DelFirst(&OrderList, &Pdel);
                        } else {
                            DelAfter(&OrderList, &Pdel, Prec);
                        }

                        OrderDeallocate(meja->custAddress->order);

                        // Deallocate Customer object
                        CustomerDeallocate(meja->custAddress);

                        // Remove association
                        meja->custAddress = Nil;

                        // Increment money
                        currentGame.money += fdel->price;

                        DataType dt;
                        dt.integer = currentGame.money;
                        publish_1p_event(UI_SET_MONEY, dt);

                        dt.list = FoodStack;
                        publish_1p_event(UI_SET_FOODSTACK, dt);

                        // Refresh UI
                        publish_event(UI_REFRESH_MAP);

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Food * getFoodAddrByFoodName(Kata foodName) {
    int i;
    boolean found;
    TabFood *tabFood = publish_getval_event(GET_TAB_FOOD).tabFood;
    i = 1;
    found = false;
    while(i <= tabFood->N && !found) {
        found = CompareKata(foodName, tabFood->T[i].name, false);
        if(!found) {
            i++;
        }
    }

    if(found) {
        return &(tabFood->T[i]);
    } else {
        return Nil;
    }
}

Meja * getMejaAddrByTableNo(int tableNo) {
    int i;
    boolean found;
    TabMeja *tabMeja = publish_getval_event(GET_TAB_MEJA).tabMeja;
    i = 1;
    found = false;
    while(i <= tabMeja->N && !found) {
        found = tableNo == tabMeja->T[i].tableNo;
        if(!found) {
            i++;
        }
    }

    if(found) {
        return &(tabMeja->T[i]);
    } else {
        return Nil;
    }
}