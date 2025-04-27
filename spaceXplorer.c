/*
    Filename: spaceXplorer.c
    Description: main file for the spaceXplorer game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output: N/A
    Version 4.3
    Log:
      1.0: initial added initMap() and printMap()               11/04/2025
      2.0: added initJunk() and initAsteroid()                  11/04/2025
        2.1: added comments                                     11/04/2025
      3.0: added ship initialisation                            23/04/2025
      4.0: added player movement test loop                      24/04/2025
        4.1: added comments                                     24/04/2025
        4.2: added hidden cursor                                24/04/2025
        4.3: moved asteroid and junk count to game.h            25/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "game.h"

// define the number of starting junk and asteroids
const int asteroidCount = 10;
const int junkCount = 10;

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

    // test loop for player movement
    while (1) {
        // hide cursor
        printf("\033[?25l");
        if (kbhit()) {
            CheckKey(&player);
        }
    }

    // pause for testing purpose
    //getchar();
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