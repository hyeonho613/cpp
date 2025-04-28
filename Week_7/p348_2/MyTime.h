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
    MyTime() : hours(0), minutes(0), seconds(0), milliseconds(0) {}
    MyTime(int h, int m, int s, int ms) : hours(h), minutes(m), seconds(s), milliseconds(ms) {}
    MyTime(double duration);

    void convert(double duration);
    void print();
    MyTime add(MyTime t);
    void reset();
    void read();
};

#endif