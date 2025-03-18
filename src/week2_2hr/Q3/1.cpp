#include <iostream>
#include <iomanip>

double Pi(int terms) 
{
    double pi = 0.0;
    for (int i = 0; i < terms; i++) 
    {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
        pi += term;
    }
    return pi * 4;
}

int main() 
{
    int terms = 1000000;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Leibniz Method Approximation of Pi: " << Pi(terms) << std::endl;
    return 0;
}
