/**
 * Engi's Kitchen Expansion
 * Game display abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file display.c
 */

#include "../game_ui.h"
#include "../../ins_set.h"
#include "../../adt/headers.h"
#include "../gameover_ui.h"
#include "../../eventbus/eventbus.h"
#include "../../adt/point.h"
#include "../../adt/mesin_kata.h"

void driver(FORM *form, FIELD **fields, int ch);
void ExecuteCommands(Kata kata);
void postStartGame();
void onExitGame();
void onGameOver();
void uiNewGame();

void updateMoney(DataType money);
void updateLife(DataType life);
void updateTime(DataType time);
void updateName(DataType name);

void uiRefreshMap();
void updateFoodStack(DataType list);
void updateOrderList(DataType list);
void updateCustQueue(DataType list);

boolean isMoveLegal(POINT point);
void movePlayer(POINT moveTo);
void updateTooltip(POINT loc);

DataType uiGetPointedMeja();
DataType uiGetPointedFood();

// Global variables
DataType uiCMoney, uiCLife, uiCTime, uiCName;
DataType uiFoodStack, uiCustQueue, uiOrderList;

boolean isGameRunning;
POINT uiRestoDoor, uiKitchenDoor;
TabMeja tabMeja;
TabFood tabFood;
boolean isInRestaurant;

int MapWidth, MapHeight;
struct {
    WINDOW *T[200];
    int N;
} TabWindow;

POINT player_position;

/**
 * Game UI initialization procedure
 */
void game_ui_init() {
    isGameRunning = false;
    // Subscribe to events
    listen_post_event(START_GAME, &postStartGame);
    listen_event(EXIT_GAME, &onExitGame);
    listen_event(GAME_OVER, &onGameOver);
    listen_event(NEW_GAME, &uiNewGame);
    listen_1p_event(UI_SET_NAME, &updateName);
    listen_1p_event(UI_SET_LIFE, &updateLife);
    listen_1p_event(UI_SET_TIME, &updateTime);
    listen_1p_event(UI_SET_MONEY, &updateMoney);

    listen_event(UI_REFRESH_MAP, &uiRefreshMap);
    listen_1p_event(UI_SET_FOODSTACK, &updateFoodStack);
    listen_1p_event(UI_SET_ORDERLIST, &updateOrderList);
    listen_1p_event(UI_SET_CUSTQUEUE, &updateCustQueue);

    listen_getval_event(UI_GET_POINTED_MEJA, &uiGetPointedMeja);
    listen_getval_event(UI_GET_POINTED_FOOD, &uiGetPointedFood);
}

/**
 * Called when new game is created
 */
void uiNewGame() {
    // Set player cursor to be the resto door
    uiRestoDoor = publish_getval_event(GET_RESTO_DOOR_COORD).point;
    player_position = uiRestoDoor;
    isInRestaurant = true;
}

/**
 * Called when the game is started (post event)
 */
void postStartGame() {
    clear();

    // Set is game running to true
    isGameRunning = true;

    MapWidth = publish_getval_event(GET_MAP_WIDTH).integer;
    MapHeight = publish_getval_event(GET_MAP_HEIGHT).integer;
    buildGameScreen(MapWidth, MapHeight);

    // Set params
    updateName(uiCName);
    updateTime(uiCTime);
    updateLife(uiCLife);
    updateMoney(uiCMoney);
    updateCustQueue(uiCustQueue);
    updateFoodStack(uiFoodStack);
    updateOrderList(uiOrderList);

    // Load Meja map
    uiRestoDoor = publish_getval_event(GET_RESTO_DOOR_COORD).point;
    uiKitchenDoor = publish_getval_event(GET_KITCHEN_DOOR_COORD).point;
    tabMeja = *publish_getval_event(GET_TAB_MEJA).tabMeja;
    tabFood = *publish_getval_event(GET_TAB_FOOD).tabFood;

    // Load layout
    if(isInRestaurant)
        loadRestaurantLayout(tabMeja, uiRestoDoor);
    else
        loadKitchenLayout(tabFood, uiKitchenDoor);

    // Move cursor to beginning of field
    form_driver(commandForm, REQ_BEG_FIELD);

    /* Loop through to get user requests */
    int ch;
    ch = getch();
    while(isGameRunning) {
        driver(commandForm, field, ch);
        refresh();
        if(isGameRunning) ch = getch();
    }

    /* Un post form and free the memory */
    unpost_form(commandForm);
    free_form(commandForm);
    free_field(field[0]);


}

