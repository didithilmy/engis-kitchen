/**
 * Engi's Kitchen Expansion
 * Mesin Karakter abstraction
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file mesin_kar.c
 */


#include "../mesin_kar.h"

// Variable definitions
char CC;
boolean EOP;
int CCi;

static char *pita;

/**
 * Opens file and select the first character (Adv)
 * @param filename File name
 * @post CC is the first character of the ribbon. If CC is mark, EOP is true
 */
void START(char *string) {
    CCi = 0;
    pita = string;
    ADV();
}

/**
 * Advance to the next character
 * If the advanced character is MARK, close the file
 * @pre Selected character is on CC and CC is not MARK
 * @post CC is the next character. CC could be MARK, if it is, EOP is true
 */
void ADV() {
    CC = pita[CCi];
    CCi++;

    EOP = (CC == MARK);
}

/**
 * CC getter
 * Gets the current character
 * @return Current character
 * @pre CC is assigned
 */
char GetCC() {
    return CC;
}

/**
 * Returns if CC is the MARK (end of ribbon)
 * @return is EOP
 * @pre CC is assigned
 */
boolean IsEOP() {
    return CC == MARK;
}

/**
 * Change char to uppercase
 * @param lower lowercase char
 * @return uppercase char
 */
char ToUpper(char lower) {
    if(lower >= 'a' && lower <= 'z') {
        return (char) (lower - 32);
    } else {
        return lower;
    }
}