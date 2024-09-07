#include <iostream>

// Provide the definition for IntPair and the print() member function here

struct IntPair {
    int one;
    int two;
    void print() {
        std::cout << "1st, 2nd: " << one << ',' << two << '\n';
    }
    bool isEqual(const IntPair& p1) {
        return one == p1.one && two == p1.two;
    }
};

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

	return 0;
}