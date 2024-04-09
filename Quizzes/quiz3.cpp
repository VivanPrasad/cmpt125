#include <iostream>
#include <iomanip>

int main() {
    double col1Value = 1.2345e-001;
    int col2Value = 42;
    float col3Value = 123.45;
    
    // Print the table line
    std::cout << std::setprecision(2) << std::setw(6) << 3.134 << ", " << std::setw(6) << 10.50;

    return 0;
}