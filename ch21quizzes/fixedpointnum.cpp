#include <cstddef>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>

class FixedPoint2 {
    std::int16_t whole{0};
    std::int8_t fract{0};
public:
    FixedPoint2(std::int16_t uWhole, std::int8_t uFract)
    : whole{uWhole}
    , fract{uFract} {
        if(whole < 0 || fract < 0) {
            if(whole > 0)
                whole = -whole;
            if(fract > 0)
                fract = -fract;
        }
        whole += fract / 100;
        fract %= 100;
    }
    FixedPoint2(double dIn)
    : FixedPoint2{static_cast<std::int16_t>(std::trunc(dIn)), static_cast<std::int8_t>(std::round(dIn * 100) - std::trunc(dIn) * 100)} {}
    explicit operator double() const {
        return whole + static_cast<double>(fract) / 100;
    }
    friend bool testDecimal(const FixedPoint2 &fp);
    friend bool operator==(const FixedPoint2& fp1, const FixedPoint2& fp2) {
        return (fp1.whole == fp2.whole && fp1.fract == fp2.fract);
    }
    friend FixedPoint2 operator+(const FixedPoint2& fp1, const FixedPoint2& fp2) {
        return static_cast<double>(fp1) + static_cast<double>(fp2);
    }
    FixedPoint2 operator-() const {
        FixedPoint2 fp = *this;
        fp.whole = static_cast<std::int16_t>(-fp.whole);
        fp.fract = static_cast<std::int8_t>(-fp.fract);
        return fp;
    }

};

std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp) {
    return out << static_cast<double>(fp);
}
std::istream& operator>>(std::istream& in, FixedPoint2& fp) {
    double uIn;
    in >> uIn;
    fp = FixedPoint2{uIn};
    return in;
}

#ifdef CAST_TEST
int main()
{
	FixedPoint2 a{ 34, 56 };
	std::cout << a << '\n';
	std::cout << static_cast<double>(a) << '\n';
	assert(static_cast<double>(a) == 34.56);

	FixedPoint2 b{ -2, 8 };
	assert(static_cast<double>(b) == -2.08);

	FixedPoint2 c{ 2, -8 };
	assert(static_cast<double>(c) == -2.08);

	FixedPoint2 d{ -2, -8 };
	assert(static_cast<double>(d) == -2.08);

	FixedPoint2 e{ 0, -5 };
	assert(static_cast<double>(e) == -0.05);

	FixedPoint2 f{ 0, 10 };
	assert(static_cast<double>(f) == 0.1);

	return 0;
}
#endif
// #define DECIMAL_TEST
#ifdef DECIMAL_TEST
bool testDecimal(const FixedPoint2 &fp)
{
    if (fp.whole >= 0)
        return fp.fract >= 0 && fp.fract < 100;
    else
        return fp.fract <= 0 && fp.fract > -100;
}

int main()
{
	FixedPoint2 a{ 1, 104 };
	std::cout << a << '\n';
	std::cout << static_cast<double>(a) << '\n';
	assert(static_cast<double>(a) == 2.04);
	assert(testDecimal(a));

	FixedPoint2 b{ 1, -104 };
	assert(static_cast<double>(b) == -2.04);
	assert(testDecimal(b));

	FixedPoint2 c{ -1, 104 };
	assert(static_cast<double>(c) == -2.04);
	assert(testDecimal(c));

	FixedPoint2 d{ -1, -104 };
	assert(static_cast<double>(d) == -2.04);
	assert(testDecimal(d));

	return 0;
}
#endif
// #define DOUBLE_CONSTRUCTOR
#ifdef DOUBLE_CONSTRUCTOR
int main()
{
	FixedPoint2 a{ 0.01 };
	assert(static_cast<double>(a) == 0.01);

	FixedPoint2 b{ -0.01 };
	assert(static_cast<double>(b) == -0.01);

	FixedPoint2 c{ 1.9 }; // make sure we handle single digit decimal
	assert(static_cast<double>(c) == 1.9);

	FixedPoint2 d{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	assert(static_cast<double>(d) == 5.01);

	FixedPoint2 e{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	assert(static_cast<double>(e) == -5.01);

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 f { 106.9978 }; // should be stored with base 107 and decimal 0
	assert(static_cast<double>(f) == 107.0);

	// Handle case where the argument's decimal rounds to -100 (need to decrease base by 1)
	FixedPoint2 g { -106.9978 }; // should be stored with base -107 and decimal 0
	assert(static_cast<double>(g) == -107.0);

	return 0;
}
#endif

#define OP_TEST
#ifdef OP_TEST
int main()
{
	assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // Test equality true
	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

	// Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // both positive, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // both positive, with decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // second negative, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // second negative, possible decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // first negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // first negative, possible decimal overflow

	FixedPoint2 a{ -0.48 };
	assert(static_cast<double>(a) == -0.48);
	assert(static_cast<double>(-a) == 0.48);

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	std::cout << "You entered: " << a << '\n';
	assert(static_cast<double>(a) == 5.68);

	return 0;
}
#endif