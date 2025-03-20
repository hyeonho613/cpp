#include <iostream>
#include "p147_2_4.h" // 헤더 파일 포함

int num, rev = 0; // 전역 변수 정의 (헤더 파일에 extern으로 선언됨)

int main() {
    std::cout << "정수를 입력하세요: ";
    std::cin >> num;

    std::cout << "역순 변환된 숫자: " << reverse(num) << std::endl;
    return 0;
}
