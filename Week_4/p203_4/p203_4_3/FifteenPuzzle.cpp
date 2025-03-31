#include "Ranking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <time.h>

#define DIM 4
#define MAX_FILENAME 100

enum Direction { Left = 68, Right = 67, Up = 65, Down = 66 }; // ←, →, ↑, ↓
static int DirKey[4] = { Left, Right, Up, Down };
static int map[DIM][DIM];
static int x, y;
static int nMove;
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

static void init() {
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;
    map[DIM - 1][DIM - 1] = 0;
    x = DIM - 1;
    y = DIM - 1;

    srand(time(NULL));
    gettimeofday(&tStart, NULL);
    nMove = 0;
}

static void display() {
    system("clear");
    printf("\tFifteen Puzzle\n\t");
    printf("--------------\n\t");
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
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
    printf("\n\t이동 횟수:%6d\n\t경과 시간:%6.1f 초\n", nMove, sec);
    printf("\t'S'를 눌러 게임을 저장하고 종료합니다.\n\n");
}

static bool move(int dir) {
    if (dir == Right && x > 0) {
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    }
    else if (dir == Left && x < DIM - 1) {
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    }
    else if (dir == Up && y < DIM - 1) {
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
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1) && (c == DIM - 1);
        }
    }
    return true;
}

static int getDirKey() {
    int ch = getch();
    if (ch == 27 && getch() == 91) // Arrow key sequence
        return getch();
    return ch; // Return regular character (like 'S' for save)
}

static void saveGame() {
    char filename[MAX_FILENAME];
    printf("저장할 파일 이름을 입력하세요 (확장자 제외): ");
    scanf("%99s", filename);
    strcat(filename, ".dat"); // Add .dat extension

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("게임 저장에 실패했습니다.\n");
        return;
    }

    // Save game state
    fwrite(map, sizeof(int), DIM * DIM, fp);
    fwrite(&x, sizeof(int), 1, fp);
    fwrite(&y, sizeof(int), 1, fp);
    fwrite(&nMove, sizeof(int), 1, fp);
    fwrite(&tStart, sizeof(struct timeval), 1, fp);

    fclose(fp);
    printf("게임이 %s에 저장되었습니다. 프로그램을 종료합니다.\n", filename);
}

static bool loadGame(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return false;
    }

    // Load game state
    fread(map, sizeof(int), DIM * DIM, fp);
    fread(&x, sizeof(int), 1, fp);
    fread(&y, sizeof(int), 1, fp);
    fread(&nMove, sizeof(int), 1, fp);
    fread(&tStart, sizeof(struct timeval), 1, fp);

    fclose(fp);
    return true;
}

int playFifteenPuzzle() {
    char choice;
    printf("새 게임(N) 또는 저장된 게임 불러오기(L)? ");
    scanf(" %c", &choice);

    if (choice == 'L' || choice == 'l') {
        char filename[MAX_FILENAME];
        printf("불러올 파일 이름을 입력하세요 (확장자 제외): ");
        scanf("%99s", filename);
        strcat(filename, ".dat"); // Add .dat extension
        
        if (!loadGame(filename)) {
            printf("파일 %s을(를) 불러오지 못했습니다. 새 게임을 시작합니다.\n", filename);
            init();
        } else {
            printf("%s에서 게임을 성공적으로 불러왔습니다.\n", filename);
        }
    } else {
        init();
    }

    display();
    printRanking();
    printf("\n 아무 키나 눌러 시작하세요...");
    getche();
    shuffle(100);
    printf("\n 퍼즐을 시작합니다...");
    getche();

    nMove = 0;
    gettimeofday(&tStart, NULL);

    while (!isDone()) {
        int key = getDirKey();
        if (key == 'S' || key == 's') {
            saveGame();
            return 0; // Exit without adding to ranking
        }
        move(key);
        display();
    }

    struct timeval tEnd;
    gettimeofday(&tEnd, NULL);
    double sec = elapsedTimeSec(tStart, tEnd);

    return addRanking(nMove, sec);
}