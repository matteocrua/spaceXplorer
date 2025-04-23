/*
    Filename: spaceXplorer.c
    Description: main file for the spaceXplorer game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output: N/A
    Version 3.0
    Log:
      1.0: initial added initMap() and printMap()               11/04/2025
      2.0: added initJunk() and initAsteroid()                  11/04/2025
        2.1: added comments                                     11/04/2025
      3.0: added ship initialisation                            23/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// define the number of starting junk and asteroids
int asteroidCount = 10;
int junkCount = 10;

int main() {
    // seed the random number generator
    srand(time(NULL));

    // declare the objects
    junk arrJunk[junkCount];
    asteroid arrAsteroid[asteroidCount];
    ship player;

    // initialise the objects
    initMap();
    initShip(&player);
    spawnAsteroid(arrAsteroid, asteroidCount);
    spawnJunk(arrJunk, junkCount);

    // print the map
    printMap();

    // pause for testing purpose
    getchar();
}


/*
　　　　　 　          ____
　　　　　        ／ フ　　  フ
　　　　　        |  　_　 _|
　 　　　        ／ ` ミ＿xノ
　　 　         /　 　　   |
　　　         /　 ヽ 　　 ﾉ
　 　         │　　 |　|　|
　        ／￣|　　 |　|　|
         | (￣ヽ＿ヽ)__)__)
         ＼ 二つ
*/