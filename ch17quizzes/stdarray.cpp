#include <array>
#include <iostream>

template <typename T, auto N>
void printArray(const std::array<T,N> arr) {
    std::cout << "Array: ";
    for(const auto& el : arr) {
        std::cout << el << " ";
    }
    std::cout << "has length " << N << '\n';
}

int main () {
    constexpr std::array greeting {'h', 'e', 'l', 'l', 'o'};
    std::cout << "The length is " << greeting.size() << '\n';
    std::cout << greeting[1] << greeting.at(1) << std::get<1>(greeting) << '\n';

    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);
}