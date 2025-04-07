#include "MineSweeper.h"

int main() {
    int width, height, total;

    printf(" <Mine Sweeper>\n");
    printf(" 맵의 가로 크기 (최대 %d): ", MAX_WIDTH);
    scanf("%d", &width);
    if (width > MAX_WIDTH) width = MAX_WIDTH;
    if (width < 1) width = 1;

    printf(" 맵의 세로 크기 (최대 %d): ", MAX_HEIGHT);
    scanf("%d", &height);
    if (height > MAX_HEIGHT) height = MAX_HEIGHT;
    if (height < 1) height = 1;

    printf(" 지뢰의 수 입력 (최대 %d): ", width * height);
    scanf("%d", &total);
    if (total > width * height) total = width * height;
    if (total < 0) total = 0;

    nx = width;
    ny = height;

    playMineSweeper(total);
    return 0;
}