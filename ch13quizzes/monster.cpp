
namespace MonsterType{
    enum MonsterType {
        orc,
        goblin,
        troll,
        ogre,
        skeleton,
    };
}

int main () {
    MonsterType::MonsterType monster{MonsterType::troll};
}
