// main.cpp
#include <iostream>
#include "p147_2_5.h"

int reverse(int num) {
    int rev = 0;
    for (; num > 0; num /= 10) 
        rev = rev * 10 + num % 10;
    return rev;
}

int main() {
    int num;
    std::cout << "정수를 입력하세요: ";
    std::cin >> num;

    std::cout << "역순 변환된 숫자: " << reverse(num) << std::endl;
    return 0;
}
