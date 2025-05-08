#include <iostream>
#include <cstring>

class Sample {
private:
    char* name;
    static int count; // 정적 변수 count

public:
    // 기본 생성자
    Sample() : name(nullptr) {
        count++; // 객체 생성 시 count 증가
    }

    // 매개변수 있는 생성자
    Sample(const char* name) {
        this->name = new char[strlen(name) + 1]; // 동적 할당
        strcpy(this->name, name); // 문자열 복사
        count++; // 객체 생성 시 count 증가
    }

    // 복사 생성자
    Sample(const Sample& other) {
        if (other.name) {
            this->name = new char[strlen(other.name) + 1]; // 깊은 복사
            strcpy(this->name, other.name);
        } else {
            this->name = nullptr; // other.name이 nullptr인 경우
        }
        count++; // 객체 생성 시 count 증가
    }

    // 소멸자
    ~Sample() {
        delete[] this->name; // 동적 메모리 해제
        count--; // 객체 소멸 시 count 감소
    }

    // count 출력 함수
    static void printCount() {
        std::cout << "Current number of Sample objects: " << count << std::endl;
    }
};

// 정적 변수 count 정의 및 초기화
int Sample::count = 0;

int main() {
    Sample a("sample");
    Sample::printCount(); // 출력: Current number of Sample objects: 1

    Sample b(a); // 복사 생성자 호출
    Sample::printCount(); // 출력: Current number of Sample objects: 2

    return 0;
}