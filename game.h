/*
    Filename: game.h
    Description: header file for the game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output: N/A
    Version 3.0
    Log:
      1.0: initial, map size and structs                        11/04/2025
        1.1: added comments                                     11/04/2025
        1̶.̶2̶:̶ ̶a̶d̶d̶e̶d̶ ̶j̶u̶n̶k̶ ̶a̶n̶d̶ ̶a̶s̶t̶e̶r̶o̶i̶d̶ ̶c̶o̶u̶n̶t̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶2̶5̶/̶0̶4̶/̶2̶0̶2̶5̶
      2.0: added cell structure for map                         27/04/2025
        2.1: added empty space symbol and comments              27/04/2025
        2.2: changed *objPtr to void* for cell structure        30/04/2025
      3.0: added enum struct for directions
           + updated asteroid struct                            09/05/2025
*/

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define MAPSIZE 20      // map size, 0-19 +2 for border
#define BORDER '#'      // border symbol
#define EMPTYSPACE ' ' // empty space symbol

///// define the ship, junk, asteroid, and cell structures /////

// coordinate structure
typedef struct{
    int x;
    int y;
}coord;

// ship structure with:
// position, health, fuel and total junk collected
typedef struct{
    coord pos;
    int health;
    int fuel;
    int totJunk;
}ship;

// junk structure with:
// position, super junk? and value
typedef struct {
    coord pos;
    bool isSuperJunk;
    int value;
}junk;

// enumerations for direction
typedef enum {
    UP, DOWN, LEFT, RIGHT
}direction;

// asteroid structure with:
// position, super asteroid?, damage and direction
typedef struct{
    coord pos;
    bool isSuperAsteroid;
    int dmg;
    direction dir;
}asteroid;

// cell structure for the map
// currently empty?, symbol of object, and pointer to object
typedef struct {
    bool isEmpty;
    char symbol;
    void *objPtr;
}cell;

////////////////////////////////////////////////////////////////

#endif //GAME_H
