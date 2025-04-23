/*
    Filename: game.h
    Description: header file for the game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output: N/A
    Version 1.1
    Log:
      1.0: initial, map size and structs                        11/04/2025
      1.1: added comments                                       11/04/2025
*/
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define MAPSIZE 20      // map size, 0-19 +2 for border
#define BORDER '#'      // border symbol

///// define the ship, junk and asteroid structures /////

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

// asteroid structure with:
// position, super asteroid? and damage
typedef struct{
    coord pos;
    bool isSuperAsteroid;
    int dmg;
}asteroid;

/////////////////////////////////////////////////////////

#endif //GAME_H
