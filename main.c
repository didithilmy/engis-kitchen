/**
 * Engi's Kitchen Expansion
 * Entrypoint
 *
 * This file serves as an entrypoint to the program, as well as the UI layer.
 * @author Muhammad Aditya Hilmy, NIM 18217025
 */

#include <stdlib.h>
#include <stdio.h>
#include "manager/intro.h"
#include "manager/game.h"
#include "ins_set.h"

char command[32];

Kata CKata;
boolean EOP;

int main() {
    // Initialize instruction set
    INS_MV_UP = BuildKata("GU");
    INS_MV_DOWN = BuildKata("GD");
    INS_MV_LEFT = BuildKata("GL");
    INS_MV_RIGHT = BuildKata("GR");

    INS_ORDER = BuildKata("ORDER");
    INS_TAKE = BuildKata("TAKE");
    INS_CLEAR_TRAY = BuildKata("CT");
    INS_PLACE = BuildKata("PLACE");
    INS_GIVE = BuildKata("GIVE");

    INS_START = BuildKata("START");
    INS_SAVE = BuildKata("SAVE");
    INS_LOAD = BuildKata("LOAD");
    INS_EXIT = BuildKata("EXIT");

    int ret = showIntro();
    while(ret != 0) {
        switch (ret) {
            case 1:
                startGame();
            default:
                ret = showIntro();
        }
    }
}