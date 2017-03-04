#include<stdio.h>
#include<stdlib.h>
#include"file.h"

//count how many characters are there in a line
int charCounter(FILE *input){
    int count = 0;
    char c;
    while((c = fgetc(input)) != '\n') {
        if(c == EOF) {
            return count;
        }
        count++;
    }
    return count;
}

//count how many lines are there in the input file
// This function calls REWIND when exits
int lineCounter(FILE *input)
{
    int linecount = 0;
    char c;
    while ((c = fgetc(input)) != EOF) {
        if(c == '\n') {
            ++ linecount;
        }
    }
    rewind(input);
    return linecount;
}

//determine the start point where start to pass in the input file into each row
int wherePut(int linelen, int charinline) {
    return ((linelen / 2) - (charinline / 2));
}

//determine the start point in y where to pass in
int wherePuty(int linecount, int giveny) {
    return ((giveny-linecount) / 2);
}

//initialize a line in the 2-d array
void putLine(int linelen, int charinline, char *curr, FILE *input) {
    int i = 0;
    
    for(i = wherePut(linelen, charinline); i < (charinline + wherePut(linelen, charinline)); i++){
        curr[i] = fgetc(input);
    }
    fgetc(input);
}
