#include <iostream>

constexpr int squares[] {0,1,4,9};

int main() {
    int userInt{};

prompt_loop:
    while(true) {
        std::cout << "Enter a single digit number or -1 to quit: ";
        std::cin >> userInt;
        if(userInt == -1) {
            break;
        }
        for(int sq : squares) {
            if(userInt == sq) {
                std::cout << "Your number is square.\n";
                goto prompt_loop;
            }
        }
        std::cout << "Your number is not square.\n";
    }
    std::cout << "Bye\n";
    return 0;
}