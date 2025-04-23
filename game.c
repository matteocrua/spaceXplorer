/*
    Filename: game.c
    Description: C file to hold all the functions for the game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output:
    Version 3.0
    Log:
      1.0: initial, added map initialisation and printMap()     11/04/2025
      1.1: added comments                                       11/04/2025
      2.0: added junk and asteroid initialisation               11/04/2025
      2.1: added occupied check for junk and asteroid           14/04/2025
      3.0: added ship initialisation                            23/04/2025
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
            }else{
                map[i][j] = ' '; // set empty cell
            }
        }
    }
}

// function to spawn the junk
void spawnJunk(junk arrJunk[], int numJunk) {
    // loop through the given number of junk
    for (int i = 0; i < numJunk; i++) {
        // check if current cell is empty
        do {
            // generate random positions avoiding borders
            arrJunk[i].pos.x = 1 + rand() % (MAPSIZE - 2);
            arrJunk[i].pos.y = 1 + rand() % (MAPSIZE - 2);

        }while (map[arrJunk[i].pos.y][arrJunk[i].pos.x] != ' ');

        // 1 in 10 chance to be super junk
        arrJunk[i].isSuperJunk = (rand() % 10 == 0);

        // set value based on junk type
        // if super junk, value is 20, else 10
        arrJunk[i].value = arrJunk[i].isSuperJunk ? 20 : 10;

        // place on map with corresponding symbol
        map[arrJunk[i].pos.y][arrJunk[i].pos.x] = arrJunk[i].isSuperJunk ? 'J' : 'j';
    }
}

// function to spawn the asteroids
void spawnAsteroid(asteroid arrAsteroid[], int numAsteroid) {
    // loop through the given number of asteroids
    for (int i = 0; i < numAsteroid; i++) {
        // check if current cell is empty
        do {
            // generate random positions avoiding borders
            arrAsteroid[i].pos.x = 1 + rand() % (MAPSIZE - 2);
            arrAsteroid[i].pos.y = 1 + rand() % (MAPSIZE - 2);

        }while (map[arrAsteroid[i].pos.y][arrAsteroid[i].pos.x] != ' ');

        // 1 in 5 chance to be super asteroid
        arrAsteroid[i].isSuperAsteroid = (rand() % 5 == 0);

        // set damage based on asteroid type
        // if super asteroid, damage is 20, else 10
        arrAsteroid[i].dmg = arrAsteroid[i].isSuperAsteroid ? 20 : 10;

        // place on map with corresponding symbol
        map[arrAsteroid[i].pos.y][arrAsteroid[i].pos.x] = arrAsteroid[i].isSuperAsteroid ? 'A' : 'a';
    }
}

// function to initialise the ship
// we want to modify the ship object so a pointer is used
void initShip(ship *player) {
    // set ship position to the centre of the map
    player->pos.x = MAPSIZE / 2;
    player->pos.y = MAPSIZE / 2;

    // set initial health, fuel and total junk collected
    player->health = 100;
    player->fuel = 100;
    player->totJunk = 0;

    // place on map with corresponding symbol
    map[player->pos.y][player->pos.x] = 'S';
}

// function to print the map
void printMap(){
    for(int i = 0; i < MAPSIZE; i++){
        for (int j = 0; j < MAPSIZE; j++){
            // 3 spaces for each cell
            // to make map look square
            printf("%3c", map[i][j]);
        }
        printf("\n");
    }
}
