#include <iterator> // for std::size
#include <iostream>

void printArr(const int arr[], int length) {
    for(int i{0}; i < length; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int length{std::size(array)};
    printArr(array, length);
    for(int i{length-1}; i > 0; --i) {
        bool swapCheck{false};
        for(int j{0}; j < i; ++j) {
            if(array[j] > array[j+1]) {
                std::swap(array[j], array[j+1]);
                swapCheck = true;
            }
        }
        if(!swapCheck) {
            std::cout << "early termination on " << length - i << '\n';
            break;
        }
    }
    printArr(array, length);
    std::cout << '\n';
}