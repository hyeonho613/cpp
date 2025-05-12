#include <iostream>
#include <string.h>

class Sample {
    char *name;
    static int count;
public:
    Sample() { 
        name = nullptr;
        count++; 
    }
    Sample(const char * name) { 
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        count++; 
    }
    Sample(const Sample& other) { 
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        count++;
    }
    ~Sample() { 
        delete[] name;
    }
    static void printCount() {
        std::cout << "Sample 객체의 개수: " << count << std::endl;
    }
};
int Sample::count = 0;

int main() {
    std::cout << "객체 추가 없음 -> ";
    Sample::printCount();

    Sample a("sample");
    std::cout << "객체 a 추가 -> ";
    Sample::printCount();

    Sample b(a);
    std::cout << "객체 b 추가 -> ";
    Sample::printCount();
    return 0;
}