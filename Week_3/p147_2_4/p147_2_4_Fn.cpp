#include "p147_2_4.h" // 헤더 파일 포함

int reverse(int num) {
    rev = 0; // rev 초기화 (여러 번 호출 시 값 유지 방지)
    for (; num > 0; num /= 10) 
        rev = rev * 10 + num % 10;
    return rev;
}
