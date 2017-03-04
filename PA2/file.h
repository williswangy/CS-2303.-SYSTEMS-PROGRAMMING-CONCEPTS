#ifndef FILE_H_
#define FILE_H_
#include<stdio.h>
#include<stdlib.h>
int charCounter(FILE *input);
int lineCounter(FILE *input);
int wherepPut(int linelen, int charinline);
int wherePuty(int linecount, int giveny);
void putLine(int linelen, int charinline, char *curr, FILE *input);
#endif
