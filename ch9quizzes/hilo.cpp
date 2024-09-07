#include "input_handling.h"
#include "random.h"
#include <iostream>
#include <limits> // for std::numeric_limits
#include <string>
#include <cassert>

int getNum(std::string_view int_description) {
    while (true) {
        std::cout << "Enter " << int_description << ": ";
        int userIn{};
        std::cin >> userIn;
        if(InputHandling::clearFailedExtraction()) {
            std::cout << "Invalid input, try again.\n";
            continue;
        }
        InputHandling::ignoreLine();
        return userIn;
    }
}

//returns whether or not picked number was correct
bool pickNumber(int min, int max, int correctNum) {
    int guess{};
    while(true) {
        std::cout << "Try to guess the right number between " << min << " and " << max << ": ";
        std::cin >> guess;
        if(InputHandling::clearFailedExtraction()) {
            std::cout << "Invalid input, try again.\n";
            continue;
        }
        if(guess > max || guess < min) {
            std::cout << "Guess should be within bounds.\n";
            continue;
        }
        InputHandling::ignoreLine();
        break;
    }
    if(guess > correctNum) {
        std::cout << "Too high\n";
    }
    else if(guess < correctNum) {
        std::cout << "Too low\n";
    }
    else {
        std::cout << "You won!\n";
        return true;
    }
    return false;
}
void guessGame() {
    int numGuesses{getNum("num of guesses")};
    assert(numGuesses > 0 && "Number of guesses should be greater than 0");
    int min {getNum("min")};
    int max {getNum("max")};
    assert(max > min && "Max needs to be greater than min");
    int correctNum{Random::get(min,max)};
    for(int i{0}; i < numGuesses; i++) {
        if(pickNumber(min, max, correctNum)) {
            return;
        }
    }
    std::cout << "You lost. The correct number was: " << correctNum << '\n';
}

int main() {
    char play{'y'};
    do {
        guessGame();
        do {
            std::cout << "Do you want to play again? [y/n]: ";
            std::cin >> play;
            if(InputHandling::clearFailedExtraction()){
                std::cout << "Invalid input, try again.\n";
                continue;
            }
            InputHandling::ignoreLine();
        } while(play != 'y' && play != 'n');
    } while(play == 'y');
    
    return 0;
}