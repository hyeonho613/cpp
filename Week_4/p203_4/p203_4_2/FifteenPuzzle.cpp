#include "Ranking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <time.h>
#include <vector>

#define MAX_DIM 5

enum Direction { Left = 68, Right = 67, Up = 65, Down = 66 }; // ←, →, ↑, ↓
static int DirKey[4] = { Left, Right, Up, Down };
static int map[MAX_DIM][MAX_DIM];
static int replayMap[MAX_DIM][MAX_DIM]; // 리플레이용 맵 저장
static int x, y;
static int replayX, replayY;            // 리플레이 시작 위치
static int nMove;
static int dim = 4; // 기본값은 4
static struct timeval tStart;
static std::vector<int> moveHistory;    // 이동 히스토리
static bool isReplayMode = false;

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

// 경과 시간 (초 단위)
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

    if (!isReplayMode) {
        struct timeval now;
        gettimeofday(&now, NULL);
        double sec = elapsedTimeSec(tStart, now);
        printf("\n\t이동 횟수:%6d\n\t경과 시간:%6.1f 초\n\n", nMove, sec);
    } else {
        printf("\n\t(리플레이 중 - 시간 및 이동 수 미표시)\n\n");
    }
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

    if (!isReplayMode) {
        nMove++;
        moveHistory.push_back(dir); // 이동 저장
    }

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

    // 섞은 직후 상태 저장
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            replayMap[r][c] = map[r][c];
            if (map[r][c] == 0) {
                replayX = c;
                replayY = r;
            }
        }
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

static void replay() {
    printf("\n=== 리플레이 시작 ===\n");
    isReplayMode = true;

    for (int r = 0; r < dim; r++)
        for (int c = 0; c < dim; c++)
            map[r][c] = replayMap[r][c];
    x = replayX;
    y = replayY;
    nMove = 0;

    for (int dir : moveHistory) {
        move(dir);
        display();
        usleep(200000); // 200ms
    }

    printf("\n=== 리플레이 종료 ===\n");
    getche();
    isReplayMode = false;
}

int playFifteenPuzzle() {
    inputPuzzleSize();
    init();
    display();
    printRanking();
    printf("\n 엔터키를 눌러 시작하세요...");
    getche();

    shuffle(100);  // 섞은 직후 상태 저장됨

    printf("\n 퍼즐을 시작합니다...");
    getche();

    moveHistory.clear();  // 이동 기록 초기화
    nMove = 0;
    gettimeofday(&tStart, NULL);

    while (!isDone()) {
        move(getDirKey());
        display();
    }

    struct timeval tEnd;
    gettimeofday(&tEnd, NULL);
    double sec = elapsedTimeSec(tStart, tEnd);

    replay(); // 게임 끝나고 리플레이

    return addRanking(nMove, sec);
}
