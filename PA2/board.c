#include<stdio.h>
#include<stdlib.h>
#include"board.h"
#include"game.h"

// print the given array
void arrayprint(char **array, int width, int height) {
	int i = 1;
	int s = 1;
	for(i = 1; i <= height; i++) {
        	for(s = 1; s <= width; s ++) {
            		printf("%c", array[i-1][s-1]);
        }
        printf("\n");
    }
}
//print and pause commands
void printAndpause(char print, char pause, char **curr, int width, int height, int gen) {
	if(print == 'y') {
		printf("This is the %d generation\n", gen);
		arrayprint(curr, width, height);
	}
	if(pause == 'y') {
		printf("Press enter to continue...\n");
		getchar();
	}
	else printf("\n");
}
