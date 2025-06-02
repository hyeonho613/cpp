#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <ctime>

class SampleList 
{
    int list[100];

public:
    SampleList() 
    {
        for (int x = 0; x < 100; x++) 
        {
            list[x] = rand() % 1000; // 0~999 사이의 임의 값
        }
    }

    // 인덱스 연산자 오버로드
    int& operator[](int index) 
    {
        return list[index];
    }

    // 함수 호출 연산자 오버로드 (단일 인덱스)
    int& operator()(int index) 
    {
        return list[index];
    }

    // 함수 호출 연산자 오버로드 (두 수의 곱)
    int& operator()(int a, int b) 
    {
        int index = (a * b) % 100;
        return list[index];
    }

    // list 배열 출력 함수
    void printList() const 
    {
        for (int i = 0; i < 100; i++) 
        {
            std::cout << "list[" << i << "] = " << list[i];
            if (i % 10 == 9) 
            {
                std::cout << std::endl; // 10개마다 줄바꿈
            } 
            else 
            {
                std::cout << "\t"; // 요소 사이 탭
            }
        }
    }
};

int main() {
    // rand() 시드 설정
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    SampleList sample;

    // 초기 list 출력
    std::cout << "=== 초기 list 상태 ===" << std::endl;
    sample.printList();

    // 1. 인덱스 연산자 [] 테스트
    std::cout << "\n=== 인덱스 연산자 테스트 ===" << std::endl;
    std::cout << "sample[14]: " << sample[14] << std::endl;
    sample[14] = 999; // 값 수정
    std::cout << "sample[14] 수정 후: " << sample[14] << std::endl;

    // 2. 함수 호출 연산자 () 테스트 (단일 인덱스)
    std::cout << "\n=== 함수 호출 연산자 테스트 ===" << std::endl;
    std::cout << "sample(38): " << sample(38) << std::endl;
    sample(38) = 888; // 값 수정
    std::cout << "sample(38) 수정 후: " << sample(38) << std::endl;

    // 3. 함수 호출 연산자 () 테스트 (두 수의 곱)
    std::cout << "\n=== 함수 호출 연산자 (두 수의 곱) 테스트 ===" << std::endl;
    int a = 9, b = 8; // 9 * 8 = 72
    std::cout << "sample(9, 8) (인덱스 " << (a * b) % 100 << "): " << sample(a, b) << std::endl;
    sample(a, b) = 777; // 값 수정
    std::cout << "sample(9, 8) 수정 후: " << sample(a, b) << std::endl;

    // 수정 후 list 출력
    std::cout << "\n=== 수정 후 list 상태 ===" << std::endl;
    sample.printList();

    return 0;
}