#include "MineSweeper.h"
#define DIM 9

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };
static int MineMapMask[DIM][DIM];    // Hide, Open, Flag
static int MineMapLabel[DIM][DIM];   // 0~8, 9(Bomb)
static int nx = DIM, ny = DIM;
static int nBomb = DIM;

// 인라인 함수들
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

static void dig(int x, int y) {      // (x,y)를 파는(여는) 함수
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

static void mark(int x, int y) {     // (x,y)를 깃발로 표시 함수
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;
}

static int getBombCount() {          // 깃발 수 계산 함수
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag) count++;
    return count;
}

static void print() {                // 게임 상태 화면 출력 함수
    system("clear");                // cls 대신 clear로 리눅스에서 화면 지우기
    printf("   깃발:%2d   전체:%2d\n", getBombCount(), nBomb);
    printf("    1 2 3 4 5 6 7 8 9\n");
    for (int y = 0; y < ny; y++) {
        printf("%2c ", 'A' + y);
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) == Hide) printf("⬜");      // 숨겨진 칸
            else if (mask(x, y) == Flag) printf("🚩"); // 깃발 표시
            else {                                     // 열린 칸
                if (isBomb(x, y)) printf("💣");        // 9: 폭탄!!
                else if (isEmpty(x, y)) printf("  ");  // 0: 빈칸 표시
                else printf("%2d", label(x, y));       // 1~8: 숫자 표시
            }
        }
        printf("\n");
    }
}

static int countNbrBombs(int x, int y) { // 주변 폭탄 수 계산 함수
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy) && label(xx, yy) == Bomb)
                count++;
    return count;
}

static void init(int total = 9) {
    srand((unsigned int)time(NULL));
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {      // 맵과 마스크 초기화
            mask(x, y) = Hide;
            label(x, y) = 0;
        }
    nBomb = total;
    for (int i = 0; i < nBomb; i++) {   // 폭탄 배치(total개)
        int x, y;
        do {
            x = rand() % nx;
            y = rand() % ny;
        } while (label(x, y) != Empty);
        label(x, y) = Bomb;
    }
    for (int y = 0; y < ny; y++)        // 주변 폭탄 수 계산
        for (int x = 0; x < nx; x++)
            if (label(x, y) == Empty)
                label(x, y) = countNbrBombs(x, y);
}

static bool getPos(int& x, int& y) {    // 키보드 좌표 입력 함수
    printf("\n깃발(P)후(A-I)와(1-9)\n      입력 --> ");
    bool isBomb = false;
    
    initscr();                          // ncurses 초기화
    cbreak();                           // 입력 즉시 반응
    noecho();                           // 입력값 화면에 안 보이게
    
    int ch = getch();                   // 첫 번째 입력 (P 또는 A-I)
    if (ch == 'P' || ch == 'p') {
        isBomb = true;
        y = toupper(getch()) - 'A';     // 두 번째 입력 (A-I)
    } else {
        y = toupper(ch) - 'A';          // 첫 입력이 P가 아니면 바로 A-I로
    }
    x = getch() - '1';                  // 세 번째 입력 (1-9)
    
    endwin();                           // ncurses 종료
    return isBomb;
}

static int checkDone() {                // 게임 종료 조건 확인 함수
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open) count++;
            else if (isBomb(x, y)) return -1;
        }
    return (count == nBomb) ? 1 : 0;
}

void playMineSweeper(int total) {       // 지뢰 찾기 게임 함수
    int x, y, status;
    init(total);                        // 맵 초기화
    do {
        print();
        bool isBomb = getPos(x, y);     // 위치 입력
        if (isBomb) mark(x, y);         // 깃발이면 mark 호출
        else dig(x, y);                 // 아니면 dig 호출
        status = checkDone();           // 게임 상태 확인
    } while (status == 0);             // 종료 조건까지 반복
    print();
    if (status < 0)                    // 실패/성공 출력
        printf("\n결과: 폭탄 터짐!!!\n\n");
    else printf("\n결과: 탐색 성공!!!\n\n");
}