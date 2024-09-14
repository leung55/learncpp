#include <iostream>
#include <string>

class Fruit {
    std::string name;
    std::string color;
public:
    Fruit(std::string_view name, std::string_view color)
    : name{name}
    , color{color} {}

    std::string& getName() {return name;}
    std::string& getColor() {return color;}
};

class Apple : public Fruit {
public:
    Apple(std::string_view color)
    : Fruit{"Apple", color} {}
};

class Banana : public Fruit {
public:
    Banana() : Fruit{"Banana", "yellow"} {}
};

class GrannySmith : public Apple {
public:
    GrannySmith() : Apple{"green"} {}
    std::string getName() {return "granny smith " + Fruit::getName();}
};

int main()
{
	Apple a{ "red" };
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

	return 0;
}