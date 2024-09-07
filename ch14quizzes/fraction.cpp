#include <iostream>

class Fraction {
    int m_numerator{0};
    int m_denominator{1};
public:
    explicit Fraction(int num = 0, int denom = 1)
        : m_numerator{num}
        , m_denominator{denom} {}
    void getFraction() {
        std::cout << "Enter numerator: ";
        std::cin >> m_numerator;
        std::cout << "Enter denominator: ";
        std::cin >> m_denominator;
    }
    Fraction multiply(const Fraction& f2) const{
        return Fraction {m_numerator * f2.m_numerator, m_denominator * f2.m_denominator};
    }
    int getNumerator() const {return m_numerator;}
    int getDenominator() const {return m_denominator;}
    void printFraction() {
        std::cout << "fraction: " << m_numerator << '/' << m_denominator << '\n';
    }
};

int main()
{
    Fraction f1{};
    f1.getFraction();
    Fraction f2{};
    f2.getFraction();

    std::cout << "Your fractions multiplied together: ";

    // printFraction(multiply(f1, f2));
    (f1.multiply(f2)).printFraction();

    return 0;
}