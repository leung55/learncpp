#include "random.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <functional>
#include <algorithm>

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
                std::cout << "> ";
                std::cin >> guess;
                auto numMatch{std::find(nums.begin(), nums.end(),guess)};
                if(numMatch == nums.end()) {
                    for(int& num : nums) {
                        num -= guess;
                    }
                    auto smallerAbs{
                        [](int& a, int& b) {
                            return abs(a) < abs(b);
                        }
                    };
                    const auto min{std::min_element(nums.begin(),nums.end(),smallerAbs)};
                    std::cout << guess << " is wrong! Try " << (*min) + guess << " next time.\n";
                    break;
                }
                else {
                    std::cout << "Nice! " << --numberOfNums << " number(s) left!. \n";
                    nums.erase(numMatch);
                }
            }
            if(numberOfNums == 0) {
                std::cout << "You won!\n" ;
            }
        }
    };
    printNums();
    return 0;
}