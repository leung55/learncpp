#include "random.h"
#include <iostream>
#include <vector>
#include <cstdlib>
int main () {

    int userInt;
    std::cout << "Enter a number: ";
    std::cin >> userInt;
    
    int numberOfNums;
    std::cout << "How many numbers do you want?: ";
    std::cin >> numberOfNums;
    const int multiplier{Random::get(2,4)};

    auto printNums {
        [=]() mutable {
            std::vector<int> nums(numberOfNums);
            for(std::size_t i{0}; i < numberOfNums; ++i) {
                nums[i] = userInt*userInt*multiplier;
                userInt++;
            }
            std::cout << "I generated " << numberOfNums << " square numbers. Do you know what each number is after multiplying it by " << multiplier << "?\n";
            while(numberOfNums > 0) {
                int guess;
                std::cout << ">";
                std::cin >> guess;
                bool numFound{false};
                int minDiff{abs(nums[0] - guess)};
                std::size_t minDiffIdx{0};
                for(std::size_t i{0}; i < numberOfNums; ++i) {
                    if(nums[i] == guess) {
                        nums.erase(nums.begin()+i);
                        numFound = true;
                        break;
                    }
                    if(abs(nums[i] - guess) < minDiff) {
                        minDiff = abs(nums[i] - guess);
                        minDiffIdx = i;
                    }
                }
                if(numFound) {
                    std::cout << "Nice! " << --numberOfNums << " number(s) left!. \n";
                }
                else {
                    std::cout << guess << " is wrong! Try " << nums[minDiffIdx] << " next time.\n";
                    break;
                }
                if(numberOfNums == 0) {
                    std::cout << "You won!\n" ;
                }
            }
        }
    };
    printNums();
    return 0;
}