#include "MineSweeper.h"

int main() {
    int total;
    printf(" <Mine Sweeper>\n");
    printf(" 지뢰의 수 입력(기본 9) : ");
    scanf("%d", &total);
    playMineSweeper(total);
    return 0;
}