#include <iostream>

int main()
{
	int a, b, dummy;
	std::cout << "Insert for value 1." << std::endl;
	std::cin >> a;
	std::cout << "Address of value 1: " << &a << std::endl;

	std::cout << "Insert for value 2." << std::endl;
	std::cin >> b;
	std::cout << "Address of value 2: " << &b << std::endl;

	std::cout << "Press enter to receive the output." << std::endl;
	std::cin >> dummy;
	std::cout << a << " + " << b << " = " << a + b << std::endl;
	return 0;
}