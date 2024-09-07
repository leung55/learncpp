#include <iostream>

template <typename T>
struct Triad {
    T one;
    T two;
    T three;
};

template <typename T>
void print(const Triad<T>& triad) {
    std::cout << "1st, 2nd, 3rd: " << triad.one << ',' << triad.two << ',' << triad.three << '\n';
}

int main() {
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template argumen        ts
	print(t2);

	return 0;
}