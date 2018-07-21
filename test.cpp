#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

int main()
{
	float a, b;
	int x = 2;
	a = 10.8453;
	b = 0.0001;
	float c = a / b;
	std::cout << "c=" << c << std::endl;
	return(0);
}