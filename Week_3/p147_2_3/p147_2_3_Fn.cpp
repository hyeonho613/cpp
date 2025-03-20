extern int rev; // main.cpp에서 선언된 전역 변수 rev를 사용

int reverse(int num) {
    rev = 0; // rev 초기화 (안 하면 여러 번 호출 시 값이 누적됨)
    for (; num > 0; num /= 10) 
        rev = rev * 10 + num % 10;
    return rev;
}
