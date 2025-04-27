/*
    Filename: game.c
    Description: C file to hold all the functions for the game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output:
    Version 5.2
    Log:
      1.0: initial, added map initialisation and printMap()     11/04/2025
        1.1: added comments                                     11/04/2025
      2.0: added junk and asteroid initialisation               11/04/2025
        2.1: added occupied check for junk and asteroid         14/04/2025
      3.0: added ship initialisation                            23/04/2025
      4.0: added colour to the game                             23/04/2025
      5.0: added player movement                                24/04/2025
        5.1: added comments                                     24/04/2025
        5.2: fixed player movement                              24/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "game.h"

// define the map using cells and its size
cell map[MAPSIZE][MAPSIZE];

// function to initialise the map cells
void initMap(){
    printf("\n");
    // loop through the map
    for(int i = 0; i < MAPSIZE; i++){
        for (int j = 0; j < MAPSIZE; j++) {
            // if cell lies on the border, set it to '#' (BORDER)
            if (i == 0 || i == MAPSIZE-1 || j == 0 || j == MAPSIZE-1){
                map[i][j].symbol = BORDER; // set border
                map[i][j].isEmpty = false;
                map[i][j].objPtr = NULL; // no object
            }else{
                map[i][j].symbol = EMPTYSPACE; // whitespace
                map[i][j].isEmpty = true;
                map[i][j].objPtr = NULL; // no object
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
        }while (map[arrJunk[i].pos.y][arrJunk[i].pos.x].isEmpty == false);

        // 1 in 10 chance to be super junk
        arrJunk[i].isSuperJunk = (rand() % 10 == 0);

        // set value based on junk type
        // if super junk, value is between 10 and 20, else 1 to 10
        arrJunk[i].value = arrJunk[i].isSuperJunk ? (10 + rand() % 11) : (1 + rand() % 10);

        // place on map with corresponding symbol and data
        map[arrJunk[i].pos.y][arrJunk[i].pos.x].symbol = arrJunk[i].isSuperJunk ? 'J' : 'j';
        map[arrJunk[i].pos.y][arrJunk[i].pos.x].isEmpty = false;
        map[arrJunk[i].pos.y][arrJunk[i].pos.x].objPtr = &arrJunk[i];
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
        }while (map[arrAsteroid[i].pos.y][arrAsteroid[i].pos.x].isEmpty == false);

        // 1 in 5 chance to be super asteroid
        arrAsteroid[i].isSuperAsteroid = (rand() % 5 == 0);

        // set damage based on asteroid type
        // if super asteroid, damage is between 15 and 25, else 1 to 10
        arrAsteroid[i].dmg = arrAsteroid[i].isSuperAsteroid ? (15 + rand() % 11) : (1 + rand() % 10);

        // place on map with corresponding symbol and data
        map[arrAsteroid[i].pos.y][arrAsteroid[i].pos.x].symbol = arrAsteroid[i].isSuperAsteroid ? 'A' : 'a';
        map[arrAsteroid[i].pos.y][arrAsteroid[i].pos.x].isEmpty = false;
        map[arrAsteroid[i].pos.y][arrAsteroid[i].pos.x].objPtr = &arrAsteroid[i];
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

    // place on map with corresponding symbol and data
    map[player->pos.y][player->pos.x].symbol = 'S';
    map[player->pos.y][player->pos.x].isEmpty = false;
    map[player->pos.y][player->pos.x].objPtr = player;
}

// function to assign colour to the current character
void assignColour(char currentChar) {
    switch (currentChar) {
        case 'J':
            // fallthrough
        case 'j':
            // green junk
            printf("\033[92m%2c\033[0m", currentChar);
            break;
        case 'A':
            // fallthrough
        case 'a':
            // red asteroid
            printf("\033[91m%2c\033[0m", currentChar);
            break;
        case 'S':
            // orange ship
            printf("\033[38;5;208m%2c\033[0m", currentChar);
            break;
        case BORDER:
            // blue border
            printf("\033[94m%2c\033[0m", currentChar);
            break;
        default:
            // 2 whitespace to keep it square
            printf("  ");
    }
}

// function to print the map
void printMap(){
    // clear the screen
    printf("\033[J\033[H");
    for(int i = 0; i < MAPSIZE; i++){
        for (int j = 0; j < MAPSIZE; j++) {
            // output the symbol of the cell
            char currentChar = map[i][j].symbol;
            assignColour(currentChar);
        }
        // print a new line after each row
        printf("\n");
    }
}

void playerMove(int key, ship *player) {
    // store current position
    int oldX = player->pos.x;
    int oldY = player->pos.y;

    // run until key string is found
    do {
        key = getch();
    } while(key == 224);
    // compare the string to the arrow
    switch (key) {
        // up
        case 72:
            // check if next move is not on the border
            if (player->pos.y - 1 > 0) {
                player->pos.y -= 1;
            }
        break;
        // down
        case 80:
            if (player->pos.y + 1 < MAPSIZE - 1) {
                player->pos.y += 1;
            }
        break;
        // left
        case 75:
            if (player->pos.x - 1 > 0) {
                player->pos.x -= 1;
            }
        break;
        // right
        case 77:
            if (player->pos.x + 1 < MAPSIZE - 1) {
                player->pos.x += 1;
            }
        break;
    }
    // clear old position
    map[oldY][oldX].symbol = EMPTYSPACE;
    map[oldY][oldX].isEmpty = true; // set cell to empty
    map[oldY][oldX].objPtr = NULL; // set object pointer to NULL

    // set new position
    map[player->pos.y][player->pos.x].symbol = 'S';
    map[player->pos.y][player->pos.x].isEmpty = false; // not empty
    map[player->pos.y][player->pos.x].objPtr = player; // set object pointer to player
    printMap();
}

void CheckKey(ship *player) {
    int key;
    // check if a key is pressed
    if (kbhit()) {
        // store the code of the key pressed
        key = getch();
        // arrow key code
        if (key == 224) {
            playerMove(key, player);
        }
    }
}