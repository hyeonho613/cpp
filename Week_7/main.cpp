#include <iostream>
#include "Complex.h"

void printComplex(const Complex& c) {
    std::cout << c.getReal() << " + " << c.getImag() << "i" << std::endl;
}

int main() {
    // 테스트용 복소수 객체 생성
    Complex a(3.0, 4.0);  // 3 + 4i
    Complex b(1.0, 2.0);  // 1 + 2i
    Complex c;            // 결과 저장용

    // 1. 일반 함수 (void, 참조 전달)
    std::cout << "1. 일반 함수 (void, 참조 전달): ";
    add(a, b, c);
    printComplex(c);  // 예상 출력: 4 + 6i

    // 2. 일반 함수 (return, 값 전달)
    std::cout << "2. 일반 함수 (return, 값 전달): ";
    c = add(a, b);
    printComplex(c);  // 예상 출력: 4 + 6i

    // 3. 멤버 함수 (void, 참조 전달)
    std::cout << "3. 멤버 함수 (void, 참조 전달): ";
    c.add(a, b);
    printComplex(c);  // 예상 출력: 4 + 6i

    // 4. 멤버 함수 (return, 참조 전달)
    std::cout << "4. 멤버 함수 (return, 참조 전달): ";
    c = a.add(b);
    printComplex(c);  // 예상 출력: 4 + 6i

    // 5. 연산자 오버로딩
    std::cout << "5. 연산자 오버로딩: ";
    c = a + b;
    printComplex(c);  // 예상 출력: 4 + 6i

    return 0;
}