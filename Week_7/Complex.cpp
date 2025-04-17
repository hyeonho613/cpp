#include "Complex.h"

// 생성자
Complex::Complex(double r, double i) : real(r), imag(i) {}

// 소멸자
Complex::~Complex() {}

// 복사 생성자
Complex::Complex(const Complex& other) : real(other.real), imag(other.imag) {}

// getter
double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }

// 1. 일반 함수 (void, 참조 전달)
void add(Complex& a, Complex& b, Complex& result) {
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
}

// 2. 일반 함수 (return, 값 전달)
Complex add(Complex a, Complex b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

// 3. 멤버 함수 (void, 참조 전달)
void Complex::add(const Complex& a, const Complex& b) {
    real = a.real + b.real;
    imag = a.imag + b.imag;
}

// 4. 멤버 함수 (return, 참조 전달)
Complex Complex::add(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

// 5. 연산자 오버로딩
Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}