#include <string>
#include <array>
#include <string_view>
#include <iostream>

namespace Animal {
    enum Types {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        maxAnimals,
    };

    struct Data {
        Types name;
        int numLegs;
        std::string_view sound;
    };
    using namespace std::string_view_literals;
    constexpr std::array animalNames{"chicken"sv, "dog"sv, "cat"sv, "elephant"sv, "duck"sv, "snake"sv};
}

std::istream& operator>>(std::istream& in, Animal::Types& anmlType) {
    std::string userStr{};
    std::getline(in >> std::ws, userStr);
    for(std::size_t i{0}; i < std::size(Animal::animalNames); ++i) { 
        if(Animal::animalNames[i] == userStr) {
            anmlType = static_cast<Animal::Types>(i);
            return in;
        }
    }
    in.setstate(std::ios_base::failbit);
    return in;
}

template <typename T, auto N>
void printAnimalInfo(const std::array<T,N> arr, Animal::Types userAnimal) {
    std::cout << "A "<< Animal::animalNames[userAnimal] << " has " << arr.at(userAnimal).numLegs << " legs and says " << arr.at(userAnimal).sound << '\n';
}

template <typename T, auto N>
void printRestInfo(const std::array<T,N> arr, Animal::Types userAnimal) {
    std::cout << "Here is the data for the rest of the animals: \n";
    for(const auto& anml : arr) {
        if(anml.name != userAnimal) {
            printAnimalInfo(arr, anml.name);
        }
    }
}
// template <typename T, auto N>
// void printRestInfo(const std::array<T,N> arr) {
//     std::cout << "Here is the data for the rest of the animals: \n"
//     for(const auto& anml : arr) {
//         printAnimalInfo(arr, anml.name);
//     }
// }

template <typename T, auto N>
void getAnimalInfo(const std::array<T,N> arr) {
    Animal::Types userAnimal{};
    std::cout << "Enter the name of an animal: ";
    std::cin >> userAnimal;
    if(!std::cin) {
        std::cout << "Your animal didn't match anything.\n";
        userAnimal = Animal::maxAnimals;
    }
    else {
        printAnimalInfo(arr, userAnimal);
    }
    printRestInfo(arr, userAnimal);

}



int main() {
    using namespace Animal;
    std::array<Data,maxAnimals> animalData {
        {
            {chicken, 2, "cluck"},
            {dog, 4, "woof"},
            {cat, 4, "meow"},
            {elephant, 4, "rmmmh"},
            {duck, 2, "quack"},
            {snake, 0, "hiss"}
        }
    };
    getAnimalInfo(animalData);
    return 0;
}


