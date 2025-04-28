#include "MyTime.h"
#include <iomanip>

MyTime::MyTime(double duration) {
    convert(duration);
}

void MyTime::convert(double duration) {
    int totalMs = static_cast<int>(duration * 1000);
    milliseconds = totalMs % 1000;
    totalMs /= 1000;
    seconds = totalMs % 60;
    totalMs /= 60;
    minutes = totalMs % 60;
    hours = totalMs / 60;
}

void MyTime::print() {
    std::cout << std::setfill('0') << std::setw(2) << hours << ":"
              << std::setfill('0') << std::setw(2) << minutes << ":"
              << std::setfill('0') << std::setw(2) << seconds << ":"
              << std::setfill('0') << std::setw(3) << milliseconds;
}

MyTime MyTime::add(MyTime t) {
    MyTime result;
    int totalMs = (milliseconds + t.milliseconds) + 
                 (seconds + t.seconds) * 1000 + 
                 (minutes + t.minutes) * 60000 + 
                 (hours + t.hours) * 3600000;
    
    result.milliseconds = totalMs % 1000;
    totalMs /= 1000;
    result.seconds = totalMs % 60;
    totalMs /= 60;
    result.minutes = totalMs % 60;
    result.hours = totalMs / 60;
    return result;
}

void MyTime::reset() {
    hours = minutes = seconds = milliseconds = 0;
}

void MyTime::read() {
    std::cout << "시를 입력하세요: ";
    std::cin >> hours;
    std::cout << "분을 입력하세요: ";
    std::cin >> minutes;
    std::cout << "초를 입력하세요: ";
    std::cin >> seconds;
    std::cout << "밀리초를 입력하세요: ";
    std::cin >> milliseconds;
}