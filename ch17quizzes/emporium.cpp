#include "random.h"
#include <iostream>
#include <string>
#include <array>

namespace Potion {
    enum Types {
        healing,
        mana,
        speed,
        invisibility,
        maxPotionTypes,
    };

    struct PotionInfo {
        std::string_view name;
        int cost;
    };

    using namespace std::string_view_literals;
    constexpr std::array<PotionInfo,maxPotionTypes> shopInventory {
        {
            {"healing"sv,       20},
            {"mana"sv,          30},
            {"speed"sv,         12},
            {"invisibility"sv,  50}
        }    
    };
    constexpr int goldMin{80}, goldMax{120};
}

class PotionBuyer {
private:
    std::array<int,Potion::maxPotionTypes> userPotions {};
    std::string name{};
    int gold{};
public:
    void userIntro() const {
        std::cout << "Hello, " << name << ", you have " << gold << " gold.\n";
    }
    void getName() {
        std::cout << "Enter your name: ";
        std::getline(std::cin >> std::ws, name);
    }
    PotionBuyer(
        int gold = 0
    ) : gold{gold} {
        getName();
        userIntro();
    }
    
    int getGold() const {return gold;}
    void setGold(int newGold) {gold = newGold;}
    void incPotions(std::size_t pType) {userPotions[pType]++;}
    void displayInventory() {
        std::cout << "Your inventory contains:\n";
        std::size_t i{0};
        for(const int pCount : userPotions) {
            if(pCount > 0) {
                std::cout << pCount << "x potion of " << Potion::shopInventory[i++].name << '\n';
            }
        }
        std::cout << "You escaped with " << gold << " gold remaining.\n";
    }
};

//returns if user chose to quit
bool getUserInput(PotionBuyer& pb) {
    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    while(true) {
        int userSelect{};
        std::cin >> userSelect;
        if(!std::cin) {
            if (std::cin.eof()) // If the stream was closed
            {
                exit(0); // Shut down the program now
            }
            std::cin.clear();
            char in{};
            std::cin >> in;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(in == 'q') {
                return true;
            }
        }
        else if(userSelect >= Potion::healing && userSelect < Potion::maxPotionTypes) {
            if(pb.getGold() >= Potion::shopInventory[userSelect].cost) {
                pb.setGold(pb.getGold() - Potion::shopInventory[userSelect].cost);
                pb.incPotions(userSelect);
                std::cout << "You purchased a potion of " << Potion::shopInventory[userSelect].name << ". You have " << pb.getGold() << " left.\n";
            }
            else {
                std::cout << "You cannot afford that.\n";
            }
            return false;
        }
        std::cout << "That is invalid input. Try again: ";
    }
}

void printSelection() {
    using namespace Potion;
    int i{0};
    for(const auto& potion : shopInventory) {
        std::cout << i++ << ") " << potion.name << " costs " << potion.cost << '\n';
    }
}

void visitEmporium() {
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    PotionBuyer pb{Random::get(Potion::goldMin,Potion::goldMax)};
    bool userQuit{false};
    while(!userQuit) {
        std::cout << "Here is our selection for today: \n";
        printSelection();
        userQuit = getUserInput(pb);
    }
    pb.displayInventory();
    std::cout << "Thanks for shopping at Roscoe's potion emporium!\n";
}

int main () {
    visitEmporium();
    return 0;
}