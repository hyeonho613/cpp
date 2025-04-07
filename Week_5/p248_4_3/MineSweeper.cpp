#include "MineSweeper.h"

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };
static int MineMapMask[MAX_HEIGHT][MAX_WIDTH];
static int MineMapLabel[MAX_HEIGHT][MAX_WIDTH];
int nx, ny;
static int nBomb;

inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

static void dig(int x, int y) {
    if (isValid(x, y) && mask(x, y) != Open) {
        mask(x, y) = Open;
        if (label(x, y) == 0) {
            dig(x - 1, y - 1); dig(x - 1, y); dig(x - 1, y + 1);
            dig(x, y - 1); dig(x, y + 1);
            dig(x + 1, y - 1); dig(x + 1, y); dig(x + 1, y + 1);
        }
    }
}

static void mark(int x, int y) {
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;
}

static int getBombCount() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag) count++;
    return count;
}

static void print() {
    system("clear");
    printf("   깃발:%2d   전체:%2d\n", getBombCount(), nBomb);
    printf("    "); // 세로축 라벨(1 )의 3칸에 맞춰 공백
    for (int x = 0; x < nx; x++) {
        if (x < 8)
            printf("%d ", x + 1); // 1~8까지 1칸 띄움
        else
            printf("%d", x + 1);  // 9부터 공백 없이 붙임
    }
    printf("\n");
    for (int y = 0; y < ny; y++) {
        printf("%2d ", y + 1); // 세로축을 숫자로 변경 (1부터 시작)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) == Hide) printf("⬜");      // 공백 제거
            else if (mask(x, y) == Flag) printf("🚩"); // 공백 제거
            else {
                if (isBomb(x, y)) printf("💣");        // 공백 제거
                else if (isEmpty(x, y)) printf(" ");   // 1칸 공백
                else printf("%d", label(x, y));        // 1칸 숫자
            }
        }
        printf("\n");
    }
}

static int countNbrBombs(int x, int y) {
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy) && label(xx, yy) == Bomb)
                count++;
    return count;
}

static void init(int total) {
    srand((unsigned int)time(NULL));
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            mask(x, y) = Hide;
            label(x, y) = 0;
        }
    nBomb = total;
    for (int i = 0; i < nBomb; i++) {
        int x, y;
        do {
            x = rand() % nx;
            y = rand() % ny;
        } while (label(x, y) != Empty);
        label(x, y) = Bomb;
    }
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (label(x, y) == Empty)
                label(x, y) = countNbrBombs(x, y);
}

static bool getPos(int& x, int& y) {
    printf("\n깃발(P)후(세로:1-%d)(가로:1-%d)\n      입력 --> ", ny, nx);
    bool isBomb = false;

    initscr();
    cbreak();
    noecho();

    int ch = getch();
    if (ch == 'P' || ch == 'p') {
        isBomb = true;
        y = getch() - '1'; // 세로 번호 (1부터 시작, 0으로 조정)
    } else {
        y = ch - '1'; // 세로 번호
    }
    x = getch() - '1'; // 가로 번호 (1부터 시작, 0으로 조정)

    endwin();
    return isBomb;
}

static int checkDone() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open) count++;
            else if (isBomb(x, y)) return -1;
        }
    return (count == nBomb) ? 1 : 0;
}

void playMineSweeper(int total) {
    int x, y, status;
    init(total);
    do {
        print();
        bool isBomb = getPos(x, y);
        if (isBomb) mark(x, y);
        else dig(x, y);
        status = checkDone();
    } while (status == 0);
    print();
    if (status < 0)
        printf("\n결과: 폭탄 터짐!!!\n\n");
    else
        printf("\n결과: 탐색 성공!!!\n\n");
}