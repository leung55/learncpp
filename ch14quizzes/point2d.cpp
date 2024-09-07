#include <iostream>
#include <cmath>

class Point2d {
    double m_x{0.0};
    double m_y{0.0};
public:
    Point2d(double x = 0.0, double y = 0.0) 
        : m_x{x}
        , m_y{y}
    {}
    const double getX() {return m_x;}
    const double getY() {return m_y;}
    void print() const {
        std::cout << "Point: " << m_x << ',' << m_y << '\n';
    }
    const double distanceTo (const Point2d& p2) const {
        return std::sqrt((m_x - p2.m_x) * (m_x - p2.m_x) + (m_y - p2.m_y) * (m_y - p2.m_y));
    }
};

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    Point2d third{ 4.0 }; // should error if uncommented

    first.print();
    second.print();
    third.print();
    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';
    return 0;
}