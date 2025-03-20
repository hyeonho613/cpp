#include <iostream>

int num, rev = 0; // 전역 변수 선언

int reverse(int num); // 함수 원형 선언

int main() {
    std::cout << "정수를 입력하세요: ";
    std::cin >> num;

    std::cout << "역순 변환된 숫자: " << reverse(num) << std::endl;
    return 0;
}
