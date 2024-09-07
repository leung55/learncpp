#include <vector>
#include <iostream>
#include <string>

template <typename T>
bool isValueInArray(const std::vector<T>& v, const T& val) {
    for(const auto& el : v) {
        if(val == el) {
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<std::string_view> names{"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};
    std::string userName;
    std::cout << "Enter a name: ";
    std::cin >> userName;

    bool nameFound{false};
    for(const auto& name: names) {
        if(name == userName) {
            nameFound = true;
            break;
        }
    }

    nameFound = isValueInArray<std::string_view>(names, userName);
    std::cout << userName << " was ";

    if(nameFound) {
        std::cout << "found.\n";
    }
    else {
        std::cout << "not found.\n";
    }
    return 0;
}