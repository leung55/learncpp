
#include "input_handling.h"
#include "random.h"
#include <iostream>
#include <string>
#include <memory>
#include <cassert>

class Creature {
protected:
    std::string name;
    char symbol;
    int health;
    int attackDamage;
    int gold;
public:
    Creature(std::string_view name, char symbol, int health, int attackDamage, int gold)
    : name        {name}
    , symbol      {symbol}
    , health      {health}
    , attackDamage{attackDamage}
    , gold        {gold} {}

    const std::string& getName() const {return name;}
    char getSymbol()             const {return symbol;}
    int getHealth()              const {return health;}
    int getAttackDamage()        const {return attackDamage;}
    int getGold()                const {return gold;}
    
    void reduceHealth(int damageTaken) {health -= damageTaken;}
    bool isDead() const                {return health <= 0;}
    void addGold(int newGold)          {gold += newGold;}
};

class Player : public Creature {
    int pLevel;
public:
    Player(std::string_view name, char symbol='@', int health=10, int attackDamage=1, int gold=0, int pLevel=1)
    : Creature{name, symbol, health, attackDamage, gold}
    , pLevel{pLevel} {
        // std::cout << "Player created.\n";
        std::cout << "Welcome, " << name << ".\n";
        std::cout << "You have " << health << " health and are carrying " << gold << " gold.\n";

    }
    // ~Player() {std::cout << "player destroyed\n";}

    void levelUp() {pLevel += 1; attackDamage += 1;}
    void addHealth(int new_health) {health += new_health;}
    void addStrength(int new_strength) {attackDamage += new_strength;}
    int getLevel() const {return pLevel;}
    bool hasWon() const {return pLevel >= 20;}
};

class Monster : public Creature {
public:
    enum Type {
        dragon,
        orc,
        slime,
        maxTypes,
    };
private:
    static inline Creature monsterData[] {
        Creature {"dragon", 'D', 20, 4, 100},
        Creature {"orc", 'o', 4, 2, 25},
        Creature {"slime", 's', 1, 1, 10}
    };
    static_assert(std::size(monsterData) == maxTypes);
public:
    Monster(std::string_view name, char symbol, int health, int attackDamage, int gold)
    : Creature{name, symbol, health, attackDamage, gold} {}
    Monster(Type mType) : Creature{monsterData[mType]} {/* std::cout << getName() << "monster created\n"; */}
    // ~Monster() {std::cout << getName() << " destroyed\n";}
    static Type getRandomMonster() {return static_cast<Type>(Random::get(0,maxTypes-1));}
};

class MonsterGame {
    std::unique_ptr<Player> p;
    std::unique_ptr<Monster> m;
public:
    bool runOrFight() {
        std::cout << "You encountered a " << m->getName() << " (" << m->getHealth() << " health, " << m->getAttackDamage() << " damage, " << m->getGold() << " gold)" << ". Run or fight? [r/f]: ";
        while(true) {
            char choice;
            std::cin >> choice;
            if(InputHandling::clearFailedExtraction() || choice != 'r' && choice != 'f') {
                std::cout << "Invalid decision. Try again [r/f]: ";
                continue;
            }
            InputHandling::ignoreLine();
            return (choice == 'r');
        }
    }
    void playerFight() {
        std::cout << "You attacked the " << m->getName() << " with " << p->getAttackDamage() << " damage.\n";
        m->reduceHealth(p->getAttackDamage());
        std::cout << "The " << m->getName() << " now has " << m->getHealth() << " health.\n";
    }
    void monsterFight() {
        std::cout << "The " << m->getName() << " attacked back with " << m->getAttackDamage() << " damage.\n";
        p->reduceHealth(m->getAttackDamage());
        std::cout << "You now have " << p->getHealth() << " health.\n";
    }
    bool runAttempt() {
        bool escaped{static_cast<bool>(Random::get(0,1))};
        if(escaped) {
            std::cout << "You escaped the monster!\n";
        }
        else {
            std::cout << "You couldn't escape! The " << m->getName() << " attacked with " << m->getAttackDamage() << " damage.\n";
            p->reduceHealth(m->getAttackDamage());
            std::cout << "You now have " << p->getHealth() << " health.\n";
        }
        return escaped;
    }
    void offerPotion() {
        char userDrink;
        std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
        while(true) {
            std::cin >> userDrink;
            if(InputHandling::clearFailedExtraction() || userDrink != 'y' && userDrink != 'n') {
                std::cout << "Invalid choice. Try again [y/n]: ";
                continue;
            }
            InputHandling::ignoreLine();
            break;
        }
        if(userDrink == 'y') {
            int type{Random::get(1,3)};
            int effect{Random::get(1,3)};

            switch(type) {
                case 1 : //health
                    switch(effect) {
                    case 1:
                    case 2:
                        p->addHealth(2); break;
                    case 3:
                        p->addHealth(5); break;
                    }
                    std::cout << "You drank a potion of health! You now have " << p->getHealth() << " health.\n";
                    break;
                case 2 : //strength
                    switch(effect) {
                        case 1:
                        case 2:
                        case 3:
                            p->addStrength(1); break;
                    }
                    std::cout << "You drank a potion of strength! You now have " << p->getAttackDamage() << " attack damage.\n";
                    break;
                case 3: //poison
                    switch(effect) {
                        case 1:
                        case 2:
                        case 3:
                            p->reduceHealth(1); break;
                    }
                    std::cout << "You drank a potion of poison! You now have " << p->getHealth() << " health.\n";
                    break;
            }
        }
    }
    void playGame() {
        std::string name;
        std::cout << "Enter your name: ";
        std::getline(std::cin >> std::ws, name);
        p = std::make_unique<Player>(name);
        while(!(p->isDead()) && !(p->hasWon())) {
            m = std::make_unique<Monster>(Monster::getRandomMonster());
            while(!(p->isDead()) && !(m->isDead())) {
                if(runOrFight()) {
                    if(runAttempt())
                        break;
                }
                else{
                    playerFight();
                    if(!(m->isDead()))
                        monsterFight();
                }
            }
            if(m->isDead()) {
                std::cout << "You killed the " << m->getName() << ".\n";
                assert(!(p->isDead()));
                p->addGold(m->getGold());
                p->levelUp();
                std::cout << "You now have " << p->getGold() << " gold and are now at level " << p->getLevel() << " with " << p->getHealth() << " health.\n";
                if(Random::get(1,10) <= 3)
                    offerPotion();
                continue;
            }
        }
        if(p->isDead()) {
            std::cout << "You died at level " << p->getLevel() << " with " << p->getGold() << " gold.\n";
            return;
        }
        assert(p->hasWon());
        std::cout << "You won with " << p->getGold() << " gold!\n";
    }
};


int main()
{
	// Creature o{ "orc", 'o', 4, 2, 10 };
	// o.addGold(5);
	// o.reduceHealth(1);
	// std::cout << "The " << o.getName() << " has " << o.getHealth() << " health and is carrying " << o.getGold() << " gold.\n";

    
    // Monster m{ Monster::Type::dragon };
	// std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
    // for (int i{ 0 }; i < 10; ++i)
	// {
	// 	Monster m2{ Monster::getRandomMonster() };
	// 	std::cout << "A " << m2.getName() << " (" << m2.getSymbol() << ") was created.\n";
	// }
    MonsterGame mg{};
    mg.playGame();
	return 0;
}