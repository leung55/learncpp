#include <cstdint>
#include <iostream>

class Average {
    std::int32_t sum;
    int numOfNums;
public:
    Average(std::int32_t sum=0, int numOfNums=0)
    : sum{sum}
    , numOfNums{numOfNums} {}
    Average& operator+=(std::int32_t newNum) {
        sum += newNum;
        ++numOfNums;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream&, const Average&);
};

std::ostream& operator<<(std::ostream& out, const Average& avg) {
    if(avg.numOfNums == 0)
        return out << 0;
    return out << (static_cast<double>(avg.sum) / avg.numOfNums);
}

int main()
{
	Average avg{};
	std::cout << avg << '\n';

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}