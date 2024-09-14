#include <iostream>
#include <string>
class Fruit {
    std::string name;
    std::string color;
public:
    Fruit(std::string_view name, std::string_view color)
    : name{name}
    , color{color} {}

    const std::string& getName() const {return name;}
    const std::string& getColor() const {return color;}
    friend std::ostream& operator<<(std::ostream& out, const Fruit& fruit) {
        return out << fruit.name << ", " << fruit.color;
    }
};

class Apple : public Fruit {
    double fiber;
public:
    Apple(std::string_view name, std::string_view color, double fiber)
    : Fruit{name, color}
    , fiber{fiber} {}

    friend std::ostream& operator<<(std::ostream& out, const Apple& apple) {
        out << "Apple: ";
        out << static_cast<Fruit>(apple);
        return out << apple.fiber;
    }
    
};

class Banana : public Fruit {
public:
    Banana(std::string_view name, std::string_view color)
    : Fruit{name,color} {}

    friend std::ostream& operator<<(std::ostream& out, const Banana& banana) {
        return out << "Banana: " << static_cast<Fruit>(banana);
    }
};

int main()
{
	const Apple a{ "Red delicious", "red", 4.2 };
	std::cout << a << '\n';

	const Banana b{ "Cavendish", "yellow" };
	std::cout << b << '\n';

	return 0;
}