/*
    Filename: spaceXplorer.c
    Description: main file for the spaceXplorer game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output: N/A
    Version 5.0
    Log:
      1.0: initial added initMap() and printMap()               11/04/2025
      2.0: added initJunk() and initAsteroid()                  11/04/2025
        2.1: added comments                                     11/04/2025
      3.0: added ship initialisation                            23/04/2025
      4.0: added player movement test loop                      24/04/2025
        4.1: added comments                                     24/04/2025
        4.2: added hidden cursor                                24/04/2025
        4̶.̶3̶:̶ ̶m̶o̶v̶e̶d̶ ̶a̶s̶t̶e̶r̶o̶i̶d̶ ̶a̶n̶d̶ ̶j̶u̶n̶k̶ ̶c̶o̶u̶n̶t̶ ̶t̶o̶ ̶g̶a̶m̶e̶.̶h̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶ ̶2̶5̶/̶0̶4̶/̶2̶0̶2̶5̶
      5.0: printmap() passes ship object                        30/04/2025
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
    printMap(&player);

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