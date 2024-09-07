#include <iostream>

void printArray(const char str[])
{
	str = &str[12];

	for (; *str != '\0'; --str)
		std::cout << *str;
}

int main()
{
	printArray("Hello World!");

	std::cout << '\n';

	return 0;
}