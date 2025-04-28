#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

public:
    // 기존 기본 생성자 (멤버 초기화 리스트 사용)
    MyTime() : hours(0), minutes(0), seconds(0), milliseconds(0) {}
    
    // 새로운 생성자 - 멤버 초기화 리스트 사용
    MyTime(int h, int m, int s, int ms) : hours(h), minutes(m), seconds(s), milliseconds(ms) {}
    
    // 새로운 생성자 - 멤버 초기화 리스트 미사용
    MyTime(int h, int m, int s, int ms) {
        hours = h;
        minutes = m;
        seconds = s;
        milliseconds = ms;
    }

    void convert(double duration);
    void print();
    MyTime add(MyTime t);
    void reset();
    void read();
};

#endif
