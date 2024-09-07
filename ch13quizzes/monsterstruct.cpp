#include <string>
#include <iostream>

enum class MonsterType {
    ogre,
    dragon,
    orc,
    giantSpider,
    slime,
};

struct Monster {
    MonsterType monsterType;
    std::string monsterName;
    int health;
};

constexpr std::string_view getMonsterType (const MonsterType& m_type) {
    using enum MonsterType;
    switch(m_type) {
        case ogre: return "ogre";
        case dragon: return "dragon";
        case orc: return "orc";
        case giantSpider: return "giant spider";
        case slime: return "slime";
        default: return "???";
    }
}
#define DEBUG
#ifdef DEBUG
std::ostream& operator<<(std::ostream& out, MonsterType m_type) {
    out << getMonsterType(m_type);
    return out;
}
void printMonster(const Monster& monster) {
    std::cout << "Monster type: " << monster.monsterType << '\n';
    std::cout << "Monster name: " << monster.monsterName << '\n';
    std::cout << "Monster health: " << monster.health << '\n';
}
#endif

int main () {
    printMonster(Monster {MonsterType::ogre, "Torg", 145});
    printMonster(Monster {MonsterType::slime, "Blurp", 23});
    std::cout << getMonsterType(MonsterType::orc) << '\n';
}