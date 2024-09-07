#include <iostream>

void printCString(const char str[]) {
    for(const char* ptr{str}; *ptr != '\0'; ++ptr) {
        std::cout << *ptr;
    }
    std::cout << '\n';
}

void printCStringBackwards(const char str[]) {
    if(*str == '\0')
        return;
    printCStringBackwards(str + 1);
    std::cout << *str;
}

int main () {
    const char greet[] {"Hello World!"};
    printCString(greet);
    printCStringBackwards(greet);
    std::cout << '\n';
    return 0;
}