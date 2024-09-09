#include <iostream>
#include <string>
#include <algorithm>
int main (int argc, char* argv[]) {

    // std::size_t num_names{};
    // std::cout << "how many names do you want to enter?: ";
    // std::cin >> num_names;

    // auto* names_ptr{new std::string[num_names]};
    // int idx{1};
    // for(std::size_t i{0}; i < num_names ; ++i) {
    //     std::cout << "Enter name #" << i + 1 << ": ";
    //     std::cin >> *(names_ptr + i);
    // }
    // std::sort(names_ptr, names_ptr + num_names);
    // idx = 1;
    // for(std::size_t i{0}; i < num_names ; ++i) {
    //     std::cout << "Name #" << i + 1 << ": " << *(names_ptr + i) << '\n';
    // }

    // delete[] names_ptr;

    int x { 2 }; // non-constant
    // int* arr[5] { new int[2][5] }; // rightmost dimension must be constexpr
    int (*arr)[5] {new int[x][5]}; // rightmost dimension must be constexpr
    for(int i{0}; i < x; ++i) {
        for(int j{0}; j < 5; ++j) {
            *(*(arr + i) + j) = i*5 + j + 1;
        }
    }
    for(int i{0}; i < x; ++i) {
        for(int j{0}; j < 5; ++j) {
            std::cout << *(*(arr + i) + j) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    return 0;
}