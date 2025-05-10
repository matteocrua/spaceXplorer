/*
    Filename: spaceXplorer.c
    Description: main file for the spaceXplorer game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output: N/A
     Version 7.1
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
      6.0: passed asteroid through checkKey()                   09/05/2025
      7.0: added menu functionality                             10/05/2025
        7.1: added comments                                     10/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "game.h"

// define the number of starting junk and asteroids
const int asteroidCount = 10;
const int junkCount = 10;

// function to display the main menu
void displayMenu() {
    // open file in read mode
    FILE *filePtr = fopen("../mainMenu.txt", "r");

    // read the file and print it
    char ch;
    while ((ch = fgetc(filePtr)) != EOF) {
        // set text colour to yellow
        printf("\033[93m\033[?25l");
        putchar(ch);
        printf("\033[0m");
    }

    // close the file once printed
    fclose(filePtr);
}

// function to view high scores
void viewHighScores() {
    // clear the screen
    printf("\033[H\033[J");

    // open file in read mode
    FILE *fptr = fopen("../highscores.txt", "r");

    // read the file and print it
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }

    // close the file once printed
    fclose(fptr);

    printf("\npress any key to return to menu...");
    // wait for user
    getch();
    // clear the screen
    printf("\033[H\033[J");
}

// function to init and play the game
void playGame() {
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

    // while player is alive and has fuel
    // run game loop
    while (checkStats(&player)) {
        // constantly check key input
        if (kbhit()) {
            checkKey(&player, arrAsteroid, asteroidCount);
        }
    }
}

// main function
int main() {
    // hide cursor
    printf("\033[?25l");
    displayMenu();
    while (1) {
        if (kbhit()) {
            // clear the screen
            printf("\033[H\033[J");
            displayMenu();
            switch (getch()) {
                case 13: // 'Enter' key
                    printf("\033[H\033[J");
                    playGame();
                    displayMenu();
                    break;
                case 104: // 'h' key
                    printf("\033[H\033[J");
                    // view high scores
                    viewHighScores();
                    displayMenu();
                    break;
                case 27: // 'ESC' key
                    // quit
                    exit(0);
                default: break; // invalid key, do nothing
            }
        }
    }
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