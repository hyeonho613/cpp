#include <iostream>

class MyTime {
private:
    int hours;
    int minutes;
public:
    MyTime(int h = 0, int m = 0) {
        hours = h + m / 60;  // 분이 60 이상이면 시간으로 변환
        minutes = m % 60;    // 나머지 분
    }
    void display() const {
        std::cout << hours << " hours, " << minutes << " minutes" << std::endl;
    }
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
};

// 방법 1: 반환값을 사용하는 방식
MyTime addTime(MyTime t1, MyTime t2) {
    int totalMinutes = (t1.getHours() * 60 + t1.getMinutes()) + 
                       (t2.getHours() * 60 + t2.getMinutes());
    return MyTime(totalMinutes / 60, totalMinutes % 60);
}

// 방법 2: 참조 매개변수를 사용하는 방식
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    int totalMinutes = (t1.getHours() * 60 + t1.getMinutes()) + 
                       (t2.getHours() * 60 + t2.getMinutes());
    t3 = MyTime(totalMinutes / 60, totalMinutes % 60);
}

// 방법 3: 포인터 매개변수를 사용하는 방식
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    int totalMinutes = (t1.getHours() * 60 + t1.getMinutes()) + 
                       (t2.getHours() * 60 + t2.getMinutes());
    *pt = MyTime(totalMinutes / 60, totalMinutes % 60);
}

int main() {
    MyTime time1(2, 45);  // 2시간 45분
    MyTime time2(1, 30);  // 1시간 30분
    MyTime result;

    // 방법 1: 반환값 사용
    result = addTime(time1, time2);
    std::cout << "방법 1 결과: ";
    result.display();  // 출력: 4 hours, 15 minutes

    // 방법 2: 참조 사용
    addTime(time1, time2, result);
    std::cout << "방법 2 결과: ";
    result.display();  // 출력: 4 hours, 15 minutes

    // 방법 3: 포인터 사용
    addTime(time1, time2, &result);
    std::cout << "방법 3 결과: ";
    result.display();  // 출력: 4 hours, 15 minutes

    return 0;
}