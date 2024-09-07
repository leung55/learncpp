#include <vector>
#include <cassert>
#include <iostream>
namespace Items {
    enum Names {
        hPotions,
        torches,
        arrows,
        maxItems,
};
}

std::string_view getItemString(Items::Names i) {
    using namespace Items;
    switch(i) {
        case hPotions: return "hPotions";
        case torches: return "torches";
        case arrows: return "arrows";
        default: return "???";
    }
}

template <typename T>
void countNumItems(const std::vector<T>& v) {
    int sum{};
    int i{0};
    for(const auto& el : v) {
        std::cout << "You have " << el << ' ' << getItemString(static_cast<Items::Names>(i++)) << " item(s). \n";
        sum += el;
    }
    std::cout << "You have " << sum << " items.\n";
}

int main() {
    std::vector itemCounts{1,5,10};

    assert(itemCounts.size() == Items::maxItems);
    countNumItems(itemCounts);
    return 0;
}