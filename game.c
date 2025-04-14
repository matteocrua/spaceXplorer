/*
Filename: game.c
    Description: C file to hold all the functions for the game
    Author: Matteo Crua
    Date: 11/04/2025
    Input/Output:
    Version 1.1
    Log:
      1.0: initial, added map initialisation and printMap() 11/04/2025
      1.1: added comments 11/04/2025
*/

#include <stdio.h>
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

// function to print the map
void printMap(){
    for(int i = 0; i < MAPSIZE; i++){
        for (int j = 0; j < MAPSIZE; j++){
            printf("%c  ", map[i][j]);
        }
        printf("\n");
    }
}
