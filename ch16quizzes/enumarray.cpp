#include <vector>
#include <cassert>

namespace Animal {
    enum Names{
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        maxAnimals,
    };
}

int main() {
    std::vector legs{2, 4, 4, 4, 2, 0};
    assert(legs.size() == Animal::maxAnimals);
}