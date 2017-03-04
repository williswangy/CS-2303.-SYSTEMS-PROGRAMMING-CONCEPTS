/*
======================================================================
Name: YUAN WANG's Life Game
Auther: Yuan Wang
Version: 1.00
Description: Display the Life Game with the user's instruction
======================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include"board.h"
#include"game.h"
#include"file.h"

//This is the main function
int main(int argc, char *argv[])
{
    //check if the arguements given meet the requirement
    if(argc < 5) {
        printf("Not enough input, please read the instruction for more information. \n");
        return 0;
    }
    
    // initialize the row x and column y
    unsigned int x = atoi(argv[1]);
    
    unsigned int y = atoi(argv[2]);
    
    
    
    //allocate the memory for the 2-D arrays
    //y rows and x columns
    int i = 0;
    
    char **A = malloc(y*sizeof(char*));
    
    for(i = 0; i < y; i++) {
        A[i] = malloc(x*sizeof(char));
    }
    
    char **B = malloc(y*sizeof(char*));
    
    for(i = 0; i < y; i++) {
        B[i] = malloc(x*sizeof(char));
    }
    
    char **C = malloc(y*sizeof(char*));
    
    for(i = 0; i < y; i++) {
        C[i] = malloc(x*sizeof(char));
    }

    //initialize gens that indicates
    int gens = atoi(argv[3]);
    if(gens <= 0) {
        printf("Gens must be greater than zero, please read the instruction for more information. \n");
        return 0;
    }
    
    //open the file the user gives
    FILE *input = fopen(argv[4], "r");
    if (!input) {
        printf("Can't open file, please check your file name and try again. \n");
        return 0;
    }
    
    //initialize print and pause
    
    char print;
    char pause;
    
    if(argc >=6) {
        print = *argv[5];
    }
    else {
        print = 'n';
        pause = 'n';
    }
    
    if(argc >=7) {
        pause = *argv[6];
    }
    else {
        pause = 'n';
    }
    //the number of lines
    int linenumber = lineCounter(input);
    
    //create an arrya that hold the number of characters in each line
    int *charofline = malloc((sizeof(int))*linenumber);
    for(i = 1; i <= linenumber; i++) {
        *(charofline + (i-1)) = charCounter(input);
    }
    rewind(input);
 
    //check if the file given is larger than the play board
    //find the largest line number
    int max = 0;
    for(i = 0; i <= linenumber; i++) {
	if(charofline[i] > max) {
		max = charofline[i];
		}
	}

    if(max > x) {
	printf("The characters in one of the lines are larger than the columns you give!\n");
	return 0;
	}
    if(linenumber > y) {
	printf("The number of lines in your input file is larger than the rows you give!\n");
	return 0;
	}

    //initialize a new tracker 
    int s = 0;
    //initialize the board
    for(i = 1; i <= y; i++) {
        for(s = 1; s <= x; s ++) {
            A[i-1][s-1] = 'o';
        }
    }
    for(i = 1; i <= y; i++) {
        for(s = 1; s <= x; s ++) {
            B[i-1][s-1] = 'o';
        }
    }
    for(i = 1; i <= y; i++) {
        for(s = 1; s <= x; s ++) {
            C[i-1][s-1] = 'o';
        }
    }


    rewind(input);
    //pass the input file in the array
    for(i = wherePuty(linenumber, y); i <= (wherePuty(linenumber, y) + linenumber - 1); i++) {
            putLine(x, charofline[(i - wherePuty(linenumber, y))], A[i], input); 
    }
    rewind(input);


    //game
    printf("---Press enter to continue...\n");
    getchar();
    printf("----------------- Welcome to Yuan Wang's Game of Life! -----------------\n");
    if(gens <= 1) {
   	 printf("The max generation is %d round\n", gens);
	}
    if(gens > 1) {
   	 printf("The max generation is %d rounds\n", gens);
	}
    if(print == 'n') {
	printf("Your setting for printing each generation is NO.\n");
	}
    if(print == 'y') {
	printf("Your setting for printing each generation is Yes.\n");
	}
    if(pause == 'n') {
	printf("Your setting for pausing at each generation is NO.\n");
	}
    if(pause == 'y') {
	printf("Your setting for pausing at each generation is Yes.\n");
	}


   	int gencounter = 0;
	printf("---Press enter to start the game...\n");
	printf("This is the 0 generation from your input file.\n");
	arrayprint(A, x, y);
    	getchar();
	while(gencounter <= gens) {
//update A as old, B as new
		if(gencounter >= gens) {
			printf("Terminated at gen: %d, reason: max generation reached\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		if(isloop(C, A, x, y)) {
			printf("Terminated at gen: %d, reason: loop entered\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		if(isloop(B, A, x, y)) {
			printf("Terminated at gen: %d, reason: loop entered\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		
		updateall(A, B, x, y);
		gencounter ++;
		printAndpause(print, pause, B, x, y, gencounter);
//update B as old, C as new
		if(gencounter >= gens) {
			printf("Terminated at gen: %d, reason: max generation reached\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		if(isloop(A, B, x, y)) {
			printf("Terminated at gen: %d, reason: loop entered\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		if(isloop(A, C, x, y)) {
			printf("Terminated at gen: %d, reason: loop entered\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		
		updateall(B, C, x, y);
		gencounter ++;
		printAndpause(print, pause, C, x, y, gencounter);
//update C as old, A as new
		if(gencounter >= gens) {
			printf("Terminated at gen: %d, reason: max generation reached\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		if(isloop(B, C, x, y)) {
			printf("Terminated at gen: %d, reason: loop entered\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		if(isloop(C, A, x, y)) {
			printf("Terminated at gen: %d, reason: loop entered\n", gencounter);
			printf("Press enter to show your final board\n");
			getchar();
			arrayprint(C, x, y);
			return 0;
		}
		
		updateall(C, A, x, y);
		gencounter ++;
		printAndpause(print, pause, A, x, y, gencounter);
	}
		

    //free the memory 
    for(i = 0; i < y; i++) {
        free(A[i]);
    }
    free(A);
    
    for(i = 0; i < y; i++) {
        free(B[i]);
    }
    free(B);

    
    for(i = 0; i < y; i++) {
        free(C[i]);
    }
    free(C);

    free(charofline);
    
    //close the file 
    fclose(input);
    return 0;
}



