#include <iostream>

int factorial(int num) {
    if(num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}

int digitSum(int num) {
    if(num < 10) {
        return num;
    }
    return digitSum(num / 10) + num % 10;
}

void printBinary(unsigned int num) {
    if(num < 2) {
        std::cout << num;
        return;
    }
    printBinary(num / 2);
    std::cout << num % 2;
}

int main () {
    int userIn;
    std::cout << "Enter a number to take the factorial of: ";
    std::cin >> userIn;
    // std::cout << factorial(userIn) << '\n';
    // std::cout << digitSum(userIn) << '\n';
    printBinary(userIn);
    std::cout << '\n';
}