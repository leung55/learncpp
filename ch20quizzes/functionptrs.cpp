#include "input_handling.h"
#include <iostream>
#include <functional>

using CalcFcn = std::function<int(int,int)>;

int add(int a, int b) {
    return a + b;
}
int subtract(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    return a / b;
}
CalcFcn calc(char op) {
    switch(op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide;
    }
    return nullptr;
}

int main() {
    int a,b;
    char op;
    std::cout << "Enter two integers and a math operation (+, -, *, /) separated by spaces: ";
    while(true) {
        std::cin >> a >> b >> op;
        if(InputHandling::clearFailedExtraction() || op != '+' && op != '-' && op != '*' && op != '/') {
            std::cout << "Invalid input. Try again: ";
            continue;
        }
        InputHandling::ignoreLine();
        break;
    }
    std::cout << a << b << op << '\n';
    CalcFcn calcfcn (calc(op));
    std::cout << calcfcn(a,b) << '\n';
    return 0;
}