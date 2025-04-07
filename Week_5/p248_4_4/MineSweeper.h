#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <memory.h>
#include <time.h>
#include <ctype.h>

#define DIM 9 // 원본 고정 크기

extern void playMineSweeper(int nBomb = 13);