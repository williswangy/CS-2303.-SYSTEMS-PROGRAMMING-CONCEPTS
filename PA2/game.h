#ifndef GAME_H_
#define GAME_H_
#include <stdio.h>
int onLeft(int X, int Y, int height);
int onTop(int X, int Y, int width);
int onRight(int X, int Y, int width, int height);
int onBottom(int X, int Y, int width, int height);
int onTopLeft(int X, int Y);
int onTopRight(int X, int Y, int width);
int onBottomLeft(int X, int Y, int height);
int onBottomRight(int X, int Y, int width, int height);
int neighbor(int X, int Y, char **curr, int width, int height);
void updategrid(int X, int Y, char **Old, char **New, int width, int height);
void updateall(char **Old, char **New, int width, int height);
int isloop(char **Old, char **New, int width, int height);
#endif
