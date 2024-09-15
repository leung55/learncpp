#include <iostream>
#include <array>
#include <vector>
struct Point {
    int x;
    int y;
};

class Shape {
public:
    virtual std::ostream& print(std::ostream&) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& s) {
        return s.print(out);
    }
    virtual ~Shape() = default;
};

class Triangle : public Shape {
    std::array<Point, 3> pts;
public:
    Triangle(const Point& pt1, const Point& pt2, const Point& pt3)
    : pts{{pt1,pt2,pt3}} {}
    std::ostream& print(std::ostream& out) const override {
        for(const auto& pt : pts)
            out << "(x,y): " << pt.x << ',' << pt.y << '\n';
        return out;
    }
};

class Circle : public Shape {
    Point center;
    int radius;
public:
    Circle(const Point& center, int radius)
    : center{center}
    , radius{radius} {}

    std::ostream& print(std::ostream& out) const override {
        return out << "Center (x,y): " << center.x << ',' << center.y << "\nRadius: " << radius << '\n';
    }
    int getRadius() const {return radius;}
};

int getLargestRadius(const std::vector<Shape*>& v) {
    Circle* biggestCircle{nullptr};
    for(const auto& shape : v) {
        Circle* c{dynamic_cast<Circle*>(shape)};
        if(c != nullptr && (biggestCircle == nullptr || c->getRadius() > biggestCircle->getRadius()))
            biggestCircle = c;
    }
    if(biggestCircle)
        return biggestCircle->getRadius();
    return -1;
}
int main()
{
	std::vector<Shape*> v{
	  new Circle{Point{ 1, 2 }, 7},
	  new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
	  new Circle{Point{ 7, 8 }, 3}
	};

	// print each shape in vector v on its own line here
    for(const auto& shape : v)
        std::cout << *shape;

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

	// delete each element in the vector here
    for(const auto& shape : v)
        delete shape;
	return 0;
}