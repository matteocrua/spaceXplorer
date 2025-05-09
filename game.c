/*
    Filename: game.c
    Description: C file to hold all the functions for the game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output:
    Version 8.1
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
        5.3: added hidden cursor                                24/04/2025
        5.4: simplified map colour assignment                   30/04/2025
      6.0: added stats display                                  30/04/2025
        6.1: added comments                                     30/04/2025
      7.0: added collision checking and effects,
           and shortened parts of code                          30/04/2025
        7.1: added comments                                     30/04/2025
        7.2: added check for player health and fuel
             with end condition                                 30/04/2025
      8.0: added asteroid movement                              09/05/2025
        8.1: added comments                                     09/05/2025
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

        // assign random direction
        // 0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
        arrAsteroid[i].dir = rand() % 4;

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

void displayStats(ship *player) {
    // store the player health and fuel
    int health = player->health;
    int fuel = player->fuel;

    // print the health bar
    printf("| HP:%3d [", health);
    for (int i = 0; i < 10; i++) {
        if (i< health/10) {
            printf("\033[101m \033[0m"); // red
        }else {
            printf("\033[100m \033[0m"); // grey
        }
    }
    printf("] | ");

    // print the fuel bar
    printf("Fuel:%3d [", fuel);
    for (int i = 0; i < 10; i++) {
        if (i< fuel/10) {
            printf("\033[43m \033[0m"); // yellow
        }else {
            printf("\033[100m \033[0m"); // grey
        }
    }
    printf("] | ");

    // print the total junk collected
    printf("Total Junk:%3d |", player->totJunk);
}

// function to print the map
void printMap(ship *player) {
    // clear the screen
    printf("\033[J\033[H");
    for(int i = 0; i < MAPSIZE; i++){
        // indent the map to align with the stats
        printf("           ");
        for (int j = 0; j < MAPSIZE; j++) {
            // output the symbol of the cell
            assignColour(map[i][j].symbol);
        }
        // print a new line after each row
        printf("\n");
    }
    // print the stats
    displayStats(player);
}

// function to move asteroids
void moveAsteroids(asteroid arrAsteroid[], int numAsteroid, ship *player) {
    for (int i = 0; i < numAsteroid; i++) {
        // current position
        int oldX = arrAsteroid[i].pos.x;
        int oldY = arrAsteroid[i].pos.y;

        // define new position
        int newX = oldX;
        int newY = oldY;

        // change coordinate based on direction
        switch (arrAsteroid[i].dir) {
            case UP:    newY = oldY - 1; break;
            case DOWN:  newY = oldY + 1; break;
            case LEFT:  newX = oldX - 1; break;
            case RIGHT: newX = oldX + 1; break;
        }

        // check if hits ship
        if (map[newY][newX].symbol == 'S') {
            player->health -= arrAsteroid[i].dmg; // reduce health
        }
        // check if cell is empty
        else if (map[newY][newX].isEmpty) {
            // clear old position
            map[oldY][oldX].symbol = EMPTYSPACE;
            map[oldY][oldX].isEmpty = true;
            map[oldY][oldX].objPtr = NULL;

            // update asteroid position
            arrAsteroid[i].pos.x = newX;
            arrAsteroid[i].pos.y = newY;

            // update map
            map[newY][newX].symbol = arrAsteroid[i].isSuperAsteroid ? 'A' : 'a';
            map[newY][newX].isEmpty = false;
            map[newY][newX].objPtr = &arrAsteroid[i];
        }
        // hit junk, asteroid, or BORDER
        else {
            // clear old position
            map[oldY][oldX].symbol = EMPTYSPACE;
            map[oldY][oldX].isEmpty = true;
            map[oldY][oldX].objPtr = NULL;

            // respawn the asteroid
            spawnAsteroid(&arrAsteroid[i], 1);
        }
    }
}

// function to check the players health and fuel
bool checkStats(ship *player) {
    // check if the player is dead
    if (player->health <= 0) {
        printf("\033[2J\033[H");
        printf("\n\nYou have died!\n");
        return false; // game over
    }
    // check if the player is out of fuel
    if (player->fuel <= 0) {
        printf("\033[2J\033[H");
        printf("\n\nYou have run out of fuel!\n");
        return false; // game over
    }
    return true; // game continues
}

// function to check for collision
bool checkCollision(ship *player, int newY, int newX) {

    // check if the new position is occupied
    if (map[newY][newX].isEmpty == false) {
        switch (map[newY][newX].symbol) {
            case 'J':
            case 'j':
                // collect junk and increase total junk collected
                // type cast the object pointer to junk to access its value
                player->totJunk += ((junk *)map[newY][newX].objPtr)->value;
                player->fuel--; // deduct 1 fuel
                return true; // can move onto junk
            case 'A':
            case 'a':
                // reduce health based on damage
                // type cast the object pointer to asteroid to access its damage
                player->health -= ((asteroid *)map[newY][newX].objPtr)->dmg;
                player->fuel--; // deduct 1 fuel
                return false; // cannot move onto asteroid
            // collision with border or unknown, do nothing
            case BORDER:
            default: return false;
        }
    }
    player->fuel--; // deduct 1 fuel
    return true; // can move onto empty space
}

// function to move the player
void playerMove(int key, ship *player, asteroid arrAsteroid[], int asteroidCount) {
    // store current position
    int oldX = player->pos.x;
    int oldY = player->pos.y;

    // temp new position values
    int newX = oldX;
    int newY = oldY;

    // run until key string is found
    do { key = getch(); } while(key == 224);

    // compare the string to the arrow
    switch (key) {
        // up
        case 72: newY = oldY - 1; break;
        // down
        case 80: newY = oldY + 1; break;
        // left
        case 75: newX = oldX - 1; break;
        // right
        case 77: newX = oldX + 1; break;
        // invalid key, do nothing
        default: break;
    }

    // if checkCollision returns true, move the player
    if (checkCollision(player, newY, newX)) {
        // clear old position
        map[oldY][oldX].symbol = EMPTYSPACE;
        map[oldY][oldX].isEmpty = true; // set cell to empty
        map[oldY][oldX].objPtr = NULL; // set object pointer to NULL

        // update player position
        player->pos.x = newX;
        player->pos.y = newY;

        // set new position
        map[newY][newX].symbol = 'S';
        map[newY][newX].isEmpty = false; // not empty
        map[newY][newX].objPtr = player; // set object pointer to player
    }

    if (checkStats(player) == false) {
        getchar();
        exit(0);
    }

    moveAsteroids(arrAsteroid, asteroidCount, player);
    printMap(player);
}

void CheckKey(ship *player, asteroid arrAsteroid[], int asteroidCount) {
    int key;
    // check if a key is pressed
    if (kbhit()) {
        // store the code of the key pressed
        key = getch();
        // arrow key code
        if (key == 224) {
            playerMove(key, player, arrAsteroid, asteroidCount);
        }
    }
}