/**
 * Called when the game is exiting
 */
void onExitGame() {
    isGameRunning = false;
}


/**
 * Called when the game is over
 */
void onGameOver() {
    isGameRunning = false;
    showGameOver();
}


/**
 * Logical form driver
 * When a case goes unhandled, it calls the ui_driver
 * @return should exit program
 */
void driver(FORM *form, FIELD **fields, int ch) {
    char *command;

    switch (ch) {
        case KEY_ENTER:
        case 10:
            form_driver(form, REQ_BEG_FIELD);

            command = field_buffer(fields[0], 0);
            STARTKATA(command);

            ExecuteCommands(CKata);
            ui_driver(form, fields, ch);
            break;
        case KEY_DOWN:
            ExecuteCommands(INS_MV_DOWN);
            break;

        case KEY_UP:
            ExecuteCommands(INS_MV_UP);
            break;

        case KEY_LEFT:
            ExecuteCommands(INS_MV_LEFT);
            break;

        case KEY_RIGHT:
            ExecuteCommands(INS_MV_RIGHT);
            break;
        default:
            ui_driver(form, fields, ch);
    }
}

/**
 * Execute command stored in CKata
 */
void ExecuteCommands(Kata kata) {
    DataType dt;
    POINT point;

    if(CompareKata(kata, INS_EXIT, false)) {
        publish_event(EXIT_GAME);
    } else if(CompareKata(kata, INS_MV_UP, false)) {
        point.X = player_position.X;
        point.Y = player_position.Y - 1;
        if(isMoveLegal(point)) {
            movePlayer(point);

            dt.cmd = CMD_GU;
            publish_1p_event(COMMAND, dt);
        }
    } else if(CompareKata(kata, INS_MV_DOWN, false)) {
        point.X = player_position.X;
        point.Y = player_position.Y + 1;

        if(isMoveLegal(point)) {
            movePlayer(point);

            dt.cmd = CMD_GD;
            publish_1p_event(COMMAND, dt);
        }
    } else if(CompareKata(kata, INS_MV_LEFT, false)) {
        point.X = player_position.X - 1;
        point.Y = player_position.Y;

        if(isMoveLegal(point)) {
            movePlayer(point);

            dt.cmd = CMD_GL;
            publish_1p_event(COMMAND, dt);
        }
    } else if(CompareKata(kata, INS_MV_RIGHT, false)) {
        point.X = player_position.X + 1;
        point.Y = player_position.Y;

        if(isMoveLegal(point)) {
            movePlayer(point);

            dt.cmd = CMD_GR;
            publish_1p_event(COMMAND, dt);
        }
    } else if(CompareKata(kata, INS_DEBUG_OVER, false)) {
        publish_event(GAME_OVER);
    } else if(CompareKata(kata, INS_PLACE, false)) {
        dt.cmd = CMD_PLACE;
        publish_1p_event(COMMAND, dt);
    } else if(CompareKata(kata, INS_ORDER, false)) {
        dt.cmd = CMD_ORDER;
        publish_1p_event(COMMAND, dt);
    } else if(CompareKata(kata, INS_TAKE, false)) {
        dt.cmd = CMD_TAKE;
        publish_1p_event(COMMAND, dt);
    } else if(CompareKata(kata, INS_CLEAR_TRAY, false)) {
        dt.cmd = CMD_CLEARTRAY;
        publish_1p_event(COMMAND, dt);
    } else if(CompareKata(kata, INS_GIVE, false)) {
        dt.cmd = CMD_GIVE;
        publish_1p_event(COMMAND, dt);
    }
}


/**
 * Set Money in display
 * @param money
 */
