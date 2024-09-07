#include "random.h"
#include <string>
#include <iostream>

class Monster {
public:
    enum Type {
    dragon,
    goblin,
    ogre,
    orc,
    skeleton,
    troll,
    vampire,
    zombie,
    maxMonsterTypes,
    };
private:
    Type m_type{};
    std::string m_name{"???"};
    std::string m_roar{"???"};
    int m_hp{};
public:
    Monster(Type type, std::string_view name, std::string_view roar, int hp)
        : m_type{type}
        , m_name{name}
        , m_roar{roar}
        , m_hp{hp} {}
    constexpr std::string_view getTypeString() const {
        switch(m_type) {
            case dragon: return "dragon";
            case goblin: return "goblin";
            case ogre: return "ogre";
            case orc: return "orc";
            case skeleton: return "skeleton";
            case troll: return "troll";
            case vampire: return "vampire";
            case zombie: return "zombie";
            case maxMonsterTypes: return "Not a valid monster type";
            default: return "???";
        }
    }
    
    void print() const {
        if(m_hp > 0) {
            std::cout << m_name << " the " << this->getTypeString() << " has " << m_hp << " hit points and says " << m_roar << '\n';
        }
        else {
            std::cout << m_name << " is dead.\n";
        }
    }
};

namespace MonsterGenerator {
    std::string_view getName(int name_choice) {
        switch(name_choice) {
            case 0: return "xander";
            case 1: return "andy";
            case 2: return "buu";
            case 3: return "carl";
            case 4: return "defon";
            case 5: return "earl";
            default: return "???";
        }
    }

    std::string_view getRoar(int roar_choice) {
        switch(roar_choice) {
            case 0: return "growls";
            case 1: return "hawk tuahs";
            case 2: return "boos";
            case 3: return "moos";
            case 4: return "rawrs";
            case 5: return "barks";
            default: return "???";
        }
    }

    Monster generate() {
        return Monster{static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterTypes - 1)), getName(Random::get(0,5)), getRoar(Random::get(0,5)), Random::get(0,100)};
    }
}

int main()
{
	Monster m{ MonsterGenerator::generate() };
	m.print();

	return 0;
}