#include <iostream>

// 방법 1: 반환값을 사용하는 방식 (구조체로 결과 반환)
struct Time {
    int hours;
    int minutes;
};

Time addTime(Time t1, Time t2) {
    int totalMinutes = (t1.hours * 60 + t1.minutes) + (t2.hours * 60 + t2.minutes);
    Time result;
    result.hours = totalMinutes / 60;
    result.minutes = totalMinutes % 60;
    return result;
}

// 방법 2: 참조 매개변수를 사용하는 방식
void addTime(Time t1, Time t2, Time& t3) {
    int totalMinutes = (t1.hours * 60 + t1.minutes) + (t2.hours * 60 + t2.minutes);
    t3.hours = totalMinutes / 60;
    t3.minutes = totalMinutes % 60;
}

// 방법 3: 포인터 매개변수를 사용하는 방식
void addTime(Time t1, Time t2, Time* pt) {
    int totalMinutes = (t1.hours * 60 + t1.minutes) + (t2.hours * 60 + t2.minutes);
    pt->hours = totalMinutes / 60;
    pt->minutes = totalMinutes % 60;
}

int main() {
    Time time1 = {2, 45};  // 2시간 45분
    Time time2 = {1, 30};  // 1시간 30분
    Time result;

    // 방법 1: 반환값 사용
    result = addTime(time1, time2);
    std::cout << "방법 1 결과: " << result.hours << " hours, " << result.minutes << " minutes" << std::endl;

    // 방법 2: 참조 사용
    Time result2;
    addTime(time1, time2, result2);
    std::cout << "방법 2 결과: " << result2.hours << " hours, " << result2.minutes << " minutes" << std::endl;

    // 방법 3: 포인터 사용
    Time result3;
    addTime(time1, time2, &result3);
    std::cout << "방법 3 결과: " << result3.hours << " hours, " << result3.minutes << " minutes" << std::endl;

    return 0;
}