void updateMoney(DataType money) {
    uiCMoney = money;

    if(isGameRunning) {
        wclear(moneyWindow);
        wprintw(moneyWindow, "Money: %d", money.integer);
        wrefresh(moneyWindow);
    }
}

/**
 * Set Life in display
 * @param life
 */
void updateLife(DataType life) {
    uiCLife = life;

    if(isGameRunning) {
        wclear(lifeWindow);
        wprintw(lifeWindow, "Life: %d", life.integer);
        wrefresh(lifeWindow);
    }
}

/**
 * Set Time in display
 * @param time
 */
void updateTime(DataType time) {
    uiCTime = time;

    if(isGameRunning) {
        wclear(timeWindow);
        wprintw(timeWindow, "Time: %d", time.integer);
        wrefresh(timeWindow);
    }
}

/**
 * Set Player's Name in display
 * @param name
 */
void updateName(DataType name) {
    int i;

    uiCName = name;

    Kata kata = name.kata;

    if(isGameRunning) {
        wclear(nameWindow);
        for(i = 1; i <= kata.Length; i++) {
            wprintw(nameWindow, "%c", kata.TabKata[i]);
        }
        wrefresh(nameWindow);
    }
}

/**
 * Update the character in the respective window coordinate
 * @param x
 * @param y
 * @param C
 */
void updateMapWindowCharacter(int x, int y, char *C) {
    int aIndex = (((y-1) * MapWidth) + x);
    wclear(TabWindow.T[aIndex]);
    mvwprintw(TabWindow.T[aIndex], 0, 1, C);
    wnoutrefresh(TabWindow.T[aIndex]);
}

/**
 * Clear the character in the respective window coordinate
 * @param x
 * @param y
 * @param C
 */
void clearMapWindow(int x, int y) {
    int aIndex = (((y-1) * MapWidth) + x);
    wclear(TabWindow.T[aIndex]);
    wnoutrefresh(TabWindow.T[aIndex]);
}

/**
 * Load map meja
 * @param T TabMeja
 */
void loadRestaurantLayout(TabMeja T, POINT door) {
    int i;

    // Render
    for(i = 1; i <= T.N; i++) {
        Meja meja = T.T[i];

        char str[4];
        sprintf(str, "%d", meja.tableNo);
        // Set the table number in the coord matrix
        updateMapWindowCharacter(meja.coordinate.X, meja.coordinate.Y, str);

        // Draw the empty chair on the surrounding
        // Draw the left and right chair
        updateMapWindowCharacter(meja.coordinate.X - 1, meja.coordinate.Y, meja.custAddress == NULL ? "X" : "C");
        updateMapWindowCharacter(meja.coordinate.X + 1, meja.coordinate.Y, meja.custAddress == NULL ? "X" : "C");

        // Draw the left and right chair, if capacity is 4
        if(meja.capacity == 4) {
            if(meja.custAddress == NULL)  {
                updateMapWindowCharacter(meja.coordinate.X, meja.coordinate.Y - 1, "X");
                updateMapWindowCharacter(meja.coordinate.X, meja.coordinate.Y + 1, "X");
            } else {
                updateMapWindowCharacter(meja.coordinate.X, meja.coordinate.Y - 1, meja.custAddress->N == 4 ? "C" : "X");
                updateMapWindowCharacter(meja.coordinate.X, meja.coordinate.Y + 1, meja.custAddress->N == 4 ? "C" : "X");
            }
        }
    }

    // Put player on position
    if(isInRestaurant) {
        // If currently in restaurant WHEN the method is invoked, do not change the position of the player

        updateMapWindowCharacter(door.X, door.Y, "D");
        updateMapWindowCharacter(player_position.X, player_position.Y, "P");
    } else {
        // Else, place player on door

        player_position.X = door.X;
        player_position.Y = door.Y;

        updateMapWindowCharacter(door.X, door.Y, "P");
    }

    doupdate();
    isInRestaurant = true;
}

/**
 * Load map food
 * @param T TabFood
 */
