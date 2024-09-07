#include "input_handling.h"
#include <iostream>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr) {
    for(std::size_t i{0}; i < arr.size(); ++i) {
            std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

template <typename T>
T getVal(T lo, T hi) {
    while(true) {
        T val{};
        std::cout << "Enter a value 1 thru 9: ";
        std::cin >> val;
        if(InputHandling::clearFailedExtraction()) {
            std::cout << "Invalid input, try again.\n";
            continue;
        }
        if(val >= hi || val <= lo) {
            std::cout << "Value should be within bounds.\n";
            continue;
        }
        InputHandling::ignoreLine();
        return val;
    }
}

template <typename T>
std::size_t getIdx(const std::vector<T>& v, T val) {
    for(std::size_t i{0}; i < v.size(); ++i) {
        if(v[i] == val)
            return i;
    }
    return -1;
}

template <typename T>
T findMax(const std::vector<T>& v) {
    T max{};
    if(v.size() > 0)
        max = v[0];
    for(std::size_t i{1}; i < v.size(); ++i) {
        if(v[i] > max)
            max = v[i];
    }
    return max;
}

int main()
{
    // std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
    // Add your code here
    double val{getVal(0.0,10.0)};
    printArray(arr);
    std::size_t idx{getIdx(arr, val)};
    if(idx == -1) {
        std::cout << val << " not found in array.\n";
    }
    else {
        std::cout << val << " at index " << idx << '\n';
    }
    std::vector data1 { 84, 92, 76, 81, 56 };
    std::cout << findMax(data1) << '\n';

    std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
    std::cout << findMax(data2) << '\n';

    std::vector<int> data3 { };
    std::cout << findMax(data3) << '\n';

    return 0;
}