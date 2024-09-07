#include <vector>
#include <iostream>
#include <cassert>

int main() {
    const std::vector divisors{3,5,7,11,13,17,19};
    const std::vector<std::string_view> words{"fizz", "buzz", "pop", "bang", "jazz", "pow", "boom"};
    assert(divisors.size() == words.size() && "Arrays must be same size");

    std::size_t length{divisors.size()};

    bool isDivisible{false};

    for(int i{1}; i <= 150; ++i) {
        for(std::size_t j{0}; j < length && i >= divisors[j]; ++j){
            if(i % divisors[j] == 0) {
                std::cout << words[j];
                isDivisible = true;
            }
        }
        if(!isDivisible) {
            std::cout << i << '\n';
        }
        else {
            std::cout << '\n';
            isDivisible = false;
        }
    }
    return 0;
}