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

void driver(FORM *form, FIELD **fields, int ch);
void ExecuteCommands(Kata kata);
void postStartGame();
void onExitGame();

void updateMoney(DataType money);
void updateLife(DataType life);
void updateTime(DataType time);
void updateName(DataType name);

boolean isMoveLegal(POINT point);
void movePlayer(POINT moveTo);
void updateTooltip(POINT loc);

// Global variables
DataType uiCMoney, uiCLife, uiCTime, uiCName;
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
    listen_1p_event(UI_SET_NAME, &updateName);
    listen_1p_event(UI_SET_LIFE, &updateLife);
    listen_1p_event(UI_SET_TIME, &updateTime);
    listen_1p_event(UI_SET_MONEY, &updateMoney);
}

/**
 * Called when the game is started (post event)
 */
void postStartGame() {
    // Set is game running to true
    isGameRunning = true;

    MapWidth = publish_getval_event(GET_MAP_WIDTH).integer;
    MapHeight = publish_getval_event(GET_MAP_HEIGHT).integer;
    buildGameScreen(MapHeight, MapWidth);

    // Set name
    updateName(uiCName);
    updateTime(uiCTime);
    updateLife(uiCLife);
    updateMoney(uiCMoney);

    // Load Meja map
    // TODO change door coordinate
    uiRestoDoor = MakePOINT(1, MapHeight);
    uiKitchenDoor = MakePOINT(1, 1);
    tabMeja = publish_getval_event(GET_TAB_MEJA).tabMeja;
    tabFood = publish_getval_event(GET_TAB_FOOD).tabFood;

    // Set player cursor to be the resto door
    player_position = uiRestoDoor;

    loadRestaurantLayout(tabMeja, uiRestoDoor);
    isInRestaurant = true;

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
                updateMapWindowCharacter(meja.coordinate.X, meja.coordinate.Y - 1, CustomerPersons(meja.custAddress) == 4 ? "C" : "X");
                updateMapWindowCharacter(meja.coordinate.X, meja.coordinate.Y + 1, CustomerPersons(meja.custAddress) == 4 ? "C" : "X");
            }
        }
    }

    // Put player on door
    player_position.X = door.X;
    player_position.Y = door.Y;

    updateMapWindowCharacter(door.X, door.Y, "P");
    doupdate();
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

    // Put player on door
    player_position.X = door.X;
    player_position.Y = door.Y;

    updateMapWindowCharacter(door.X, door.Y, "P");
    doupdate();
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
            isInRestaurant = false;
            clearMapWindows();
            loadKitchenLayout(tabFood, uiKitchenDoor);
        } else if(moveTo.X == uiKitchenDoor.X && moveTo.Y == uiKitchenDoor.Y && !isInRestaurant) {
            // If it goes to a door, change layout to restaurant
            isInRestaurant = true;
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

    // Initiate order panel
    printBorder((HEIGHT/2) + 1 + 3, HEIGHT + 3, 0, SIDE_PANEL_WIDTH);
    mvprintw((HEIGHT/2) + 2 + 3, 1, "%s", "Order");

    // Initiate food stack panel
    printBorder(3, 3 + (HEIGHT), WIDTH - SIDE_PANEL_WIDTH, WIDTH);
    mvprintw(4, WIDTH - SIDE_PANEL_WIDTH + 1, "%s", "Food Stack");
    foodStackWindow = newwin(HEIGHT - 3, SIDE_PANEL_WIDTH - 1, 6, WIDTH - SIDE_PANEL_WIDTH + 1);

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