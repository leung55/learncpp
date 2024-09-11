#include <cstddef>
#include <cassert>
#include <iostream>

class IntArray {
    int* arr{nullptr};
    std::size_t arrSize{0};
public:
    explicit IntArray(std::size_t size) : arrSize{size} {
        assert(arrSize > 0);
        arr = new int[arrSize];
    }
    ~IntArray() {
        delete[] arr;
    }
    void deepCopy(const IntArray& intArr) {
        delete[] arr;
        arrSize = intArr.arrSize;
        if(intArr.arr != nullptr) {
            arr = new int[arrSize];
            for(std::size_t i{0}; i < arrSize; ++i)
                arr[i] = intArr.arr[i];
        }
        else
            arr = nullptr;
    }
    IntArray (const IntArray& intArr) {
        deepCopy(intArr);
    }
    IntArray& operator=(const IntArray& intArr) {
        if(this != &intArr)
            deepCopy(intArr);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream&, const IntArray&);
    int& operator[](std::size_t idx) {
        assert(idx >= 0 && idx < arrSize);
        return arr[idx];
    }
};
std::ostream& operator<<(std::ostream& out, const IntArray& intArr) {
    if(intArr.arrSize > 0)
        out << intArr.arr[0];
    for(std::size_t i{1}; i < intArr.arrSize; ++i)
        out << ", " << intArr.arr[i];
    return out;
}

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

	return 0;
}