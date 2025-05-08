#include <iostream>
#include <cstring>

class Sample {
    char* name;
    static int count;

public:
    Sample() { count++; }
    Sample(const char* name) { 
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        count++;
    }
    Sample(const Sample& other) { 
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        count++;
    }
    ~Sample() { 
        delete[] name;
        count--; 
    }

    static void printCount() { 
        std::cout << "Number of Sample objects: " << count << std::endl;
    }
};

int Sample::count = 0;

int main() {
    Sample a("sample");
    Sample b(a);
    Sample::printCount();
}