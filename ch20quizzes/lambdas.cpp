#include <string>
#include <array>
#include <algorithm>
#include <iostream>
struct Student {
    std::string_view name;
    int pts;
};

int main () {
    std::array<Student, 8> arr{
    { { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };
    const auto studentComp{
        [](const Student& a, const Student& b) {
            return a.pts < b.pts;
        }
    };
    const Student* top{std::max_element(arr.begin(), arr.end(),studentComp)};
    std::cout << top->name << " is the best student.\n";
    return 0;
}