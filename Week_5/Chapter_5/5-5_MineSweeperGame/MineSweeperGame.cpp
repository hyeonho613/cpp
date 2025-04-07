#include "MineSweeper.h"

int main() // void main 대신 int main 사용 (리눅스 표준)
{
    int total;
    printf(" <Mine Sweeper>\n");
    printf(" 지뢰의 수 입력(기본 9) : ");
    scanf("%d", &total);
    playMineSweeper(total);
    return 0; // 리턴값 추가
}