void loadKitchenLayout(TabFood T, POINT door) {
    int i;

    // Render
    for(i = 1; i <= T.N; i++) {
        Food food = T.T[i];
        updateMapWindowCharacter(food.coordinate.X, food.coordinate.Y, "M");
    }

    // Put player on position
    if(!isInRestaurant) {
        // If currently in kitchen WHEN the method is invoked, do not change the position of the player

        updateMapWindowCharacter(door.X, door.Y, "D");
        updateMapWindowCharacter(player_position.X, player_position.Y, "P");
    } else {
        // Else, place player on door

        player_position.X = door.X;
        player_position.Y = door.Y;

        updateMapWindowCharacter(door.X, door.Y, "P");
    }
    doupdate();

    isInRestaurant = false;
}

/**
 * Clear map windows
 */
void clearMapWindows() {
    int i;
    // Clear all windows
    for(i = 1; i <= TabWindow.N; i++) {
        if(mvwinch(TabWindow.T[i], 0, 1) != 0) {
            wclear(TabWindow.T[i]);
            wnoutrefresh(TabWindow.T[i]);
        }
    }
}

/**
 * Determine if the move is legal
 * @param point next point
 * @return is move legal
 */
boolean isMoveLegal(POINT point) {
    // Get matrix
    MATRIKS matriks;
    if(isInRestaurant) {
        matriks = publish_getval_event(GET_RESTO_MATRIX).matriks;
    } else {
        matriks = publish_getval_event(GET_KITCHEN_MATRIX).matriks;
    }

    return (point.X > 0 && point.Y > 0) && (point.X <= MapWidth && point.Y <= MapHeight) && !ElmtIsPhysical(matriks, point.Y, point.X);
}

/**
 * Move cursor to
 * @param moveTo
 */
void movePlayer(POINT moveTo) {
    if(isMoveLegal(moveTo)) {
        // Check if the moveTo point is a door in its respective layout
        if(moveTo.X == uiRestoDoor.X && moveTo.Y == uiRestoDoor.Y && isInRestaurant) {
            // If it goes to a door, change layout to kitchen
            clearMapWindows();
            loadKitchenLayout(tabFood, uiKitchenDoor);
        } else if(moveTo.X == uiKitchenDoor.X && moveTo.Y == uiKitchenDoor.Y && !isInRestaurant) {
            // If it goes to a door, change layout to restaurant
            clearMapWindows();
            loadRestaurantLayout(tabMeja, uiRestoDoor);
        } else {

            // Check if player_position is a door
            if((isInRestaurant && player_position.X == uiRestoDoor.X && player_position.Y == uiRestoDoor.Y) || (!isInRestaurant && player_position.X == uiKitchenDoor.X && player_position.Y == uiKitchenDoor.Y)) {
                // If it is, set point to Door
                updateMapWindowCharacter(player_position.X, player_position.Y, "D");
            } else {
                // Clear previous point
                clearMapWindow(player_position.X, player_position.Y);
            }

            // Set new point
            updateMapWindowCharacter(moveTo.X, moveTo.Y, "P");

            player_position.X = moveTo.X;
            player_position.Y = moveTo.Y;
        }

        updateTooltip(moveTo);
        doupdate();
    }
}

/**
 * Update tooltip window
 * @param loc
 */
void updateTooltip(POINT loc) {
    // Local variables
    MATRIKS matriks;
    Kata foodName;
    int i;

    if(isInRestaurant) {
        matriks = publish_getval_event(GET_RESTO_MATRIX).matriks;
    } else {
        matriks = publish_getval_event(GET_KITCHEN_MATRIX).matriks;
    }

    wclear(tooltipWindow);
    switch (ElmtType(matriks, loc.Y, loc.X)) {
        case M_MEJA:
            mvwprintw(tooltipWindow, 0, 0, "Table %d", ElmtMeja(matriks, loc.Y, loc.X)->tableNo);
            break;
        case M_FOOD:
            foodName = ElmtFood(matriks, loc.Y, loc.X)->name;
            for(i = 1; i <= foodName.Length; i++) {
                wprintw(tooltipWindow, "%c", foodName.TabKata[i]);
            }
            break;
        default:
            mvwprintw(tooltipWindow, 0, 0, isInRestaurant ? "Dining Room" : "Kitchen");
    }

    wrefresh(tooltipWindow);
}


