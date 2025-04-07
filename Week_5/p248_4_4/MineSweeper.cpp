#include "MineSweeper.h"

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };
static int MineMapMask[DIM][DIM];    // Hide, Open, Flag
static int MineMapLabel[DIM][DIM];   // 0~8, 9(Bomb)
static int nx = DIM, ny = DIM;       // 고정 크기
static int nBomb;

// 인라인 함수들
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

static void dig(int x, int y) {
    if (isValid(x, y) && mask(x, y) != Open) {
        mask(x, y) = Open;
        if (label(x, y) == 0) {
            dig(x - 1, y - 1);
            dig(x - 1, y);
            dig(x - 1, y + 1);
            dig(x, y - 1);
            dig(x, y + 1);
            dig(x + 1, y - 1);
            dig(x + 1, y);
            dig(x + 1, y + 1);
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
    printf("    1 2 3 4 5 6 7 8 9\n"); // 원본 고정 출력
    for (int y = 0; y < ny; y++) {
        printf("%2c ", 'A' + y);
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) == Hide) printf("⬜");      // 숨겨진 칸
            else if (mask(x, y) == Flag) printf("🚩"); // 깃발 표시
            else {
                if (isBomb(x, y)) printf("💣");        // 폭탄
                else if (isEmpty(x, y)) printf("  ");  // 빈칸
                else printf("%2d", label(x, y));       // 숫자
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
    printf("\n입력(열 행 또는 P 열 행, 예: 2 1, P 2 1) --> ");
    char input[10];
    bool isBomb = false;

    fgets(input, sizeof(input), stdin); // 문자열 입력

    // 입력 파싱
    int col, row;
    if (input[0] == 'P' || input[0] == 'p') {
        isBomb = true;
        sscanf(input + 1, "%d %d", &col, &row); // P 다음 열, 행 읽기
    } else {
        sscanf(input, "%d %d", &col, &row); // 열, 행 읽기
    }

    // 열(가로)=x, 행(세로)=y로 매핑 (1부터 시작하니까 0 기반으로 조정)
    x = col - 1; // 열 (1-9)
    y = row - 1; // 행 (1-9, A-I에 맞게)

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