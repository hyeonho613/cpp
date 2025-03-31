#include "Ranking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <time.h>

#define MAX_DIM 5

enum Direction { Left = 68, Right = 67, Up = 65, Down = 66 }; // ←, →, ↑, ↓
static int DirKey[4] = { Left, Right, Up, Down };
static int map[MAX_DIM][MAX_DIM];
static int x, y;
static int nMove;
static int dim = 4; // 기본값은 4
static struct timeval tStart;

// getch() & getche()
static int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(0, TCSANOW, &oldt);
    return ch;
}
static int getche() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(0, TCSANOW, &oldt);
    return ch;
}

// 경과 시간 (초 단위, double)
static double elapsedTimeSec(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
}

static void inputPuzzleSize() {
    int input;
    printf("맵 크기를 입력하세요 (3~5): ");
    scanf("%d", &input);
    if (input >= 3 && input <= 5) {
        dim = input;
    } else {
        printf("잘못된 입력입니다. 기본값 4로 설정합니다.\n");
        dim = 4;
    }
}

static void init() {
    for (int i = 0; i < dim * dim - 1; i++)
        map[i / dim][i % dim] = i + 1;
    map[dim - 1][dim - 1] = 0;
    x = dim - 1;
    y = dim - 1;

    srand(time(NULL));
    gettimeofday(&tStart, NULL);
    nMove = 0;
}

static void display() {
    system("clear");
    printf("\tFifteen Puzzle\n\t");
    printf("--------------\n\t");
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            if (map[r][c] > 0)
                printf("%3d", map[r][c]);
            else
                printf("   ");
        }
        printf("\n\t");
    }
    printf("--------------\n\t");

    struct timeval now;
    gettimeofday(&now, NULL);
    double sec = elapsedTimeSec(tStart, now);
    printf("\n\t이동 횟수:%6d\n\t경과 시간:%6.1f 초\n\n", nMove, sec);
}

static bool move(int dir) {
    if (dir == Right && x > 0) {
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    }
    else if (dir == Left && x < dim - 1) {
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    }
    else if (dir == Up && y < dim - 1) {
        map[y][x] = map[y + 1][x];
        map[++y][x] = 0;
    }
    else if (dir == Down && y > 0) {
        map[y][x] = map[y - 1][x];
        map[--y][x] = 0;
    }
    else return false;

    nMove++;
    return true;
}

static void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        int key = DirKey[rand() % 4];
        if (!move(key)) {
            i--;
            continue;
        }
        display();
        usleep(50000); // 50ms
    }
}

static bool isDone() {
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            if (map[r][c] != r * dim + c + 1)
                return (r == dim - 1) && (c == dim - 1);
        }
    }
    return true;
}

static int getDirKey() {
    if (getch() == 27 && getch() == 91)
        return getch();
    return 0;
}

int playFifteenPuzzle() {
    inputPuzzleSize();
    init();
    display();
    printRanking();
    printf("\n 엔터키를 눌러 시작하세요...");
    getche();
    shuffle(100);
    printf("\n 퍼즐을 시작합니다...");
    getche();

    nMove = 0;
    gettimeofday(&tStart, NULL);

    while (!isDone()) {
        move(getDirKey());
        display();
    }

    struct timeval tEnd;
    gettimeofday(&tEnd, NULL);
    double sec = elapsedTimeSec(tStart, tEnd);

    return addRanking(nMove, sec); // 초 단위 그대로 넘김
}