/**
 * Builds game screen
 * @param HORZ horizontal columns
 * @param VERT vertical rows
 */
void buildGameScreen(int HORZ, int VERT) {
    int i, j, n;

    int HEIGHT = VERT * MAP_GRID_LINE;
    int WIDTH = (HORZ * MAP_GRID_COL) + (2 * (SIDE_PANEL_WIDTH + 1));

    curs_set(1);

    resizeTerminalWindow(WIDTH + 2, HEIGHT + MAP_TOP_OFFSET_LINE + MAP_TOP_OFFSET_LINE + 1);

    // TODO add delay to allow the window size to stabilize

    TabWindow.N = HORZ * VERT;

    // Build command input
    field[0] = new_field(1, 50, MAP_TOP_OFFSET_LINE + HEIGHT+2, 11, 0, 0);
    field_opts_off(field[0], O_AUTOSKIP);
    commandForm = new_form(field);
    post_form(commandForm);
    mvprintw(MAP_TOP_OFFSET_LINE + HEIGHT+2, 1, "%s", "Command: ");
    printBorder(MAP_TOP_OFFSET_LINE + HEIGHT + 1, MAP_TOP_OFFSET_LINE + HEIGHT+3, 0, WIDTH - SIDE_PANEL_WIDTH - 1);

    // Initiate tooltip panel
    printBorder(MAP_TOP_OFFSET_LINE + HEIGHT + 1, MAP_TOP_OFFSET_LINE + HEIGHT+3, WIDTH - SIDE_PANEL_WIDTH, WIDTH);
    tooltipWindow = newwin(1, SIDE_PANEL_WIDTH - 2, MAP_TOP_OFFSET_LINE + HEIGHT+2, WIDTH - SIDE_PANEL_WIDTH + 2);

    // Initiate name panel
    printBorder(0, 2, 0, SIDE_PANEL_WIDTH);
    nameWindow = newwin(1, SIDE_PANEL_WIDTH - 2, 1, 1);
    refresh();

    // Initiate queue panel
    printBorder(3, 3 + (HEIGHT/2), 0, SIDE_PANEL_WIDTH);
    mvprintw(4, 1, "%s", "Waiting Cust.");
    waitingCustWindow = newwin((HEIGHT/2) - 2, SIDE_PANEL_WIDTH - 1, 5, 1);

    // Initiate order panel
    printBorder((HEIGHT/2) + 1 + 3, HEIGHT + 3, 0, SIDE_PANEL_WIDTH);
    mvprintw((HEIGHT/2) + 2 + 3, 1, "%s", "Order");
    orderWindow = newwin((HEIGHT/2) - 3, SIDE_PANEL_WIDTH - 1, (HEIGHT/2) + 6, 1);

    // Initiate food stack panel
    printBorder(3, 3 + (HEIGHT), WIDTH - SIDE_PANEL_WIDTH, WIDTH);
    mvprintw(4, WIDTH - SIDE_PANEL_WIDTH + 1, "%s", "Food Stack");
    foodStackWindow = newwin(HEIGHT - 2, SIDE_PANEL_WIDTH - 1, 5, WIDTH - SIDE_PANEL_WIDTH + 1);

    // Remaining width
    int remWidth = WIDTH - (SIDE_PANEL_WIDTH + 1);

    // Initiate money panel
    int moneyX1 = (SIDE_PANEL_WIDTH + 1);
    int moneyX2 = WIDTH - (remWidth/2);
    printBorder(0, 2, moneyX1, moneyX2);
    moneyWindow = newwin(1, moneyX2 - moneyX1 - 2, 1, moneyX1 + 1);
    refresh();

    // Initiate life panel
    int lifeX1 = moneyX2 + 1;
    int lifeX2 = WIDTH - (remWidth/4);
    printBorder(0, 2, lifeX1, lifeX2);
    lifeWindow = newwin(1, lifeX2 - lifeX1 - 2, 1, lifeX1 + 1);
    refresh();

    // Initiate time panel
    int timeX1 = lifeX2 + 1;
    int timeX2 = WIDTH;
    printBorder(0, 2, timeX1, timeX2);
    timeWindow = newwin(1, timeX2 - timeX1 - 2, 1, timeX1 + 1);
    refresh();

    // Initiate MAP boxes
    n = 0;
    for(i = 0; i < VERT; i++) {
        for(j = 0; j < HORZ; j++) {
            n++;
            printBorder(MAP_TOP_OFFSET_LINE + (i*MAP_GRID_LINE), MAP_TOP_OFFSET_LINE + ((i+1)*MAP_GRID_LINE), (SIDE_PANEL_WIDTH + 1) + (j*MAP_GRID_COL), (SIDE_PANEL_WIDTH + 1) + ((j+1)*MAP_GRID_COL));
            TabWindow.T[n] = newwin(MAP_GRID_LINE - 1, MAP_GRID_COL - 1, MAP_TOP_OFFSET_LINE + (i*MAP_GRID_LINE) + 1, (SIDE_PANEL_WIDTH + 1) + (j*MAP_GRID_COL) + 1);
        }
    }

    refresh();
}

