#include <vector>
#include <iostream>

void vectorPrint() {
    std::vector<int> v(3);
    std::cout << "enter 3 values: ";
    std::cin >> v[0] >> v[1] >> v[2];
    std::cout << "sum: " << v[0] + v[1] + v[2] << '\n';
    std::cout << "product: " << v[0] * v[1] * v[2] << '\n';
}

template <typename T>
void printElement(const std::vector<T>& v, std::size_t idx) {
    if(idx >= std::ssize(v)) {
        std::cout << "index out of bounds\n";
        return;
    }
    std::cout << v[idx] << '\n';
}

int main() {
    std::vector v{1,4,9,16,25};
    std::vector<double> v2(365);
    std::vector v3 {'h','e','l','l','o'};
    std::cout << std::size(v3) << '\n' << v3[1] << v3.at(1) << '\n';
    vectorPrint();

    std::vector v1 { 0, 1, 2, 3, 4 };
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v4 { 1.1, 2.2, 3.3 };
    printElement(v4, 0);
    printElement(v4, -1);
    return 0;
}