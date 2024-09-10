#include <iostream>
#include <numeric>

class Fraction {
    int num{0};
    int denom{1};
public:
    Fraction(int num=0, int denom=1)
    : num{num}
    , denom{denom} {
        reduce();
    }

    void print() const {
        std::cout << num << "/" << denom << '\n';
    }

    void reduce() {
        int gcd = std::gcd(num,denom);
        if(gcd)
        {num /= gcd;
        denom /= gcd;}
    }
    friend Fraction operator*(const Fraction&, const Fraction&);
    friend std::ostream& operator<<(std::ostream&, const Fraction&);
    friend bool operator==(const Fraction& f1, const Fraction& f2) {return f1.num * f2.denom == f2.num * f1.denom;}
    friend bool operator<(const Fraction& f1, const Fraction& f2) {return f1.num * f2.denom < f2.num * f1.denom;}
    friend bool operator!=(const Fraction& f1, const Fraction& f2) {return !(f1 == f2);}
    friend bool operator>(const Fraction& f1, const Fraction& f2) {return f2 < f1;}
    friend bool operator<=(const Fraction& f1, const Fraction& f2) {return !(f1 > f2);}
    friend bool operator>=(const Fraction& f1, const Fraction& f2) {return !(f1 < f2);}

    // friend Fraction operator*(const Fraction&, int);
    // friend Fraction operator*(int, const Fraction&);
};
Fraction operator*(const Fraction& f1, const Fraction& f2) {
    return {f1.num * f2.num, f1.denom * f2.denom};
}

std::ostream& operator<<(std::ostream& out, const Fraction& f) {
    return out << f.num << "/" << f.denom;
}
std::istream& operator>>(std::istream& in, Fraction& f) {
    int num, denom;
    in >> num >> denom;
    if(in) {
        f = Fraction{num,denom};
    }
    return in;
}

// Fraction operator*(const Fraction& f1, int f2) {
//     return {f1.num * f2, f1.denom};
// }

// Fraction operator*(int f2, const Fraction& f1) {
//     return {f1 * f2};
// }

int main()
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    Fraction f7{0, 6};
    f7.print();

    Fraction f8{};
	std::cout << "Enter fraction 1: ";
	std::cin >> f8;

	Fraction f9{};
	std::cout << "Enter fraction 2: ";
	std::cin >> f9;

	std::cout << f8 << " * " << f9 << " is " << f8 * f9 << '\n'; // note: The result of f1 * f2 is an r-value

    Fraction f10{ 3, 2 };
	Fraction f11{ 5, 8 };

	std::cout << f10 << ((f10 == f11) ? " == " : " not == ") << f11 << '\n';
	std::cout << f10 << ((f10 != f11) ? " != " : " not != ") << f11 << '\n';
	std::cout << f10 << ((f10 < f11) ? " < " : " not < ") << f11 << '\n';
	std::cout << f10 << ((f10 > f11) ? " > " : " not > ") << f11 << '\n';
	std::cout << f10 << ((f10 <= f11) ? " <= " : " not <= ") << f11 << '\n';
	std::cout << f10 << ((f10 >= f11) ? " >= " : " not >= ") << f11 << '\n';

    return 0;
}