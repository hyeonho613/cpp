#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <memory.h>
#include <time.h>
#include <ctype.h>

#define MAX_HEIGHT 40
#define MAX_WIDTH 80

extern int nx, ny;
extern void playMineSweeper(int nBomb = 13);