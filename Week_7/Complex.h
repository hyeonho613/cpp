#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
private:
    double real;      // 실수부
    double imag;      // 허수부

public:
    // 생성자
    Complex(double r = 0.0, double i = 0.0);
    
    // 소멸자
    ~Complex();
    
    // 복사 생성자
    Complex(const Complex& other);
    
    // getter
    double getReal() const;
    double getImag() const;
    
    // 1. 일반 함수 (void, 참조 전달)
    friend void add(Complex& a, Complex& b, Complex& result);
    
    // 2. 일반 함수 (return, 값 전달)
    friend Complex add(Complex a, Complex b);
    
    // 3. 멤버 함수 (void, 참조 전달)
    void add(const Complex& a, const Complex& b);
    
    // 4. 멤버 함수 (return, 참조 전달)
    Complex add(const Complex& other) const;
    
    // 5. 연산자 오버로딩
    Complex operator+(const Complex& other) const;
};

#endif