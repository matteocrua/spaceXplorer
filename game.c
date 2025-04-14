/*
Filename: game.c
    Description: C file to hold all the functions for the game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output:
    Version 2.0
    Log:
      1.0: initial, added map initialisation and printMap() 11/04/2025
      1.1: added comments 11/04/2025
      2.0: added junk initialisation 11/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// define the map and its size
char map[MAPSIZE][MAPSIZE];

// function to initialise the map
void initMap(){
    printf("\n");
    // loop through the map
    for(int i = 0; i < MAPSIZE; i++){
        for (int j = 0; j < MAPSIZE; j++) {
            // if cell lies on the border, set it to '#'
            if (i == 0 || i == MAPSIZE-1 || j == 0 || j == MAPSIZE-1){
                map[i][j] = BORDER;
            }
        }
    }
}

void initJunk(junk arrJunk[], int numJunk) {
    // loop through the given number of junk
    for (int i = 0; i < numJunk; i++) {
        // generate random positions avoiding borders
        arrJunk[i].pos.x = 1 + rand() % (MAPSIZE - 2);
        arrJunk[i].pos.y = 1 + rand() % (MAPSIZE - 2);

        // 1 in 5 chance to be super junk
        arrJunk[i].isSuperJunk = (rand() % 10 == 0);

        // set value based on junk type
        // if super junk, value is 50, else 10
        arrJunk[i].value = arrJunk[i].isSuperJunk ? 20 : 10;

        // place on map with corresponding symbol
        map[arrJunk[i].pos.y][arrJunk[i].pos.x] = arrJunk[i].isSuperJunk ? 'J' : 'j';
    }
}

// function to initialise the asteroids
void initAsteroid(asteroid arrAsteroid[], int numAsteroid) {
    // loop through the given number of asteroids
    for (int i = 0; i < numAsteroid; i++) {
        // generate random positions avoiding borders
        arrAsteroid[i].pos.x = 1 + rand() % (MAPSIZE - 2);
        arrAsteroid[i].pos.y = 1 + rand() % (MAPSIZE - 2);

        // 1 in 5 chance to be super asteroid
        arrAsteroid[i].isSuperAsteroid = (rand() % 5 == 0);

        // set damage based on asteroid type
        // if super asteroid, damage is 20, else 10
        arrAsteroid[i].dmg = arrAsteroid[i].isSuperAsteroid ? 20 : 10;

        // place on map with corresponding symbol
        map[arrAsteroid[i].pos.y][arrAsteroid[i].pos.x] = arrAsteroid[i].isSuperAsteroid ? 'A' : 'a';
    }
}

// function to print the map
void printMap(){
    for(int i = 0; i < MAPSIZE; i++){
        for (int j = 0; j < MAPSIZE; j++){
            printf("%c  ", map[i][j]);
        }
        printf("\n");
    }
}
