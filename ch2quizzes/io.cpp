#include "io.h"
#include <iostream>

int readNumber() {
    int userNum{};
    std::cout << "Enter a number: ";
    std::cin >> userNum;
    return userNum;
}

void writeAnswer(int sum) {
    std::cout << sum << '\n';
}