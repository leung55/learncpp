#include <utility>
#include <vector>
#include <iostream>

template <typename T>
std::pair<T,T> vecToPair(const std::vector<T>& vec) {
    std::size_t length = vec.size();
    if(length <= 0)
        return {-1,-1};
    int min_idx{0}, max_idx{0};
    for(std::size_t i{1}; i < length; ++i) {
        if(vec[i] < vec[min_idx]){
            min_idx = i;
        }
        else if(vec[i] > vec[max_idx]) {
            max_idx = i;
        }
    }

    return {min_idx, max_idx};
}

template <typename T>
void printPair(const std::pair<T,T>& p) {
    std::cout << '(' << std::get<0>(p) << ", " << std::get<1>(p) << ")\n";
}

std::vector<int> getUserVector() {
    std::vector<int> vec{};
    std::cout << "Enter numbers to add (use -1 to stop): ";
    int userIn{};
    std::cin >> userIn;
    while(userIn != -1) {
        vec.push_back(userIn);
        std::cin >> userIn;
    }
    return vec;
    
}

int main() {
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    std::pair p1{vecToPair(v1)};
    std::pair p2{vecToPair(v2)};
    printPair(p1);
    printPair(p2);
    printPair(vecToPair(getUserVector()));
}