#include <string>
#include <array>
#include <iostream>
struct Item {
    std::string_view name;
    int gold;
};

std::ostream& operator<<(std::ostream& out, Item item) {
    out << "A " << item.name << " costs " << item.gold << " gold.\n";
    return out;
}

template <typename T, auto N>
void printArray(const std::array<T,N> arr) {
    std::cout << "Array: ";
    for(const auto& el : arr) {
        std::cout << el << " ";
    }
    std::cout << "has length " << N << '\n';
}

int main () {
    constexpr std::array<Item,4> items { {
        {"sword", 4},
        {"mace", 2},
        {"axe", 9},
        {"bow", 12}
        }
    };
    printArray(items);
    return 0;
}