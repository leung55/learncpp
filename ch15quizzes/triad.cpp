#include <iostream>
#include <string>

template <typename T, typename U, typename V>
class Triad {
    T m_one;
    U m_two;
    V m_three;
public:
    Triad(const T& one, const U& two, const V& three)
        : m_one{one}
        , m_two{two}
        , m_three{three} {}
    const T& getOne() const {return m_one;}
    const U& getTwo() const {return m_two;}
    const V& getThree() const {return m_three;}
    void print() const;
};

template <typename T, typename U, typename V>
void Triad<T,U,V>::print() const {
    std::cout << "Triad: " << m_one << ',' << m_two << ',' << m_three << '\n';
}

int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.getOne() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}