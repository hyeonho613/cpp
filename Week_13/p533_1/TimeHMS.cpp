#include <iostream>

class TimeHMS {
    int hour, min, sec; // 시, 분, 초 저장

    // 시간 정규화: 분과 초를 0~59로 맞춤
    void normalize() {
        // 초가 60 이상이면 분으로 변환
        min += sec / 60;
        sec = sec % 60;
        if (sec < 0) {
            sec += 60;
            min--;
        }
        // 분이 60 이상이면 시로 변환
        hour += min / 60;
        min = min % 60;
        if (min < 0) {
            min += 60;
            hour--;
        }
        // 음수 시간은 0으로
        if (hour < 0) hour = 0;
    }

public:
    // 생성자: 시, 분, 초 설정
    TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) {
        normalize();
    }

    // 1. 두 시간 더하기
    TimeHMS operator+(const TimeHMS& other) {
        TimeHMS result(hour + other.hour, min + other.min, sec + other.sec);
        return result;
    }

    // 2. 두 시간 빼기
    TimeHMS operator-(const TimeHMS& other) {
        TimeHMS result(hour - other.hour, min - other.min, sec - other.sec);
        return result;
    }

    // 3. 두 시간 같은지 확인
    bool operator==(const TimeHMS& other) {
        return hour == other.hour && min == other.min && sec == other.sec;
    }

    // 3. 두 시간 다른지 확인
    bool operator!=(const TimeHMS& other) {
        return !(*this == other);
    }

    // 4. 1시간 늘리기 (전위++)
    TimeHMS& operator++() {
        hour++;
        normalize();
        return *this;
    }

    // 4. 1시간 줄이기 (전위--)
    TimeHMS& operator--() {
        hour--;
        normalize();
        return *this;
    }

    // 5. 1초 늘리기 (후위++)
    TimeHMS operator++(int) {
        TimeHMS temp = *this;
        sec++;
        normalize();
        return temp;
    }

    // 5. 1초 줄이기 (후위--)
    TimeHMS operator--(int) {
        TimeHMS temp = *this;
        sec--;
        normalize();
        return temp;
    }

    // 6. 시, 분, 초 접근 (0=시, 1=분, 2=초)
    int operator[](int index) {
        if (index == 0) return hour;
        if (index == 1) return min;
        if (index == 2) return sec;
        return 0; // 잘못된 인덱스는 0 반환
    }

    // 7. 초 단위로 변환
    operator int() {
        return hour * 3600 + min * 60 + sec;
    }

    // 8. 시간 단위로 변환
    operator double() {
        return hour + min / 60.0 + sec / 3600.0;
    }

    // 9. 정수와 시간 곱하기
    friend TimeHMS operator*(int n, TimeHMS t) {
        TimeHMS result(t.hour * n, t.min * n, t.sec * n);
        return result;
    }

    // 10. 시간 입력 (hh:mm:ss)
    friend std::istream& operator>>(std::istream& is, TimeHMS& t) {
        char colon;
        is >> t.hour >> colon >> t.min >> colon >> t.sec;
        t.normalize();
        return is;
    }

    // 10. 시간 출력 (hh:mm:ss)
    friend std::ostream& operator<<(std::ostream& os, TimeHMS t) {
        // 두 자리로 출력
        if (t.hour < 10) os << "0";
        os << t.hour << ":";
        if (t.min < 10) os << "0";
        os << t.min << ":";
        if (t.sec < 10) os << "0";
        os << t.sec;
        return os;
    }
};

// 모든 연산자 테스트
int main() {
    TimeHMS t1(1, 20, 30), t2(4, 35, 46), t3;

    // 문제 1: 두 시간 더하기 테스트
    t3 = t1 + t2;
    std::cout << "t1 + t2 = " << t3 << std::endl; // 05:56:16

    // 문제 2: 두 시간 빼기 테스트
    t3 = t2 - t1;
    std::cout << "t2 - t1 = " << t3 << std::endl; // 03:15:16

    // 문제 3: 시간 같음/다름 테스트
    std::cout << "t1 == t2: " << (t1 == t2 ? "참" : "거짓") << std::endl; // 거짓
    std::cout << "t1 != t2: " << (t1 != t2 ? "참" : "거짓") << std::endl; // 참

    // 문제 4: 1시간 늘리고 줄이기 테스트
    ++t1;
    std::cout << "++t1 = " << t1 << std::endl; // 02:20:30
    --t1;
    std::cout << "--t1 = " << t1 << std::endl; // 01:20:30

    // 문제 5: 1초 늘리고 줄이기 테스트
    t1++;
    std::cout << "t1++ = " << t1 << std::endl; // 01:20:31
    t1--;
    std::cout << "t1-- = " << t1 << std::endl; // 01:20:30

    // 문제 6: 시, 분, 초 접근 테스트
    std::cout << "t1[0] = " << t1[0] << ", t1[1] = " << t1[1] << ", t1[2] = " << t1[2] << std::endl; // 1, 20, 30

    // 문제 7: 초 단위 변환 테스트
    std::cout << "(int)t1 = " << (int)t1 << " 초" << std::endl; // 4830 초

    // 문제 8: 시간 단위 변환 테스트
    std::cout << "(double)t1 = " << (double)t1 << " 시간" << std::endl; // 약 1.34167

    // 문제 9: 시간 2배 만들기 테스트
    t3 = 2 * t1;
    std::cout << "2 * t1 = " << t3 << std::endl; // 02:41:00

    // 문제 10: 시간 입력 및 출력 테스트
    std::cout << "시간 입력 (hh:mm:ss): ";
    std::cin >> t3;
    std::cout << "입력 시간: " << t3 << std::endl;

    return 0;
}