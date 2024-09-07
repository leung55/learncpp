#include "random.h"
#include <iostream>

int getNumGuesses() {
    std::cout << "Enter number of guesses: ";
    int numGuesses{};
    std::cin >> numGuesses;
    return numGuesses;
}

int getMin() {
    std::cout << "Enter min: ";
    int min{};
    std::cin >> min;
    return min;
}

int getMax() {
    std::cout << "Enter max: ";
    int max{};
    std::cin >> max;
    return max;
}

void pickNumber(int min, int max, int correctNum) {
    std::cout << "Try to guess the right number between " << min << " and " << max << ": ";
    int guess{};
    std::cin >> guess;
    if(guess > correctNum) {
        std::cout << "Too high\n";
    }
    else if(guess < correctNum) {
        std::cout << "Too low\n";
    }
    else {
        std::cout << "You won!";
    }
}
int main() {
    char play{'y'};
    do {
    int numGuesses{getNumGuesses()};
    int min {getMin()};
    int max {getMax()};
    int correctNum{Random::get(min,max)};
    int i{};
        for(i = 0; i < numGuesses; i++) {
        std::cout << "Try to guess the right number between " << min << " and " << max << ": ";
        int guess{};
        std::cin >> guess;
        if(guess > correctNum) {
            std::cout << "Too high\n";
        }
        else if(guess < correctNum) {
            std::cout << "Too low\n";
        }
        else {
            std::cout << "You won!\n";
            break;
        }
        }
        if (i >= numGuesses) {
            std::cout << "You lost. The correct number was: " << correctNum << '\n';
        }
        do {
            std::cout << "Do you want to play again? [y/n]: ";
            std::cin >> play;
        } while(play != 'y' and play != 'n');

    } while(play == 'y');
    
    return 0;
}