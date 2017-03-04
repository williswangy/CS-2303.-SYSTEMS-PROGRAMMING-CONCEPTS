#include<stdio.h>
#include<stdlib.h>
#include"game.h"

//X here is width, Y is height

//check if this grid is on the left edge of the board
int onLeft(int X, int Y, int height) {
    if(X == 0) {
        return 1;
    }
    else return 0;
}

//check if this grid is on the top edge of the board
int onTop(int X, int Y, int width) {
    if(Y == 0) {
        return 1;
    }
    else return 0;
}

//check if this grid is on the right edge of the board
int onRight(int X, int Y, int width, int height) {
    if(X == (width - 1)) {
        return 1;
    }
    else return 0;
}

//check if this grid is on the bottom edge of the board
int onBottom(int X, int Y, int width, int height) {
    if(Y == (height - 1)) {
        return 1;
    }
    else return 0;
}

//check if this grid is on the top left
int onTopLeft(int X, int Y) {
    if(X == 0 && Y == 0) {
        return 1;
    }
    else return 0;
}

//check if this grid is on the top right
int onTopRight(int X, int Y, int width) {
    if(X == (width - 1) && Y == 0) {
        return 1;
    }
    else return 0;
}

//check if this grid is on the bottom left
int onBottomLeft(int X, int Y, int height) {
    if(Y == (height - 1) && X == 0) {
        return 1;
    }
    else return 0;
}

//check if this grid is on the bottom right
int onBottomRight(int X, int Y, int width, int height) {
    if(Y == (height - 1) && X == (width -1)) {
        return 1;
    }
    else return 0;
}


//count the number of neighbors
int neighbor(int X, int Y, char **curr, int width, int height) {

    int count = 0;

    if(!onTop(X, Y, width)) {
        if(curr[Y-1][X] == 'x'){
            count ++;
        }
	if(!onLeft(X, Y, height)) {
		if(curr[Y-1][X-1] == 'x'){
            		count ++;
        	}
	}
    }
    

    if(!onRight(X, Y, width, height)) {
        if(curr[Y][X+1] == 'x'){
            count ++;
        }
        if(!onTop(X, Y, width)) {
		if(curr[Y-1][X+1] == 'x'){
            		count ++;
        	}
	}
    }
    
    
    if(!onBottom(X, Y, width,height)){
        if(curr[Y+1][X] == 'x'){
            count ++;
        }
	if(!onRight(X, Y, width, height)) {
		if(curr[Y+1][X+1] == 'x'){
            		count ++;
        	}
	}
    }
    
    
    
    if(!onLeft(X, Y, height)){
        if(curr[Y][X-1] == 'x') {
            count ++;
	}
	if(!onBottom(X, Y, width, height)) {
		if(curr[Y+1][X-1] == 'x'){
			count ++;
		}
	}
    }
    
    return count;
}



//update one grid by the number of neighbors and store the value in a second array

void updategrid(int X, int Y, char **Old, char **New, int width, int height) {
        int adj = neighbor(X, Y, Old, width, height);
	if(Old[Y][X] == 'x') {
		if(adj == (0 | 1 | 4 | 5 | 6 | 7 | 8)) {
			New[Y][X] = 'o';
		}
		else {
			New[Y][X] = 'x';
		}
	}
	else if(Old[Y][X] == 'o') {
		if(adj == 3) {
			New[Y][X] = 'x';
		}
	}
}

//update all grids
void updateall(char **Old, char **New, int width, int height) {
	int i = 1;
	int s = 1;
	for(i = 1; i <= height; i++) {
        	for(s = 1; s <= width; s ++) {
	 		updategrid((i-1), (s-1), Old, New, width, height);
       		 }
	}
}
//deternmine whether the old and new are the same
int isloop(char **Old, char **New, int width, int height) {
	int i = 1;
	int s = 1;
	int checker = 1;
	for(i = 1; i <= height; i++) {
        	for(s = 1; s <= width; s ++) {
	 		checker = (checker && ((Old[i-1][s-1]) == (New[i-1][s-1])) );
       		 }
	}
	return checker;
}	
	