/**
 * Refresh map
 */
void uiRefreshMap() {
    if(isInRestaurant) {
        loadRestaurantLayout(tabMeja, uiRestoDoor);
    } else {
        loadKitchenLayout(tabFood, uiKitchenDoor);
    }
}

/**
 * Update food stack
 * @param list
 */
void updateFoodStack(DataType list) {
    address P;
    Kata foodName;
    int i;
    Stack S = list.list;

    uiFoodStack = list;

    wclear(foodStackWindow);
    P = First(S);
    while(P != Nil) {
        foodName = Info(P).food->name;
        // Print food name
        for(i = 1; i <= foodName.Length; i++) {
            wprintw(foodStackWindow, "%c", foodName.TabKata[i]);
        }
        wprintw(foodStackWindow, "\n");
        P = Next(P);
    }

    wrefresh(foodStackWindow);
}

/**
 * Update order list
 * @param list
 */
void updateOrderList(DataType list) {
    address P;
    Kata foodName;
    int i;
    List L = list.list;

    uiOrderList = list;

    wclear(orderWindow);
    P = First(L);
    while(P != Nil) {
        foodName = Info(P).order->food->name;
        // Print food name
        for(i = 1; i <= foodName.Length; i++) {
            wprintw(orderWindow, "%c", foodName.TabKata[i]);
        }
        wprintw(orderWindow, ", %d\n", Info(P).order->meja->tableNo);
        P = Next(P);
    }

    wrefresh(orderWindow);
}

/**
 * Update customer queue
 * @param list
 */
void updateCustQueue(DataType list) {
    address P;
    Queue Q = list.list;

    uiCustQueue = list;

    wclear(waitingCustWindow);
    P = First(Q);
    while(P != Nil) {
        wprintw(waitingCustWindow, "%d person\n", CustomerPersons(CustomerInfo(P)));
        P = Next(P);
    }

    wrefresh(waitingCustWindow);
}

/**
 * Get currently pointed Meja, if any
 * @return pointer to pointed Meja
 */
DataType uiGetPointedMeja() {
    // Local variables
    DataType dt;
    MATRIKS matriks;
    Kata foodName;

    dt.ptrMeja = Nil;

    if(isInRestaurant) {
        matriks = publish_getval_event(GET_RESTO_MATRIX).matriks;

        if (ElmtType(matriks, player_position.Y, player_position.X) == M_MEJA) {
            dt.ptrMeja = ElmtMeja(matriks, player_position.Y, player_position.X);
        }
    }

    return dt;
}

/**
 * Get currently pointed Food, if any
 * @return pointer to pointed Food
 */
DataType uiGetPointedFood() {
    // Local variables
    DataType dt;
    MATRIKS matriks;
    Kata foodName;

    dt.ptrFood = Nil;

    if(!isInRestaurant) {
        matriks = publish_getval_event(GET_KITCHEN_MATRIX).matriks;

        if (ElmtType(matriks, player_position.Y, player_position.X) == M_FOOD) {
            dt.ptrFood = ElmtFood(matriks, player_position.Y, player_position.X);
        }
    }

    return dt;
}