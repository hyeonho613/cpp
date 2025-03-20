#include <iostream>

int num, rev = 0; // 변수 선언

int reverse(int);

int main() {
    std::cout << "정수를 입력하세요: ";
    std::cin >> num;

    std::cout << "역순 변환된 숫자: " << reverse(num) << std::endl;
    return 0;
}

int reverse(int num) {
    for (; num > 0; num /= 10) 
        rev = rev * 10 + num % 10;
    return rev;
}
