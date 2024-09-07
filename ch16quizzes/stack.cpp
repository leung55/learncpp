#include <vector>
#include <string>
#include <iostream>

template <typename T>
void printStack(std::string_view action, const std::vector<T>& v) {
    std::cout << action << "\t(Stack: ";
    if(v.size() == 0) {
        std::cout << "empty";
    }
    for(const auto& el : v) {
        std::cout << el << ' ';
    }

    std::cout << ")\n";
}

int main() {
    std::vector<int> v1{};
    printStack("",v1);
    v1.push_back(1);
    printStack("Push 1", v1);
    v1.push_back(2);
    printStack("Push 2", v1);
    v1.push_back(3);
    printStack("Push 3", v1);
    v1.pop_back();
    printStack("Pop", v1);
    v1.push_back(4);
    printStack("Push 4", v1);
    v1.pop_back();
    printStack("Pop", v1);
    v1.pop_back();
    printStack("Pop", v1);
    v1.pop_back();
    printStack("Pop", v1);
    return 0;
}