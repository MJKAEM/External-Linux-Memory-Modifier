#include <iostream>
#include "../include/Memory.h"

int main()
{
	gMemory->Process("Program");
	std::cout << gMemory->getPID() << std::endl;
	//gMemory->Write(0x7ffcf248a8ac, 12);

	return 0;
}