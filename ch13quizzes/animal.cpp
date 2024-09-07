#include <string>
#include <iostream>
enum class Animal {
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

constexpr std::string_view getAnimalName(Animal animal) {
    using enum Animal;
    switch (animal) {
    case pig: return "pig";
    case chicken: return "chicken";
    case goat: return "goat";
    case cat: return "cat";
    case dog: return "dog";
    case duck: return "duck";
    default: return "???";
    }
}

void printNumberLegs(Animal animal) {
    using enum Animal;
    int numLegs{};
    switch (animal) {
    case chicken:
    case goat:
    case cat: 
    case dog:
        numLegs = 4;
        break;
    case duck:
    case pig:
        numLegs = 2;
        break;
    default: return;  
    }
    std::cout << "A " << getAnimalName(animal) << " has " << numLegs << " legs.\n";
}

int main () {
    printNumberLegs(Animal::cat);
    printNumberLegs(Animal::duck);
    printNumberLegs(Animal::chicken);
    return 0;
}